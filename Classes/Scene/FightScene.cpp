/**
* @file FightScene.cpp
* @author wukef & wyf
*/


#include "cocos2d.h"
#include <vector>
#include <string>

#include "Consts.h"
#include "FightScene.h"
#include "Scene/ChooseHero.h"


USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* 预先加载地图函数 */
FightScene::FightScene(TMXTiledMap* map) : _tileMap(map)
{
    currentPlayer = nullptr;
};

FightScene* FightScene::create(TMXTiledMap* map)
{
    auto pRet = new(std::nothrow) FightScene(map);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
    return nullptr;
}

Scene* FightScene::createScene()
{
    auto scene = Scene::createWithPhysics();
   
    if (scene != nullptr)
    {
        scene->addChild(this, 0);
        scene->getPhysicsWorld()->setAutoStep(true);
        scene->getPhysicsWorld()->setGravity(cocos2d::Vec2::ZERO);
        scene->retain();
        return scene;
    }
    return nullptr;
}

/* 界面初始化函数 */
bool FightScene::init()
{
    if (!Scene::init()|| !Scene::initWithPhysics())
    {
        return false;
    }

    
    //to zyy 游戏加载的时候加入音乐组件

    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    initMap();//初始化地图

    initHero();//初始化英雄

    initAI();//初始化AI

    initUI();// 加入ui组件，包括剩余人数，蓝条血条，设置键（音乐和音效各种东西to zyy），暂停和退出按钮（不知道是不是ui）

    gamePause();

    initSmoke();

    listenToUserOperation();//监听用户操作，相当于一个战斗管控器，但感觉只要有监听就可以，这个可以放在战斗类里？？？

    setCamera();

    //this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5秒执行一次schedule AI会0.5秒更新一次目的地，追着你跑

    this->scheduleUpdate();

    return true;
}

/* 需要添加的信息有：镜头的跟随、人物的移动、草坪的状态、人物移动要注意是否有障碍物 */
void FightScene::update(float dt)
{
    //更新玩家的位置
    Vec2 playerPosition = currentPlayer->getPosition();
    this->setPlayerPosition(playerPosition);

    //this->grassCover(playerPosition);//草丛的变化也应该加到这里,但目前有点bug先注释掉
    if (true == AI->isAlive())
    {
        AI->update_hp();
    }

    currentPlayer->update_hp();
    currentPlayer->update_sp();
    currentPlayer->update_mp();

    HeroCount();//记录英雄人数

    currentPlayer->recoverHealth();
    AI->recoverHealth();

    currentPlayer->recoverBullet();
    AI->recoverBullet();
   
}

// OpenGL坐标转成格子坐标，但这个目前的转换不太成功
Vec2 FightScene::tilePosition(const Vec2& position)
{
    Size mapSize = _tileMap->getMapSize();      // 获取以tiles数量为单位的地图尺寸
    Size tileSize = _tileMap->getTileSize();    // 获取以像素点为单位的tile尺寸属性

    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    return Vec2(x, y);
}
/*****************************人物移动**************************************************/
void FightScene::setPlayerPosition(Point position)
{
    Point tileCoord = this->tilePosition(position);
    //首先判断能否移动，注意这个判断的是上一个的内容，如果不能的话返回上一步
    // 比如，人物移动到了一个障碍物处，然后下一步就是人物不能动了，此时恢复原状态
    //边界范围限制
    if (!(tileCoord.x <= 62 && tileCoord.y <= 62 && tileCoord.x >= 3 && tileCoord.y >= 3))
    {
        this->currentPlayer->ChangePosition(false);//最后全改成false
        return;
    }
    //barrier限制
    if (_collidable->getTileAt(tileCoord))
    {
        this->currentPlayer->ChangePosition(false);//最后改成false

        return;
    }

    this->currentPlayer->ChangePosition(true);

}

