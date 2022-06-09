#pragma once
#ifndef __SHUNDE_H__
#define __SHUNDE_H__

#include "Hero/Player.h"

class ShunDe :public Player
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static ShunDe* createPlayer();

    static Hero* createAI();

    void ultimateSkill() override;
};

#endif