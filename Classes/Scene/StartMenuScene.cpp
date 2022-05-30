/**
*@file StartMenuScene.cpp
* @author wyf
*/
#include "StartMenuScene.h"
#include "SetScene.h"
#include "FightScene.h"
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

	//����С���
	initDecoration();//һЩ�û������۵Ķ���
	initSetButton();//���ý��棬�����й���˵��/��������/����ԭ������
	initUserButton();//�û���Ϣ�鿴����
	initStartButton();//��ʼ��ť
	initOnlineButton();//������ʼ��ť
	initExitButton();//�뿪��ť
	//loadingFightScene();//������ͼ����,��̫������ΪʲôҪ��ǰ���غã�������ȥ�˽����ټ���

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);//API���ýӿڣ�Ŀǰ��Ҳ������

	return true;
}

void StartMenuScene::initDecoration()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto* background = Sprite::create("Scene/MenuScene.jpg");        //���������࣬����ͼƬΪbackground.jpg
	background->setScale(1.05f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //�ñ���ͼ�������ʾ
	addChild(background, 0);
	//��������Ф��
	auto* character = Sprite::create("StarMenuCuteHe.png");
	character->setPosition(origin.x + (character->getContentSize().width * 4) / 5, origin.y + (character->getContentSize().height * 2) / 5);        //�ñ���ͼ�������ʾ
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
	//fightScene_->settingLayer_->backgroundMusicID_ = cocos2d::AudioEngine::play2d("audio/bgm_1low.mp3", true, .5);
	//����һ���������֣�Ŀǰ���ǻ��ǲ��Ӱ�
	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	//Director::getInstance()->replaceScene(FightScene::createScene());
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

	auto userButton = cocos2d::MenuItemImage::create("UserYunHe.png", "UserYunHe.png", CC_CALLBACK_1(StartMenuScene::startCallback, this));
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
	//Director::getInstance()->replaceScene(UserInfo::createScene());
}

/*�����ΪʲôҪ��ǰ���ض����Ǵ��½���֮���ټ��أ������ɴ򿪽�����ټ���
void StartMenuScene::loadingFightScene()
{
	auto snowMap= TMXTiledMap::create("Map/SnowMap.tmx");
	snowMap->setPosition(Vec2(0, 0));//λ�û���Ҫ�ٴ�ȷ��һ��o
	addChild(snowMap);

	snowMap = FightScene::create(_tileMap1, _tileMap2, _tileMap3, Obstacle::createObsSet(1), 1);//��ӵ�ͼ�Լ��ϰ���
	snowMap->bindPlayer(Player::create("MIKU/idle_down/idle_down1.png"));//����������û�
	snowMap->retain();//�ȿ�����ɶ

	//AudioEngine::preload("audio/bgm_1low.mp3");//��������
}*/

/*void StartMenuScene::loadingFightScene()
{
	auto _tileMap1 = TMXTiledMap::create("map/map_1/map/bottomMap.tmx");//�����������Ƭ��ͼ�Ĳ���Ŷ
	_tileMap1->setPosition(Vec2(0, 0));

	auto _tileMap2 = TMXTiledMap::create("map/map_1/map/middleMap.tmx");
	_tileMap2->setPosition(Vec2(0, 50 * 32));

	auto _tileMap3 = TMXTiledMap::create("map/map_1/map/topMap.tmx");
	_tileMap3->setPosition(Vec2(0, 100 * 32));
	//ѧ���ǰ���Ƭ��ͼ��Ϊ�����������أ��������볡����ʱ��Ҳ�������������
	fightScene_ = FightScene::create(_tileMap1, _tileMap2, _tileMap3, Obstacle::createObsSet(1), 1);//��ӵ�ͼ�Լ��ϰ���
	fightScene_->bindPlayer(Player::create("MIKU/idle_down/idle_down1.png"));//����������û�
	fightScene_->retain();//�ȿ�����ɶ


	AudioEngine::preload("audio/bgm_1low.mp3");//��������
}*/