/*****************************************战斗所需函数************************************************/
void FightScene::listenToUserOperation()
{
    /* 监听键盘WASD实现移动 */
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::listenToKeyPresses, this->currentPlayer);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::listenToKeyReleases, this->currentPlayer);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /* 监听鼠标 实现点击攻击 */
    auto eventListener = cocos2d::EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(FightScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(FightScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool FightScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent)
{
    int bulletRemain = currentPlayer->currentBullet();

    /* touch转世界坐标 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 touchWorldPosition = touch->getLocation() + currentPlayer->getPosition() - Vec2(winSize.width * 0.5f, winSize.height * 0.5f);

    if (0 <= bulletRemain && false == currentPlayer->isReleaseConfirmed())
    {
        /* 创造currentBullet并设置初始位置 */
        auto currentBullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");// 因为子弹是打一个删一个的，所以只能放在onTouchBegan内部
        currentBullet->setPosition(this->currentPlayer->getPosition());// 初始位置是从currentPlayer出发

        /* 给currentBullet绑定物理躯干 */
        bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

        /* 加入渲染树 */
        this->addChild(currentBullet);

        Vec2 offset = touchWorldPosition - this->currentPlayer->getPosition();
        offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

        /* 定义一些动作 */
        auto actionMove = MoveBy::create(1.5f, offset * ShootSpeed);// 1.5秒到达目的地
        auto actionRemove = RemoveSelf::create();// 删掉自身

        /* 让currentBullet完成上面的一系列动作 */
        currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));
    }
    else if (0 <= bulletRemain && true == currentPlayer->isReleaseConfirmed())
    {
        currentPlayer->ultimateSkill(touchWorldPosition);
    }
    else if(0 > bulletRemain)
    {
        auto noBullet = Sprite::create("Hero/Bullet/nobullet.png");
        noBullet->setPosition(touchWorldPosition);
        this->addChild(noBullet);
        auto scaleTo = ScaleTo::create(0.5f, 1.5f, 1.5f);
        auto actionRemove = RemoveSelf::create();
        noBullet->runAction(Sequence::create(scaleTo, actionRemove, nullptr));
    }

    return false;
}

bool FightScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    /* 获取两个碰撞的物体 */
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    /* 火花特效 & 删除标记为BulletTag的那个node(就是之前标记的currentBullet) */
    if (nodeA && nodeB)
    {
        auto currentHero = dynamic_cast<Hero*>(currentPlayer);
        if (nodeA->getTag() == PlayerBulletTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeA);
            AI->receiveDamage(currentPlayer->dealDamage(), AI, currentHero);
        }
        else if (nodeB->getTag() == PlayerBulletTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeB);
            AI->receiveDamage(currentPlayer->dealDamage(), AI, currentHero);
        }
        else if (nodeA->getTag() == EnemyBulletTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeA);
            currentPlayer->receiveDamage(AI->dealDamage(), currentHero, AI);
        }
        else if (nodeB->getTag() == EnemyBulletTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeB);
            currentPlayer->receiveDamage(AI->dealDamage(), currentHero, AI);
        }
        //else if (nodeA->getTag() == PlayerTag && nodeB->getTag() == EnergyTag)
        //{
            //nodeB->removeFromParentAndCleanup(true);
        //}
        //else if (nodeB->getTag() == PlayerTag && nodeA->getTag() == EnergyTag)
        //{
            //nodeA->removeFromParentAndCleanup(true);
        //}

    }

    return true;

}

void FightScene::showSpark(const std::string& filename, cocos2d::Node*& node)
{
    auto spark = Sprite::create(filename);
    spark->setPosition(node->getPosition());
    this->addChild(spark);
    auto scaleTo = ScaleTo::create(0.5f, 0.5f, 0.5f);
    auto actionRemove = RemoveSelf::create();
    spark->runAction(Sequence::create(scaleTo, actionRemove, nullptr));
    node->removeFromParentAndCleanup(true);
}

void FightScene::createAI(float delta)
{
    auto destination = this->currentPlayer->getPosition();
    auto actionMoveAI = MoveTo::create(1.5f, destination);// 1.5秒移动到目的地
    AI->runAction(actionMoveAI);

    Vec2 playerPosition = this->currentPlayer->getPosition();

    /* 创造currentBullet并设置初始位置 */
    auto currentBullet = Sprite::create("Hero/Bullet/enemy-bullet.png");
    currentBullet->setPosition(AI->getPosition());// 初始位置是从AI出发

    /* 给currentBullet绑定物理躯干 */
    bindPhysicsBodyAndTag(currentBullet, EnemyBulletAndPlayerBitmask, EnemyBulletTag);// 只管敌人子弹与玩家的接触

    /* 加入渲染树 */
    this->addChild(currentBullet);

    Vec2 offset = playerPosition - AI->getPosition();
    offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

    /* 定义一些动作 */
    auto actionMove = MoveBy::create(2.0f, offset * ShootSpeed);// 2.0秒到达目的地
    auto actionRemove = RemoveSelf::create();// 删掉自身

    /* 让currentBullet完成上面的一系列动作 */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    if (!AI->isAlive())
    {
        AI->removeFromParentAndCleanup(true);// 这句会让AI造成的伤害清零，player满血
        this->unschedule(CC_SCHEDULE_SELECTOR(FightScene::createAI));
    }
}

