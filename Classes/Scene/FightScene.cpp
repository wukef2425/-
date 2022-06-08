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
using namespace std;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/*Ԥ�ȼ��ص�ͼ����,*/
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

/*�����ʼ������*/
bool FightScene::init()
{

    if (!Scene::init()|| !Scene::initWithPhysics())
    {
        return false;
    }

    //to zyy ��Ϸ���ص�ʱ������������

    initMap();//��ʼ����ͼ

    //initUI(); ����ui���������ʣ������������Ѫ�������ü������ֺ���Ч���ֶ���to zyy������ͣ���˳���ť����֪���ǲ���ui��

    initHero();//��ʼ��Ӣ��

    initAI();//��ʼ��AI

    listenToUserOperation();//�����û��������൱��һ��ս���ܿ��������о�ֻҪ�м����Ϳ��ԣ�������Է���ս���������

    this->scheduleUpdate();

    return true;
}

/*��Ҫ��ӵ���Ϣ�У���ͷ�ĸ��桢������ƶ�����ƺ��״̬�������ƶ�Ҫע���Ƿ����ϰ���*/
void FightScene::update(float dt)
{
    //this->setViewPointCenter(playerPos);//to wkf ���þ�ͷ������Լӵ�����
    // 
    // 
    // 
    // //�����ƶ��ĸ���Ӧ�÷�����update��
    //������ҵ�λ��
    Vec2 playerPos = currentPlayer->getPosition();
    this->setPlayerPosition(playerPos);//to wkf ���������������ҵ�λ�ã��ȴ���setplayerposition�����н����жϣ�������Ը��ĵĻ���setposition�������ԵĻ�
                                       //��ֱ��return�ﵽ�޷��ƶ���Ч��
    //����ai���ƶ��Ƿ�ҲҪ�ӵ�����������ܻ᲻ͬ������Ҫ��һ��ʱ��
                                       //this->setGrassOpacity(playerPos);//�ݴԵı仯ҲӦ�üӵ�����
   
}

/*****************************************ս�����躯��************************************************/
void FightScene::listenToUserOperation()
{
    this->addChild(this->currentPlayer);// ����Ҫ�ȼӵ�player���ټӵ�scene�����
    this->currentPlayer->scheduleUpdate();// ����schedule update

    /* ��������WASDʵ���ƶ� */
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::listenToKeyPresses, this->currentPlayer);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::listenToKeyReleases, this->currentPlayer);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /* ������� ʵ�ֵ������ */
    auto eventListener = cocos2d::EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(FightScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    /* ��ײ���� */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(FightScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool FightScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent)
{
    Vec2 touchLocation = touch->getLocation();

    /* ����currentBullet�����ó�ʼλ�� */
    auto currentBullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");// ��Ϊ�ӵ��Ǵ�һ��ɾһ���ģ�����ֻ�ܷ���onTouchBegan�ڲ�
    currentBullet->setPosition(this->currentPlayer->getPosition());// ��ʼλ���Ǵ�currentPlayer����

    /* ��currentBullet���������� */
    bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

    /* ������Ⱦ�� */
    this->addChild(currentBullet);

    Vec2 offset = touchLocation - this->currentPlayer->getPosition();
    offset.normalize();// currentPlayerλ��ָ�����touchλ�õĵ�λ����
    auto aid = offset * ShootSpeed;// �Ķ�������Ը��ӵ��������ʣ����ڿ��Բ�ͬ��Ӣ�۲�һ��
    auto shootRange = aid + currentBullet->getPosition();// ��̣�ʵ������Vec2��Ŀ�ĵ�

    /* ����һЩ���� */
    auto actionMove = MoveTo::create(1.5f, shootRange);// 1.5�뵽��Ŀ�ĵ�
    auto actionRemove = RemoveSelf::create();// ɾ������

    /* ��currentBullet��������һϵ�ж��� */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    return true;
}

bool FightScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    /* ��ȡ������ײ������ */
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    /* ����Ч & ɾ�����ΪBulletTag���Ǹ�node(����֮ǰ��ǵ�currentBullet) */
    if (nodeA && nodeB)
    {
        if (nodeA->getTag() == PlayerBulletTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeA);
            AI->receiveDamage(30);// �����д�� ���������Ӣ�۱仯
        }
        else if (nodeB->getTag() == PlayerBulletTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeB);
            AI->receiveDamage(30);// �����д�� ���������Ӣ�۱仯
        }
        else if (nodeA->getTag() == EnemyBulletTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeA);
        }
        else if (nodeB->getTag() == EnemyBulletTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeB);
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
    auto actionMoveAI = MoveTo::create(1.5f, destination);// 1.5���ƶ���Ŀ�ĵ�
    AI->runAction(actionMoveAI);

    Vec2 playerPosition = this->currentPlayer->getPosition();

    /* ����currentBullet�����ó�ʼλ�� */
    auto currentBullet = Sprite::create("Hero/Bullet/enemy-bullet.png");
    currentBullet->setPosition(AI->getPosition());// ��ʼλ���Ǵ�AI����

    /* ��currentBullet���������� */
    bindPhysicsBodyAndTag(currentBullet, EnemyBulletAndPlayerBitmask, EnemyBulletTag);// ֻ�ܵ����ӵ�����ҵĽӴ�

    /* ������Ⱦ�� */
    this->addChild(currentBullet);

    Vec2 offset = playerPosition - AI->getPosition();
    offset.normalize();// currentPlayerλ��ָ�����touchλ�õĵ�λ����
    auto aid = offset * ShootSpeed;// �Ķ�������Ը��ӵ��������ʣ����ڿ��Բ�ͬ��Ӣ�۲�һ��
    auto shootRange = aid + currentBullet->getPosition();// ��̣�ʵ������Vec2��Ŀ�ĵ�

    /* ����һЩ���� */
    auto actionMove = MoveTo::create(2.0f, shootRange);// 2.0�뵽��Ŀ�ĵ�
    auto actionRemove = RemoveSelf::create();// ɾ������

    /* ��currentBullet��������һϵ�ж��� */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    if (!AI->isAlive())
    {
        AI->removeFromParentAndCleanup(true);
        this->unschedule(CC_SCHEDULE_SELECTOR(FightScene::createAI));
    }
}

