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
   
    this->addChild(_tileMap, 0);
   
    listenToUserOperation("Hero/polar-bear.png");

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


void FightScene::listenToUserOperation(const std::string& filename)
{
    currentPlayer = Player::create(filename);

    this->addChild(currentPlayer);// ����Ҫ�ȼӵ�player���ټӵ�scene�����

    currentPlayer->scheduleUpdate();// ����schedule update

    /* ��������WASDʵ���ƶ� */
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::listenToKeyPresses, currentPlayer);

    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::listenToKeyReleases, currentPlayer);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /* ������� ʵ�ֵ������ */
    auto eventListener = cocos2d::EventListenerTouchOneByOne::create();

    eventListener->onTouchBegan = CC_CALLBACK_2(FightScene::onTouchBegan, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

bool FightScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent)
{
    Vec2 touchLocation = touch->getLocation();

    Vec2 offset = touchLocation - currentPlayer->getPosition();

    auto bullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");

    bullet->setPosition(currentPlayer->getPosition());

    this->addChild(bullet);

    offset.normalize();

    auto aid = offset * 1000;// �Ķ�������Ը��ӵ��������ʣ����ڿ��Բ�ͬ��Ӣ�۲�һ��

    auto shootRange = aid + bullet->getPosition();

    auto actionMove = MoveTo::create(2.0f, shootRange);// ���뵽��Ŀ�ĵأ�Ҳ����ͨ�����������

    auto actionRemove = RemoveSelf::create();

    bullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    return true;
}