void FightScene::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// 传引用，否则会被释放掉
{
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(bitmask);// bitmask是碰撞的body种类 这一句是设置种类
    physicsBody->setContactTestBitmask(bitmask);// 这一句是在这个种类碰撞的时候通知
    sprite->setPhysicsBody(physicsBody);
    sprite->setTag(tag);
}
/******************************************界面初始化*************************************************/
/*初始化地图，添加障碍物/草坪/毒烟/宝箱/人物及ai坐标*/
void FightScene::initMap()
{
    //添加地图,记得添加地图的选择
    //mapChoose界面，将选择的地图传入参数中
    
    this->addChild(_tileMap, 0);//map是已经预加载好的

    //分属性添加内容

    _background = _tileMap->getLayer("Basic");//基础背景

    _barrier = _tileMap->getLayer("Barrier");//障碍物,考虑砖块与小河是否要分开，因为砖块可摧毁

    _collidable = _tileMap->getLayer("Collision");//碰撞图层
    _collidable->setVisible(false);

    _grass = _tileMap->getLayer("Grass");//草丛
}
//绑定指定人物
void FightScene::initHero()
{
    //通过选择的人物来调用不同的createPlayer函数进行
    switch (GameData::_hero)
    {
    case GameData::ChangYi:
        this->currentPlayer = ChangYi::createPlayer();

        break;
    case GameData::YunHe:
        this->currentPlayer = YunHe::createPlayer();

        break;
    case GameData::HaoQing:
        this->currentPlayer = HaoQing::createPlayer();

        break;
    case GameData::SanYue:
        this->currentPlayer = SanYue::createPlayer();

        break;
    case GameData::ShunDe:
        this->currentPlayer = ShunDe::createPlayer();

        break;
    default:
        break;
    }

    this->addChild(this->currentPlayer);// 好像要先加到player里再加到scene里？？？
}

void FightScene::initAI()
{
    AI = PolarBear::createAI();

    this->addChild(AI);

    this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5秒执行一次schedule AI会0.5秒更新一次目的地，追着你跑
}

void FightScene::initUI()
{
    currentPlayer->initHpSlider();
    currentPlayer->initMpSlider();
    currentPlayer->initSpSlider();

    AI->initHpSlider();
    AI->initMpSlider();
    AI->initSpSlider();
}

/***********************************瓦片地图初始化（毒烟、草坪、障碍物）**********************************************/
void FightScene::initSmoke()
{

    _smoke = _tileMap->getLayer("Smoke");//毒烟
    _xSmokeMin = 0,
        _xSmokeMax = _tileMap->getMapSize().width,
        _ySmokeMin = 0,
        _ySmokeMax = _tileMap->getMapSize().height;
    this->smokeMove();
    //不能直接false _smoke->setVisible(false);

    for (int X = _xSmokeMin; X < _xSmokeMax; X++)
    {
        for (int Y = _ySmokeMin; Y < _ySmokeMax; Y++)
        {
            if (_smoke->getTileAt(Vec2(X, Y))) 
            {
                _smokeCell = _smoke->getTileAt(Vec2(X, Y));
                _smokeCell->setVisible(false);
            }
        }
    }

    this->schedule([=](float dt) {				//每20秒刷新
        smokeMove();
        }, SmokeSpeed, "smoke move");


}
//毒烟的移动
void FightScene::smokeMove()
{
    for (int X = _xSmokeMin; X < _xSmokeMax; X++)
    {
        if (_smoke->getTileAt(Vec2(X, _ySmokeMin)))
        {
            _smokeCell = _smoke->getTileAt(Vec2(X, _ySmokeMin));
            _smokeCell->setVisible(true);
        }
        if (_smoke->getTileAt(Vec2(X, _ySmokeMax - 1)))
        {
            _smokeCell = _smoke->getTileAt(Vec2(X, _ySmokeMax - 1));
            _smokeCell->setVisible(true);
        }
    }
    for (int Y = _ySmokeMin; Y < _ySmokeMax; Y++)
    {
        if (_smoke->getTileAt(Vec2(_xSmokeMin, Y)))//如果通过tile坐标能够访问指定毒烟单元格
        {
            _smokeCell = _smoke->getTileAt(Vec2(_xSmokeMin, Y));
            _smokeCell->setVisible(true);
        }
        if (_smoke->getTileAt(Vec2(_xSmokeMax - 1, Y)))
        {
            _smokeCell = _smoke->getTileAt(Vec2(_xSmokeMax - 1, Y));
            _smokeCell->setVisible(true);
        }
    }

    _xSmokeMin++;
    _xSmokeMax--;
    _ySmokeMin++;
    _ySmokeMax--;


}
//毒烟的伤害
void FightScene::smokeHurt(Vec2 position)
{
    Vec2 _tileCoord = this->tilePosition(position); //转化为瓦片地图坐标
    if (_smoke->getTileAt(_tileCoord))
    {
        _smokeCell = _smoke->getTileAt(_tileCoord);
        if (_smokeCell->isVisible()) //如果毒烟可见
        {
            auto currentHero = dynamic_cast<Hero*>(currentPlayer);
            currentPlayer->receiveDamage(SmokeDamage, currentHero);
        }
    }
}
//草坪，这个目前会出现bug所以我准备等坐标修好了之后再来修这个
void FightScene::grassCover(Vec2 position)
{
    //草坪的操作模式是->检测人物碰撞->变透明->人物离开->恢复颜色
    //所以要储存好坐标，走过去和走回来

    static vector<Vec2> grassChange = {}; //储存改变的草丛

    //将之前位置的草丛恢复
    int i; 
    for (i = 0; i < grassChange.size(); i++)
    {
        Point tileCoord = this->tilePosition(grassChange[i]);
        if (_grass->getTileAt(tileCoord))
        {
            _grassCell = _grass->getTileAt(tileCoord); //通过tile坐标访问指定草丛单元格
            _grassCell->setOpacity(255); //将指定草丛单元格设为不透明
        }
    }

    Vec2 tileSize = _tileMap->getTileSize(); //获得单个瓦片尺寸
    
    //将玩家及其周围所在草丛变透明
    grassChange =
    {
        position,
        Vec2(position.x + tileSize.x, position.y),
        Vec2(position.x - tileSize.x, position.y),
        Vec2(position.x, position.y + tileSize.y),
        Vec2(position.x, position.y - tileSize.y)
    }; 

    for (i = 0; i < grassChange.size(); i++)
    {
        Vec2 tileCoord = this->tilePosition(grassChange[i]);
        if (_grass->getTileAt(tileCoord))
        {
            _grassCell = _grass->getTileAt(tileCoord); 
            _grassCell->setOpacity(100); //将指定草丛单元格变透明
        }
    }

    /*英雄在草丛里半透明
    Point tileCoord = this->tileCoordForPosition(position);
    if (_grass->getTileAt(tileCoord))
    {
        _player->getBrawler()->getSprite()->setOpacity(100);
    }
    else
    {
        _player->getBrawler()->getSprite()->setOpacity(255);
    }*/


}
/***********************************ui组件初始化（剩余人数、时间）**********************************************/