void FightScene::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// �����ã�����ᱻ�ͷŵ�
{
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(bitmask);// bitmask����ײ��body���� ��һ������������
    physicsBody->setContactTestBitmask(bitmask);// ��һ���������������ײ��ʱ��֪ͨ
    sprite->setPhysicsBody(physicsBody);
    sprite->setTag(tag);
}
/******************************************�����ʼ��*************************************************/
/*��ʼ����ͼ������ϰ���/��ƺ/����/����/���Ｐai����*/
void FightScene::initMap()
{
    //��ӵ�ͼ,�ǵ���ӵ�ͼ��ѡ��
    //mapChoose���棬��ѡ��ĵ�ͼ���������
    
    this->addChild(_tileMap, 0);//map���Ѿ�Ԥ���غõ�

    //�������������

    _background = _tileMap->getLayer("Basic");//��������

    _barrier = _tileMap->getLayer("Barrier");//�ϰ���,����ש����С���Ƿ�Ҫ�ֿ�����Ϊש��ɴݻ�

    _collidable = _tileMap->getLayer("Collision");//��ײͼ��
    _collidable->setVisible(false);

    _grass = _tileMap->getLayer("Grass");//�ݴ�

    _smoke = _tileMap->getLayer("Smoke");//����
    _xSmokeMin = 0,
    _xSmokeMax = _tileMap->getMapSize().width,
    _ySmokeMin = 0,
    _ySmokeMax = _tileMap->getMapSize().height;
    this->smokeMove();

    //���̵��ƶ���һ�����ƶ�30�Σ�ÿ20���ƶ�һ�Σ���Ϸһ��6min
    //to wkf ��֪�����������ʲô���÷���Ҫ�����������÷�ʽ���Ը���һ��
    this->schedule([=](float dt) {				//ÿ20��ˢ��
        smokeMove();
        }, SmokeSpeed, "smoke move");


}
/*��ָ������*/
void FightScene::initHero()
{
    //ͨ��ѡ������������ò�ͬ��createPlayer��������
    switch (FightUtils::_hero)
    {
    case FightUtils::ChangYi:
        this->currentPlayer = ChangYi::createPlayer();

        break;
    case FightUtils::YunHe:
        this->currentPlayer = YunHe::createPlayer();

        break;
    case FightUtils::HaoQing:
        this->currentPlayer = HaoQing::createPlayer();

        break;
    case FightUtils::SanYue:
        this->currentPlayer = SanYue::createPlayer();

        break;
    case FightUtils::ShunDe:
        this->currentPlayer = ShunDe::createPlayer();

        break;
    default:
        break;
    }
}

void FightScene::initAI()
{
    AI = PolarBear::createAI();

    this->addChild(AI);

    this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5��ִ��һ��schedule AI��0.5�����һ��Ŀ�ĵأ�׷������
}

void FightScene::initUI()
{

}

/***********************************��Ƭ��ͼ��ʼ�������̡���ƺ���ϰ��**********************************************/

// OpenGL����ת�ɸ�������
Vec2 FightScene::tileCoordFormPosition(const Vec2& position)
{
    Size mapSize = _tileMap->getMapSize();      // ��ȡ��tiles����Ϊ��λ�ĵ�ͼ�ߴ�
    Size tileSize = _tileMap->getTileSize();    // ��ȡ�����ص�Ϊ��λ��tile�ߴ�����
    
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    return Vec2(x, y);
}

void FightScene::setPlayerPosition(Point position)
{

    Point tileCoord = this->tileCoordFormPosition(position); 

    //�߽緶Χ����
    if (!(tileCoord.x <=62 && tileCoord.y <=62 && tileCoord.x >= 3 && tileCoord.y >= 3))
    {
        return; 
    }
    //barrier����
    if (_collidable->getTileAt(tileCoord))
    {
        return;
    }

    currentPlayer->setPosition(position);

}

//���̵��ƶ�
void FightScene::smokeMove()
{

    /* ȫ����ʾ���� */
    for (int X = _xSmokeMin; X <_xSmokeMax; X++)
    {
        for (int Y = _ySmokeMin; Y < _ySmokeMax; Y++)
        {
            if (_smoke->getTileAt(Vec2(X, Y))) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
            {
                _smokeCell = _smoke->getTileAt(Vec2(X, Y));
                _smokeCell->setVisible(true);
            }
        }
    }

    /* ���Ĳ���ʾ���� */
    for (int X = _xSmokeMin; X <_xSmokeMax; X++)
    {
        for (int Y = _ySmokeMin; Y <_ySmokeMax; Y++)
        {
            if (_smoke->getTileAt(Vec2(X, Y))) //���ͨ��tile�����ܹ�����ָ�����̵�Ԫ��
            {
                _smokeCell = _smoke->getTileAt(Vec2(X, Y));
                _smokeCell->setVisible(false);
            }
        }
    }

    /* �����ƶ� */
    _xSmokeMin++;
    _xSmokeMax--;
    _ySmokeMin++;
    _ySmokeMax--;

    
}
//���̵��˺�

/***********************************ui�����ʼ����ʣ��������Ѫ����������**********************************************/



/**********************************��Ϸ״̬��¼�������Ƿ���������Ϸ�Ƿ����*************************************************/



