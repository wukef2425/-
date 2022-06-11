/**
*@file SetScene.cpp
* @author wyf
*/
/*ҳ��Ҫʵ�ֵ����ݣ�
�鿴�û����ǳ�ͷ�񲢿��Ը���
�鿴�û�Ŀǰ�Ľ����������룩
�鿴����ֵ�͵ȼ�
�鿴ʤ����
������ҳ�棨���룩
*/
#include "UserInfo.h"
#include "Scene/StartMenuScene.h"

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
    //�ǵ�����һ������ͼƬ����ͳ��ģ���ʵ���Ի���һ�𣬰�������ɶ�ģ����ǿ�������������������������ǵò�Ҫ�ڵ�
    //��������ť��λ�ò�û�кú÷ţ��ǵø�һ�£��������ÿ�������������¹���
    initDecoration();//һЩ�û������۵Ķ���

    initReturnMenu();
    return true;
}

void UserInfo::initDecoration()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ñ���ͼƬ
    auto* setScene = Sprite::create("Scene/SetScene.jpg");        //�����౳��ͼ
    setScene->setScale(0.8f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //�ñ���ͼ�������ʾ
    addChild(setScene, 0);
    
}

void UserInfo::initReturnMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto returnButton = cocos2d::MenuItemImage::create("Button/Return.png", "Button/Return.png", CC_CALLBACK_1(UserInfo::menuReturnCallback, this));

    if (returnButton == nullptr ||
        returnButton->getContentSize().width <= 0 ||
        returnButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width * 4) / 5 - returnButton->getContentSize().width / 3;
        float y = origin.y + (visibleSize.height * 2) / 3;
        returnButton->setScale(0.9f);
        returnButton->setPosition(cocos2d::Vec2(x, y));
    }
    returnButton_ = cocos2d::Menu::create(returnButton, nullptr);
    this->addChild(returnButton_, 1);
    returnButton_->setPosition(cocos2d::Vec2::ZERO);
}

void UserInfo::menuReturnCallback(Ref* pSender)
{
    //���·��ذ�ť���л���menuҳ��
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}