#pragma once
#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"

class StartMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void StartMenuScene::initDecoration();//һЩ�û������۵Ĳ��

	void StartMenuScene::initSetButton();//���ð�ť

	void StartMenuScene::setCallback(cocos2d::Ref* pSender);

	void StartMenuScene::initUserButton();//�û���Ϣ�鿴��ť

	void StartMenuScene::userCallback(cocos2d::Ref* pSender);

	void StartMenuScene::initStartButton();//��ͨ��ʼ��ť

	void StartMenuScene::initOnlineButton();//������ʼ��ť

	void StartMenuScene::startCallback(cocos2d::Ref* pSender);

	void StartMenuScene::initExitButton();//�뿪��ť

	void StartMenuScene::exitCallback(cocos2d::Ref* pSender);

	//void StartMenuScene::loadingFightScene();//��ͼ���ع���,һֱ�㲻��Ϊɶ����ֱ�Ӽ���

	CREATE_FUNC(StartMenuScene);

protected:

	cocos2d::Menu* startButton_;

	cocos2d::Menu* onlineButton_;

	cocos2d::Menu* exitButton_;

	cocos2d::Menu* setButton_;

	cocos2d::Menu* userButton_;


};

#endif // __STARTMENU_SCENE_H__