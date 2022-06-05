/**
* @file PolarBear.h
* @author wukef
*/

#ifndef __POLAR_BEAR_H__
#define __POLAR_BEAR_H__

#include "Hero/Player.h"

class PolarBear :public Player
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

	static PolarBear* createPlayer();

    static Hero* createAI();
};

#endif
