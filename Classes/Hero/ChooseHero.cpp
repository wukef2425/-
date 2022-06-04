/**
* @file ChooseHero.cpp
* @author wyf
*/

#include "ChooseHero.h"
#include <map>

USING_NS_CC;
using namespace ui;
int cur_hero_index = 0;
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
	//initHeroMsg();
	preLoadingFightScene();

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);
	return true;
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

	
	//ѡ��ť
	auto leftBtn = MenuItemImage::create("Hero/ChooseHero/Button/LeftButton.png", 
		"Hero/ChooseHero/Button/LeftButton.png",
		CC_CALLBACK_1(ChooseHero::leftHero, this));

	leftBtn_ = Menu::create(leftBtn, NULL);
	leftBtn_->setPosition(Vec2(visibleSize.width / 8, visibleSize.height / 2));
	addChild(leftBtn_, 1);

	auto rightBtn = MenuItemImage::create("Hero/ChooseHero/Button/RightButton.png", 
		"Hero/ChooseHero/Button/RightButton.png",
		CC_CALLBACK_1(ChooseHero::rightHero, this));

	rightBtn_ = Menu::create(rightBtn, NULL);
	rightBtn_->setPosition(Vec2((visibleSize.width*7) / 8, visibleSize.height / 2));
	addChild(rightBtn_, 1);
	
}





/*

void ChooseHero::initHeroMsg() {
	
	loadHeroes();
	
	cur_hero_index = 0;

	hero = nullptr;

	setCurHeroMsg(0��;
}
void ChooseHero::loadHeroes() {

	map<int, HeroMessage> heroMap = HeroMessageUtil::getInstance()->getHeroMessageMap();

	for (auto it = heroMap.begin(); it != heroMap.end(); it++) {
		HeroMessage msg = (*it).second;
		HeroItem item(msg.name, msg.id, msg.r_name);
		heroArray.push_back(item);
	}
}

*/


void setCurHeroMsg(int index,int cur_hero_index)
{

	//ʵ��ѡ������ʱ��ѭ��
	if (index < 0) {
		//index = index + heroArray.size();
		index = index + 5;
	}

	//if (index >= heroArray.size()) 
	if (index >= 5) {
		//index = index - heroArray.size();
		index = index - 5;
	}

	cur_hero_index = index;

	//����ͼƬ��Ŀǰ��û���ҵ����Ը���ķ�ʽ������ѡ�񸲸�
	//auto winSize = Director::getInstance()->getVisibleSize();

	//auto* hero = Sprite::create("heroArray[cur_hero_index].r_name");
	
	//hero->setPosition(winSize.width / 2, winSize.height / 2);

	//addChild(hero, 1);

}

void ChooseHero::startGame(Ref* pSender)
{
	//fightScene_->bindPlayer(Player::create("heroArray[cur_hero_index].name"));
		
	cocos2d::Director::getInstance()->replaceScene(fightScene_->createScene());	
}

void ChooseHero::leftHero(Ref* pSender) 
{
	//setCurHeroMsg(cur_hero_index - 1);

}

void ChooseHero::rightHero(Ref* pSender) 
{
	//setCurHeroMsg(cur_hero_index + 1);
}

void ChooseHero::backToMenu(Ref* pSender)
{
	//���·��ذ�ť���л���menuҳ��
	Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

void ChooseHero::preLoadingFightScene()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* _tileMap = TMXTiledMap::create("Map/SnowMap.tmx");

	_tileMap->setPosition(origin.x - _tileMap->getContentSize().width / 2, origin.y - _tileMap->getContentSize().height / 2);

	fightScene_ = FightScene::create(_tileMap);
	//snowMap->bindPlayer(Player::create("MIKU/idle_down/idle_down1.png"));//����������û�
	fightScene_->retain();//�ȿ�����ɶ

	//AudioEngine::preload("audio/bgm_1low.mp3");//��������
}


