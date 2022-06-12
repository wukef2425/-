/**
*@file SetScene.cpp
* @author wyf
*/
#include "UserInfo.h"
#include "Scene/StartMenuScene.h"
#include "Utils/GameData.h"

#include "cocos2d.h"
#include <string>
USING_NS_CC;

Scene* UserInfo::createScene()
{
    return UserInfo::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool UserInfo::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    //�ǵ�����һ������ͼƬ����ͳ��ģ���ʵ���Ի���һ�𣬰�������ɶ�ģ����ǿ�������������������������ǵò�Ҫ�ڵ�
    //��������ť��λ�ò�û�кú÷ţ��ǵø�һ�£��������ÿ�������������¹���
    initDecoration();//һЩ�û������۵Ķ���
    initHero();
    initTrophy();
    initReturnMenu();
    return true;
}

void UserInfo::initDecoration()
{
    

    //���ñ���ͼƬ
    auto* setScene = Sprite::create("Scene/UserScene.png");        //�����౳��ͼ
    setScene->setScale(0.8f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //�ñ���ͼ�������ʾ
    addChild(setScene, 0);
    
}

void UserInfo::initHero()
{
    int chooseHeroNumber = GameData::getChooseHero();
    Sprite* character;
    switch (chooseHeroNumber)
    {
    case ChangYiNumber:
        character = Sprite::create("Hero/EndHero/ChangYi.png");
        break;
    case YunHeNumber:
        character = Sprite::create("Hero/EndHero/YunHe.png");
        break;
    case HaoQingNumber:
        character = Sprite::create("Hero/EndHero/HaoQing.png");
        break;
    case SanYueNumber:
        character = Sprite::create("Hero/EndHero/SanYue.png");
        break;
    case ShunDeNumber:
        character = Sprite::create("Hero/EndHero/ShunDe.png");
        break;
    default:
        break;
    }
    character->setScale(1.3f);
    character->setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 3);
    addChild(character, 1);
}

void UserInfo::initTrophy()
{
    auto _trophy = Label::createWithTTF(StringUtils::format("Trophy: %d", GameData::_trophy).c_str(), "fonts/arial.ttf", 40);
    _trophy->setColor(Color3B::YELLOW);
    _trophy->enableShadow();
    _trophy->enableGlow(Color4B(255, 0, 0, 0));
    _trophy->setAnchorPoint(Vec2(0, 1));
    _trophy->setPosition(Vec2(origin.x + 2*visibleSize.width / 3,  2*visibleSize.height / 5 + origin.y));
    this->addChild(_trophy, 1);
}

void UserInfo::initReturnMenu()
{

    auto pReturnItem = cocos2d::MenuItemImage::create(
        "Button/ReturnSet.png",
        "Button/ReturnSet.png",
        CC_CALLBACK_1(UserInfo::menuReturnCallback, this));

    pReturnItem->setPosition(Vec2(8 * visibleSize.width / 10, 7 * visibleSize.height / 9));

    pMenu = cocos2d::Menu::create(pReturnItem, nullptr);
    pMenu->setScale(1.2f);
    pMenu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(pMenu, 2);

}

void UserInfo::menuReturnCallback(Ref* pSender)
{
    //���·��ذ�ť���л���menuҳ��
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}