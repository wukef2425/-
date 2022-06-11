#ifndef __ENERGYBOX_H__
#define __ENERGYBOX_H__

#include "Entity/Player.h"

class EnergyBox :public Hero
{
private:
    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    static Hero* createBox(Vec2 position);// ����position���Ǹ�λ�����ɱ���
};

#endif