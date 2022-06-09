/**
* @file PolarBear.cpp
* @author wukef
*/

#include "PolarBear.h"
#include "Consts.h"

PolarBear* PolarBear::createPlayer()
{
    auto player = new(std::nothrow) PolarBear;

    if (player == nullptr)
    {
        return nullptr;
    }

    player->isAlive_ = true;//�Ƿ���

    player->health_ = 100;//��ǰ����

    player->bullet_ = 3;//��ǰ��ҩ

    player->maxHealth_ = 100;//�������

    player->attack_ = 35;//����ֵ

    player->defend_ = 10;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/polar-bear.png");

    if (chosenHero)
    {
        player->setPosition(player->x, player->y);// player��ʼ����(x,y)���ݴ��ڴ�С ��protected�����

        player->bindPhysicsBodyAndTag(chosenHero, EnemyBulletAndPlayerBitmask, PlayerTag);

        player->addChild(chosenHero);

        player->autorelease();

        return player;
    }

    return nullptr;
}

Hero* PolarBear::createAI()
{
    auto AI = new(std::nothrow) PolarBear;

    if (AI == nullptr)
    {
        return nullptr;
    }

    AI->isAlive_ = true;//�Ƿ���

    AI->health_ = 100;//��ǰ����

    AI->bullet_ = 3;//��ǰ��ҩ

    AI->maxHealth_ = 100;//�������

    AI->attack_ = 35;//����ֵ

    AI->defend_ =10;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/polar-bear.png");

    if (chosenHero)
    {
        AI->setPosition(0, 0);

        AI->bindPhysicsBodyAndTag(chosenHero, PlayerBulletAndEnemyBitmask, EnemyTag);

        AI->addChild(chosenHero);

        AI->autorelease();

        return AI;
    }

    return nullptr;
}