#ifndef _CHOOSEHERO_H_
#define _CHOOSEHERO_H_

#include "cocos2d.h"
#include "Scene/FightScene.h"


USING_NS_CC;
using namespace std;

class ChooseHero : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	//Ԥ����ս������
	void ChooseHero::preLoadingFightScene();
	//Ԥ���ذ�ť
	void initButton();
	//Ӣ��ѡ��ť
	void initHeroButton();
	//��ť�ص�����
	void ChooseHero::startGame(cocos2d::Ref* pSender);
	void ChooseHero::backToMenu(cocos2d::Ref* pSender);
	//Ӣ�ۻص�����
	void ChooseHero::menuShunDeCallback(cocos2d::Ref* pSender);
	void ChooseHero::menuHaoQingCallback(cocos2d::Ref* pSender);
	void ChooseHero::menuYunHeCallback(cocos2d::Ref* pSender);
	void ChooseHero::menuChangYiCallback(cocos2d::Ref* pSender);
	void ChooseHero::menuSanYueCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ChooseHero);

private:

	cocos2d::Menu* backBtn_;
	cocos2d::Menu* enterBtn_;
	cocos2d::Menu* heroButton;

	FightScene* fightScene_;
};

#endif