//to myself 记得加上第二个层，要不没法做
//to wkf 每当消灭一个英雄，在消灭英雄函数内执行减一操作，然后在执行计分板操作
void FightScene::HeroCount()//计分板
{// 有个问题就是放到update里会有重叠 然后touch会执行多次 by wkf
    heroNumber = Label::createWithTTF(StringUtils::format("Brawler Left: %d", GameData::getRemainingPlayer()).c_str(), "fonts/arial.ttf", 40);
    heroNumber->setAnchorPoint(Vec2(0, 1));
    heroNumber->setPosition(Vec2(_origin.x, _visibleSize.height + _origin.y));
    this->addChild(heroNumber, 3);
    heroNumber->setCameraMask(2, true);
}
//游戏暂停
void FightScene::gamePause()
{
    //初始化gamepause的按钮，当点击的时候，执行转换函数，注意场景应该是pop
    //注意时间的暂停！！！
    auto pauseItem = cocos2d::MenuItemImage::create(
        "Button/PauseNormal.png",
        "Button/PauseSelected.png",
        CC_CALLBACK_1(FightScene::GamePauseCallback, this));

    pauseItem->setPosition(Vec2(_visibleSize.width - pauseItem->getContentSize().width / 2,
        _visibleSize.height - pauseItem->getContentSize().height / 2));

    pauseButton_ = cocos2d::Menu::create(pauseItem, nullptr);
    pauseButton_->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(pauseButton_, 2);
    pauseButton_->setCameraMask(2, true);

}

void FightScene::GamePauseCallback(Ref* pSender)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();

    Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
    
}

/*****************************游戏状态记录，人物是否死亡、游戏是否结束**********************************************/

void FightScene::setCamera()
{
    this->fightCamera = CameraEffect::create(this);
    if (this->fightCamera != nullptr && this->currentPlayer != nullptr)
    {
        this->fightCamera->FollowPlayer(currentPlayer);
    }
}

void FightScene::GameOver()
{
    //游戏结束的条件
    //玩家死亡or剩余英雄为（只有玩家）or定时器时间到（可以不用考虑）-》把定时器的时间设置为毒雾蔓延＋人物血量减毒雾伤害
    //转到游戏结算界面



}