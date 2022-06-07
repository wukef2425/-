#pragma once
#ifndef __CHANGYI_H__
#define __CHANGYI_H__

#include "Hero/Player.h"

class ChangYi :public Player
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static ChangYi* createPlayer();

    static Hero* createAI();
};

#endif