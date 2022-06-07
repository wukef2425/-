#pragma once
#ifndef __YUNHE_H__
#define __YUNHE_H__

#include "Hero/Player.h"

class YunHe :public Player
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static YunHe* createPlayer();

    static Hero* createAI();
};

#endif