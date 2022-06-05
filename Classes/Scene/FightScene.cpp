/**
* @file FightScene.cpp
* @author wukef & wyf
*/

/*Fight������ҪҪ���ص�������
1.UI������������Ϸʱ��/����Ѫ������/��������/��/��ľ��棬�����Ƕ�̬�ɱ仯��
2.��������ͨ�����/����/��������������ﶯ�����иı�
3.ÿһ��Ԫ�����ڵĲ㣺��ͼ 0���ϰ������ 1�����ò� 5��������
4.�ֽ��ߣ�������Χ����������

*/

#include "Consts.h"
#include "cocos2d.h"
#include "FightScene.h"

USING_NS_CC;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

FightScene::FightScene(TMXTiledMap* map): _tileMap(map)
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

void FightScene::bindPlayer(Player* player)
{
    if (player != nullptr && currentPlayer == nullptr)
    {
        this->currentPlayer = player;
        //this->addChild(player);
    }
   
}
// on "init" you need to initialize your instance
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
   
    this->addChild(_tileMap, 0);

    this->currentPlayer = PolarBear::createPlayer();// ͨ�������任Ӣ��
    AI = PolarBear::createAI();

    this->addChild(AI);
    
    this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5��ִ��һ��schedule AI��0.5�����һ��Ŀ�ĵأ�׷������

    listenToUserOperation();

    return true;
}

/*
void FightScene::loadingFightScene()//���ص�ͼ����ͼ�е��ϰ���/��ƺ/Ӣ�ۡ���ͼ�е�UI���
{

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    TMXTiledMap* _tileMap = TMXTiledMap::create("Map/SnowMap.tmx");

    _tileMap->setPosition(origin.x - _tileMap->getContentSize().width / 2, origin.y - _tileMap->getContentSize().height / 2);

    this->addChild(_tileMap, 0);

}
*/


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

