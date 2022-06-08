/**
* @file ChooseHero.cpp
* @author wyf
*/

#include "ChooseHero.h"
#include<vector>
#include<string>
using namespace std;
USING_NS_CC;


Scene* ChooseHero::createScene()
{
	return ChooseHero::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool ChooseHero::init()
{
	if (!Scene::init())
	{
		return false;
	}

	preLoadingFightScene();

	initButton();

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);
	return true;
}

void ChooseHero::preLoadingFightScene()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* _tileMap = TMXTiledMap::create("Map/SnowMap.tmx");

	_tileMap->setPosition(origin.x - _tileMap->getContentSize().width / 2, origin.y - _tileMap->getContentSize().height / 2);

	fightScene_ = FightScene::create(_tileMap);

	fightScene_->retain();//�ȿ�����ɶ

	//AudioEngine::preload("audio/bgm_1low.mp3");//��������
}

void ChooseHero::initButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto* background = Sprite::create("Scene/HeroChooseScene.jpg");        //���������࣬����ͼƬΪbackground.jpg
	background->setScale(1.05f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //�ñ���ͼ�������ʾ
	addChild(background, 0);

	//��ʼ��ť
	auto enterBtn = MenuItemImage::create("Hero/ChooseHero/Button/Begin.png",
		"Hero/ChooseHero/Button/Begin.png",
		CC_CALLBACK_1(ChooseHero::startGame, this));
	enterBtn_ = Menu::create(enterBtn, NULL);
	enterBtn_->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5));
	addChild(enterBtn_, 1);

	//�������˵���ť
	auto backBtn = MenuItemImage::create("Hero/ChooseHero/Button/Back.png",
		"Hero/ChooseHero/Button/Back.png",
		CC_CALLBACK_1(ChooseHero::backToMenu, this));

	backBtn_ = Menu::create(backBtn, NULL);
	backBtn_->setPosition(Vec2((visibleSize.width * 8) / 9, (visibleSize.height * 8) / 9));
	addChild(backBtn_, 1);

	//Ӣ��ѡ��ť����ȡͳһ�ķ�ʽ������ѡ��

	Vector<MenuItem*> HeroMenuVector;

	vector<string> NameMenuVector = { "ShunDe","ChangYi","YunHe", "HaoQing","SanYue" };

	vector<void (ChooseHero::*)(Ref* pSender)> CallbackVector = {
		&ChooseHero::menuShunDeCallback,
		&ChooseHero::menuChangYiCallback,
		&ChooseHero::menuYunHeCallback,
		&ChooseHero::menuHaoQingCallback,
		&ChooseHero::menuSanYueCallback };

	vector<Vec2> PositionVector = {
		Vec2(visibleSize.width / 6 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(2 * visibleSize.width / 6 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(3 * visibleSize.width / 6 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(4 * visibleSize.width / 6 + origin.x, visibleSize.height / 2 + origin.y),
		Vec2(5 * visibleSize.width / 6 + origin.x, visibleSize.height / 2 + origin.y), };

	//���������ť��������Ϣ������Vector
	for (int i = 0; i < NameMenuVector.size(); i++)
	{
		MenuItem* heroButton = MenuItemImage::create("Hero/ChooseHero/" + NameMenuVector.at(i) + "Before.jpg",
			"Hero/ChooseHero/" + NameMenuVector.at(i) + "After.jpg",
			bind(CallbackVector.at(i), this, std::placeholders::_1));

		if (heroButton == nullptr || heroButton->getContentSize().width <= 0 || heroButton->getContentSize().height <= 0)
		{
			problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
		}
		else
		{
			heroButton->setPosition(PositionVector.at(i));
		}
		HeroMenuVector.pushBack(heroButton);
	}

	//���������ݷ���menu��
	Menu* menu = Menu::createWithArray(HeroMenuVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void ChooseHero::startGame(Ref* pSender)
{
	//fightScene_->bindPlayer(Player::create("heroArray[cur_hero_index].name"));

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	cocos2d::Director::getInstance()->replaceScene(fightScene_->createScene());
}

void ChooseHero::backToMenu(Ref* pSender)
{
	//���·��ذ�ť���л���menuҳ��
	Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

//˳��
void ChooseHero::menuShunDeCallback(cocos2d::Ref* pSender)
{
	
	FightUtils::_hero = FightUtils::AllHero::ShunDe;

}

//���
void ChooseHero::menuHaoQingCallback(cocos2d::Ref* pSender)
{
	FightUtils::_hero = FightUtils::AllHero::HaoQing;
}

//�ƺ�
void ChooseHero::menuYunHeCallback(cocos2d::Ref* pSender)
{
	
	FightUtils::_hero = FightUtils::AllHero::YunHe;
}

//����
void ChooseHero::menuChangYiCallback(cocos2d::Ref* pSender)
{
	FightUtils::_hero = FightUtils::AllHero::ChangYi;
}


//����
void ChooseHero::menuSanYueCallback(cocos2d::Ref* pSender)
{
	FightUtils::_hero = FightUtils::AllHero::SanYue;
}
