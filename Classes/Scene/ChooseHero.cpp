/**
* @file ChooseHero.cpp
* @author wyf
*/

#include<vector>
#include<string>
#include "ChooseHero.h"
#include "Utils/GameData.h"
#include "Scene/StartMenuScene.h"

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

	
	initButton();

	initHeroButton();

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

	fightScene_->retain();

}

void ChooseHero::initButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景图片
	auto* background = Sprite::create("Scene/HeroChooseScene.jpg");        //创建精灵类，背景图片为background.jpg
	background->setScale(1.05f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //让背景图像居中显示
	addChild(background, 0);

	//开始按钮
	auto enterBtn = MenuItemImage::create("Hero/ChooseHero/Button/Begin.png",
		"Hero/ChooseHero/Button/Begin.png",
		CC_CALLBACK_1(ChooseHero::startGame, this));
	enterBtn_ = Menu::create(enterBtn, NULL);
	enterBtn_->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5));
	addChild(enterBtn_, 1);

	//返回主菜单按钮
	auto backBtn = MenuItemImage::create("Hero/ChooseHero/Button/Back.png",
		"Hero/ChooseHero/Button/Back.png",
		CC_CALLBACK_1(ChooseHero::backToMenu, this));

	backBtn_ = Menu::create(backBtn, NULL);
	backBtn_->setPosition(Vec2((visibleSize.width * 8) / 9, (visibleSize.height * 8) / 9));
	addChild(backBtn_, 1);	
}

void ChooseHero::initHeroButton()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
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

	Menu* menu = Menu::createWithArray(HeroMenuVector);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void ChooseHero::startGame(Ref* pSender)
{
	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);
	preLoadingFightScene();

	cocos2d::Director::getInstance()->replaceScene(fightScene_->createScene());
}

void ChooseHero::backToMenu(Ref* pSender)
{
	Director::getInstance()->replaceScene(StartMenuScene::createScene());
}
/******************************************************Hero************************************************************/

void ChooseHero::menuShunDeCallback(cocos2d::Ref* pSender)
{
	GameData::ChangeHeroToShunDe();
}

void ChooseHero::menuHaoQingCallback(cocos2d::Ref* pSender)
{
	GameData::ChangeHeroToHaoQing();
}

void ChooseHero::menuYunHeCallback(cocos2d::Ref* pSender)
{
	
	GameData::ChangeHeroToYunHe();
}

void ChooseHero::menuChangYiCallback(cocos2d::Ref* pSender)
{
	GameData::ChangeHeroToChangYi();
}

void ChooseHero::menuSanYueCallback(cocos2d::Ref* pSender)
{
	
	GameData::ChangeHeroToSanYue();
}

