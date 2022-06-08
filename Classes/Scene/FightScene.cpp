/**
* @file FightScene.cpp
* @author wukef & wyf
*/

#include "Consts.h"
#include "cocos2d.h"
#include "FightScene.h"
#include "Scene/ChooseHero.h"
#include <vector>
#include <string>

USING_NS_CC;
using namespace std;
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

FightScene::FightScene(TMXTiledMap* map) : _tileMap(map)
{
    currentPlayer = nullptr;
    //dropNode_ = nullptr;
    //mainCFightScene::FightScene(TMXTiledMap* map): _tileMap(map)amera_ = nullptr;
   // touchHolding_ = false;
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

cocos2d::Scene* FightScene::createScene()
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


bool FightScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    
    initMap();//初始化地图

    initHero();//初始化英雄

    AI = PolarBear::createAI();

    this->addChild(AI);

    setCamera();

    this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5秒执行一次schedule AI会0.5秒更新一次目的地，追着你跑

    listenToUserOperation();

    return true;
}

void FightScene::initMap()
{
    //添加地图
    this->addChild(_tileMap, 0);

   //分属性添加内容

    _background = _tileMap->getLayer("Basic");//基础背景
    
    _barrier = _tileMap->getLayer("Barrier");//障碍物

    _collision = _tileMap->getLayer("Collision");//碰撞图层
    _collision->setVisible(false);
    
    _grass = _tileMap->getLayer("Grass");//草丛

   /*
   _smoke = _tileMap->getLayer("Smoke");//毒烟
    _xTileCoordMin = 0,
        _xTileCoordMax = _map->getMapSize().width,
        _yTileCoordMin = 0,
        _yTileCoordMax = _map->getMapSize().height;
    this->smokeMove();

    _box = _tileMap->getObjectGroup("Box");//宝箱

     // 获取全部宝箱位置
    this->getBoxPosition();

    //添加宝箱/
    addBox();
   
   */ 
    
}


/*绑定指定人物*/
void FightScene::initHero()
{

    this->currentPlayer = PolarBear::createPlayer();// 通过这两句换英雄

    string brawlerName;

    switch (FightUtils::_hero)
    {
    case FightUtils::ChangYi:
        this->currentPlayer = ChangYi::createPlayer();
        brawlerName = "ChangYi";
        break;
    case FightUtils::YunHe:
        this->currentPlayer = YunHe::createPlayer();
        brawlerName = "YunHe";
        break;
    case FightUtils::HaoQing:
        this->currentPlayer = HaoQing::createPlayer();
        brawlerName = "HaoQing";
        break;
    case FightUtils::SanYue:
        this->currentPlayer = SanYue::createPlayer();
        brawlerName = "SanYue";
        break;
    case FightUtils::ShunDe:
        this->currentPlayer = ShunDe::createPlayer();
        brawlerName = "ShunDe";
        break;
    default:
        break;
    }

}

void FightScene::listenToUserOperation()
{
    this->addChild(this->currentPlayer);// 好像要先加到player里再加到scene里？？？
    this->currentPlayer->scheduleUpdate();// 用来schedule update

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
    /* 创造currentBullet并设置初始位置 */
    auto currentBullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");// 因为子弹是打一个删一个的，所以只能放在onTouchBegan内部
    currentBullet->setPosition(this->currentPlayer->getPosition());// 初始位置是从currentPlayer出发

    /* 给currentBullet绑定物理躯干 */
    bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

    /* 加入渲染树 */
    this->addChild(currentBullet);

    /* touch转世界坐标 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 touchWorldPosition = touch->getLocation() + currentPlayer->getPosition() - Vec2(winSize.width * 0.5f, winSize.height * 0.5f);

    Vec2 offset = touchWorldPosition - this->currentPlayer->getPosition();
    offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

    /* 定义一些动作 */
    auto actionMove = MoveBy::create(1.5f, offset * ShootSpeed);// 1.5秒到达目的地
    auto actionRemove = RemoveSelf::create();// 删掉自身

    /* 让currentBullet完成上面的一系列动作 */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    return true;
}

bool FightScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    /* 获取两个碰撞的物体 */
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    /* 火花特效 & 删除标记为BulletTag的那个node(就是之前标记的currentBullet) */
    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == PlayerBulletTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeA);
            AI->receiveDamage(20,AI);// 我随便写的 后面可以随英雄变化
        }
        else if (nodeB->getTag() == PlayerBulletTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeB);
            AI->receiveDamage(20,AI);// 我随便写的 后面可以随英雄变化
        }
        else if (nodeA->getTag() == EnemyBulletTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeA);
        }
        else if (nodeB->getTag() == EnemyBulletTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeB);
        }
        else if (nodeA->getTag() == PlayerTag && nodeB->getTag() == EnergyTag)
        {
            nodeB->removeFromParentAndCleanup(true);
        }
        else if (nodeB->getTag() == PlayerTag && nodeA->getTag() == EnergyTag)
        {
            nodeA->removeFromParentAndCleanup(true);
        }

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
        AI->removeFromParentAndCleanup(true);
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

void FightScene::setCamera()
{
    this->fightCamera = CameraEffect::create(this);
    if (this->fightCamera != nullptr && this->currentPlayer != nullptr)
    {
        this->fightCamera->FollowPlayer(currentPlayer);
    }
}