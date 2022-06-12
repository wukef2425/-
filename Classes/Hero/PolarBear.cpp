/**
* @file PolarBear.cpp
* @author wukef
*/

#include "PolarBear.h"
#include "Consts.h"
#include "Entity/AI.h"

Hero* PolarBear::createAI()
{
    auto player = AI::create("Hero/FightHero/polar-bear.png");

    player->health_ = 100;//��ǰ����

    player->healthInit_ = 100;//�������

    player->attack_ = 20;//����ֵ

    player->defend_ = 8;//����ֵ

    return player;
}