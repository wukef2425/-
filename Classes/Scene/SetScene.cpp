/**
*@file SetScene.cpp
* @author wyf
*/
#include "SetScene.h"
#include "StartMenuScene.h"

USING_NS_CC;

Scene* SetScene::createScene()
{
    return SetScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SetScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //�ǵ�����һ������ͼƬ����ͳ��ģ���ʵ���Ի���һ�𣬰�������ɶ�ģ����ǿ�������������������������ǵò�Ҫ�ڵ�
    //��������ť��λ�ò�û�кú÷ţ��ǵø�һ�£��������ÿ�������������¹���
    initDecoration();//һЩ�û������۵Ķ���
    initRuleBooks();
    initVolumeSound();
    initReturnMenu();
    return true;
}

void SetScene::initDecoration()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ñ���ͼƬ
    auto* setScene = Sprite::create("Scene/SetScene.jpg");        //�����౳��ͼ
    setScene->setScale(1.05f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //�ñ���ͼ�������ʾ
    addChild(setScene, 0);
    //��ǩ
    auto setLabel = Label::createWithTTF("Setting", "fonts/arial.ttf", 60);
    setLabel->enableGlow(Color4B::BLUE);
    if (setLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        setLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - setLabel->getContentSize().height));
        this->addChild(setLabel, 1);
    }
}

void SetScene::initRuleBooks()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto ruleButton = cocos2d::MenuItemImage::create("Button/RuleBooks.png", "Button/RuleBooks.png", CC_CALLBACK_1(SetScene::ruleBooksCallback, this));

    if (ruleButton == nullptr ||
        ruleButton->getContentSize().width <= 0 ||
        ruleButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width*2)/5-ruleButton->getContentSize().width / 3;
        float y = origin.y + (visibleSize.height*2)/3;
        ruleButton->setScale(0.9f);
        ruleButton->setPosition(cocos2d::Vec2(x, y));
    }
    ruleButton_ = cocos2d::Menu::create(ruleButton, nullptr);
    this->addChild(ruleButton_, 1);
    ruleButton_->setPosition(cocos2d::Vec2::ZERO);
}

void SetScene::ruleBooksCallback(Ref* pSender)
{
    //���°�ť���л���˵����ҳ�棬����˵����ҳ�滹û�����͵Ȼ��~
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

void SetScene::initVolumeSound()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto vosoButton = cocos2d::MenuItemImage::create("Button/VolumeSound.png", "Button/VolumeSound.png", CC_CALLBACK_1(SetScene::volumeSoundCallback, this));

    if (vosoButton == nullptr ||
        vosoButton->getContentSize().width <= 0 ||
        vosoButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width * 3) / 5 - vosoButton->getContentSize().width / 3;
        float y = origin.y + (visibleSize.height * 2) / 3;
        vosoButton->setScale(0.9f);
        vosoButton->setPosition(cocos2d::Vec2(x, y));
    }
    vosoButton_ = cocos2d::Menu::create(vosoButton, nullptr);
    this->addChild(vosoButton_, 1);
    vosoButton_->setPosition(cocos2d::Vec2::ZERO);
}

void SetScene::volumeSoundCallback(Ref* pSender)
{
    //���°�ť�����ǲ��л��½��棬���ǳ���һ�������ƶ������ӣ�Ȼ��Ҳ���Թص�
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

void SetScene::initReturnMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto returnButton = cocos2d::MenuItemImage::create("Button/Return.png", "Button/Return.png", CC_CALLBACK_1(SetScene::menuReturnCallback, this));

    if (returnButton == nullptr ||
        returnButton->getContentSize().width <= 0 ||
        returnButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width * 4) / 5 - returnButton->getContentSize().width/3;
        float y = origin.y + (visibleSize.height * 2) / 3;
        returnButton->setScale(0.9f);
        returnButton->setPosition(cocos2d::Vec2(x, y));
    }
    returnButton_ = cocos2d::Menu::create(returnButton, nullptr);
    this->addChild(returnButton_, 1);
    returnButton_->setPosition(cocos2d::Vec2::ZERO);
}

void SetScene::menuReturnCallback(Ref* pSender)
{
    //���·��ذ�ť���л���menuҳ��
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}
