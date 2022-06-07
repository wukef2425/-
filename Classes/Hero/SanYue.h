#pragma once
#ifndef __SANYUE_H__
#define __SANYUE_H__

#include "Hero/Player.h"

class SanYue :public Player
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static SanYue* createPlayer();

    static Hero* createAI();
};

#endif