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

Scene* FightScene::createScene()
{
    return FightScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FightScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
   //��֪��Ϊʲô����tmx��ʱ�����Ǽ��ش���̫������
	//auto* SnowMap = TMXTiledMap::create("Map/SnowMap.tmx");
	//addChild(SnowMap, 0);

    auto winSize = Director::getInstance()->getVisibleSize();

    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = DrawNode::create();

    /* Ŀǰ�ȷ�һ����ɫ�������ĸ�float������һ�����Ի���ɫ */
    background->drawSolidRect(origin, winSize, cocos2d::Color4F(0.6f, 0.6f, 0.6f, 1.0f));

    this->addChild(background);

    listenToUserOperation("Hero/polar-bear.png");

    return true;
}

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