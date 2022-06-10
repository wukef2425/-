/**
*@file StartMenuScene.cpp
* @author wyf
*/

#include "cocos2d.h"
#include "StartMenuScene.h"
#include "Scene/SetScene.h"
#include "Scene/ChooseHero.h"
#include "User/UserInfo.h"

USING_NS_CC;

Scene* StartMenuScene::createScene()
{
	return StartMenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	/*��¼��������Ҫ�п�ʼ��Ϸ/������ʼ��Ϸ/���ã�������˵���飬���أ�
	/�û����棨��Ҫ�ǲ鿴���������������ǣ�/����Ҫ��Ҫ�Ӹ�Ӣ�۽��ܽ��棨ûɶ����Ҫ�Ǻÿ���
	�󲿷��Ѿ���ƺã�������������ֻ�û����ɣ�����������Ϸ��¼�йأ��ȷ��Ű�*/

	initDecoration();
	initSetButton();
	initUserButton();
	initStartButton();
	initOnlineButton();
	initExitButton();

	/*to zyy ��������뱳�����ֽ��棬��һ��������Ҫ���ֵķ�Χ���ڵ�¼���漰���ܹ�����Ľ��棨���á��û���
	Ȼ�������ý����п��Կ��������Ĵ�С�Լ��Ƿ񲥷����֣������Ҫ�����Ļ�˽����һ����
	����ս������Ļ��������֣�����Ҫ�ǱȽ��鷳�Ļ����Ȳ���Ҳ��*/

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	return true;
}

void StartMenuScene::initDecoration()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//background
	auto* background = Sprite::create("Scene/MenuScene.jpg");       
	background->setScale(1.05f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);       
	addChild(background, 0);
	//decoration
	auto* character = Sprite::create("StarMenuCuteHe.png");
	character->setPosition(origin.x + (character->getContentSize().width * 4) / 5, origin.y + (character->getContentSize().height * 2) / 5);      
	addChild(character, 1);
}

void StartMenuScene::initStartButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startButton = cocos2d::MenuItemImage::create("Button/Start.png", "Button/Start.png", CC_CALLBACK_1(StartMenuScene::startCallback, this));

	if (startButton == nullptr ||
		startButton->getContentSize().width <= 0 ||
		startButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - startButton->getContentSize().width;
		float y = origin.y + startButton->getContentSize().height * 3;
		startButton->setScale(1.3f);
		startButton->setPosition(cocos2d::Vec2(x, y));
	}
	startButton_ = cocos2d::Menu::create(startButton, nullptr);
	this->addChild(startButton_, 1);
	startButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::startCallback(cocos2d::Ref* pSender)
{

	//to zyy ����Ƚ���ˮ�߲����Ļ����Ը������ť���Ӹ���Ч��λ�ö�����replaceǰ���Եø߼�

	//switch to chooseHeroScene
	
	Director::getInstance()->replaceScene(ChooseHero::createScene());

}

void StartMenuScene::initOnlineButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto onlineButton = cocos2d::MenuItemImage::create("Button/OnlineStart.png", "Button/OnlineStart.png", CC_CALLBACK_1(StartMenuScene::startCallback, this));

	if (onlineButton == nullptr ||
		onlineButton->getContentSize().width <= 0 ||
		onlineButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - onlineButton->getContentSize().width;
		float y = origin.y + onlineButton->getContentSize().height * 2;
		onlineButton->setScale(1.3f);
		onlineButton->setPosition(cocos2d::Vec2(x, y));
	}

	onlineButton_ = cocos2d::Menu::create(onlineButton, nullptr);
	this->addChild(onlineButton_, 1);
	onlineButton_->setPosition(cocos2d::Vec2::ZERO);
}

/*Ŀǰ��������������״̬Ҫ���ǵĶ���
void StartMenuScene::startOnlineCallback(cocos2d::Ref* pSender)
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	auto label = cocos2d::Label::createWithTTF("Connecting to Server...", "fonts/IRANYekanBold.ttf", 36);
	label->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label->setPosition(winSize / 2);
	label->enableOutline(cocos2d::Color4B(194, 69, 69, 255), 5);
	auto remove = cocos2d::RemoveSelf::create();
	auto delay = cocos2d::DelayTime::create(.1f);
	auto fade2 = cocos2d::FadeTo::create(1, 0);

	auto connect = cocos2d::CallFunc::create([=]() {
		Client::getInstance()->initialization();
		Client::getInstance()->Send("Join");
		cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(false);
		goToFightScene();
		});
	label->runAction(cocos2d::Sequence::create(delay, connect, fade2, remove, nullptr));
	addChild(label, 3);
}*/

void StartMenuScene::initExitButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto exitBotton = cocos2d::MenuItemImage::create("Button/Leave.png", "Button/Leave.png", CC_CALLBACK_1(StartMenuScene::exitCallback, this));
	if (exitBotton == nullptr ||
		exitBotton->getContentSize().width <= 0 ||
		exitBotton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - exitBotton->getContentSize().width;
		float y = origin.y + exitBotton->getContentSize().height;
		exitBotton->setScale(1.3f);
		exitBotton->setPosition(cocos2d::Vec2(x, y));
	}

	exitButton_ = cocos2d::Menu::create(exitBotton, nullptr);
	this->addChild(exitButton_, 1);
	exitButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::exitCallback(cocos2d::Ref* pSender)
{
	//Client::clientRelease();//Ҳ����������ڴ����˼������

	Director::getInstance()->end();
}

void StartMenuScene::initSetButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto setButton = MenuItemImage::create(
		"SetButton.png",
		"SetButton.png",
		CC_CALLBACK_1(StartMenuScene::setCallback, this));

	if (setButton == nullptr ||
		setButton->getContentSize().width <= 0 ||
		setButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - setButton->getContentSize().width;
		float y = visibleSize.height - setButton->getContentSize().height;
		setButton->setPosition(cocos2d::Vec2(x, y));
	}
	setButton_ = cocos2d::Menu::create(setButton, nullptr);
	this->addChild(setButton_, 1);
	setButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::setCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(SetScene::createScene());
}

void StartMenuScene::initUserButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto userButton = cocos2d::MenuItemImage::create("UserYunHe.png", "UserYunHe.png", CC_CALLBACK_1(StartMenuScene::userCallback, this));
	//����ͷ����ĳɶ�̬�ģ���ʱ�򿴿��в���
	if (userButton == nullptr ||
		userButton->getContentSize().width <= 0 ||
		userButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + userButton->getContentSize().width;
		float y = visibleSize.height - userButton->getContentSize().height;
		userButton->setScale(1.3f);
		userButton->setPosition(cocos2d::Vec2(x, y));
	}

	userButton_ = cocos2d::Menu::create(userButton, nullptr);
	this->addChild(userButton_, 1);
	userButton_->setPosition(cocos2d::Vec2::ZERO);
	//�����û���Ϣ�򣬿�����ʾ�û����ǳƺ͵ȼ���Ҳ�Ƕ�̬�Ŀ��Ըĵ�
}

void StartMenuScene::userCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(UserInfo::createScene());
}









