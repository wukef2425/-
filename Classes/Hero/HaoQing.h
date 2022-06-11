#pragma once
#ifndef __HAOQING_H__
#define __HAOQING_H__

#include "Entity/Player.h"

class HaoQing :public Player
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static HaoQing* createPlayer();

    static Hero* createAI();

    void ultimateSkill(Vec2 touchWorldPosition) override;
};

#endif