#include "Gamepause.h"

USING_NS_CC;
#include "FightScene.h"
#include "Scene/ChooseHero.h"
#include "Scene/StartMenuScene.h"

Scene* Gamepause::scene(RenderTexture* sqr)
{

	Scene* scene = Scene::create();
	Gamepause* layer = Gamepause::create();
	scene->addChild(layer, 1);
	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
  //����Sprite��ӵ�GamePause��������
  //�õ����ڵĴ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
	back_spr->setFlippedY(true);            //��ת����ΪUI�����OpenGL���겻ͬ
	back_spr->setColor(Color3B::GRAY); //ͼƬ��ɫ���ɫ
	scene->addChild(back_spr);
	return scene;
}

bool Gamepause::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//ͼƬ���
	auto* background = Sprite::create("Button/pause_background.png");
	background->setScale(1.2f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2+50);
	addChild(background, 1);
	
	//������Ϸ��ť
	auto pContinueItem = cocos2d::MenuItemImage::create(
		"Button/pause_continue.png",
		"Button/pause_continue.png",
		CC_CALLBACK_1(Gamepause::menuContinueCallback, this));

	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-50));

	pMenu = cocos2d::Menu::create(pContinueItem, nullptr);
	pMenu->setScale(1.6f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);


	//���¿�ʼ��Ϸ��ť
	auto pRestartItem = cocos2d::MenuItemImage::create(
		"Button/pause_restart.png",
		"Button/pause_restart.png",
		CC_CALLBACK_1(Gamepause::menuRestartCallback, this));

	pRestartItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


	pMenu = cocos2d::Menu::create(pRestartItem, nullptr);
	pMenu->setScale(1.6f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);

	//��������
	auto pLoginItem = cocos2d::MenuItemImage::create(
		"Button/pause_login.png",
		"Button/pause_login.png",
		CC_CALLBACK_1(Gamepause::menuLoginCallback, this));

	pLoginItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+50));


	pMenu = cocos2d::Menu::create(pLoginItem, nullptr);
	pMenu->setScale(1.6f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);

	return true;
}
//������Ϸ
void Gamepause::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->popScene();

}
//���¿�ʼ��Ϸ
void Gamepause::menuRestartCallback(Ref* pSender)
{
	GameData::resetPlayerNum();
	Director::getInstance()->replaceScene(ChooseHero::createScene());
}
//��������
void Gamepause::menuLoginCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

