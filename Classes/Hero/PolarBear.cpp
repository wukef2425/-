/**
* @file PolarBear.cpp
* @author wukef
*/

#include "PolarBear.h"
#include "Consts.h"

PolarBear* PolarBear::createPlayer()
{
    auto player = new(std::nothrow) PolarBear;

    if (!player)
    {
        return nullptr;
    }

    player->isAlive_ = true;//�Ƿ���

    player->health_ = 100;//��ǰ����

    player->bullet_ = 3;//��ǰ��ҩ

    player->maxHealth_ = 100;//�������

    player->attack_ = 35;//����ֵ

    player->defend_ = 10;//����ֵ

    player->energy_ = 1;//�����Ժ�����������

    auto chosenHero = Sprite::create("Hero/polar-bear.png");

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
    auto player = new(std::nothrow) PolarBear;

    if (!player)
    {
        return nullptr;
    }

    player->isAlive_ = true;//�Ƿ���

    player->health_ = 100;//��ǰ����

    player->bullet_ = 3;//��ǰ��ҩ

    player->maxHealth_ = 100;//�������

    player->attack_ = 35;//����ֵ

    player->defend_ = 0;//����ֵ

    player->energy_ = 1;//�����Ժ�����������

    auto chosenHero = Sprite::create("Hero/polar-bear.png");

    if (chosenHero)
    {
        player->setPosition(0, 0);

        player->bindPhysicsBodyAndTag(chosenHero, PlayerBulletAndEnemyBitmask, EnemyTag);

        player->addChild(chosenHero);

        player->autorelease();

        return player;
    }

    return nullptr;
}