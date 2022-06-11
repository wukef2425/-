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

    player->health_ = 100;//��ǰ����

    player->healthInit_ = 100;//�������

    player->attack_ = 25;//����ֵ

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
    auto player = new(std::nothrow) PolarBear;

    if (player == nullptr)
    {
        return nullptr;
    }

    player->health_ = 100;//��ǰ����

    player->healthInit_ = 100;//�������

    player->attack_ = 20;//����ֵ

    player->defend_ = 10;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/polar-bear.png");

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