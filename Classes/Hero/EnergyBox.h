#ifndef __ENERGYBOX_H__
#define __ENERGYBOX_H__

#include "Entity/Player.h"

class EnergyBox :public Hero
{
public:

    static Hero* createBox(Vec2 position);// ����position���Ǹ�λ�����ɱ���
};

#endif