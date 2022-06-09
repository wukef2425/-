#include "ShunDe.h"
#include "Consts.h"

ShunDe* ShunDe::createPlayer()
{
    auto player = new(std::nothrow) ShunDe;

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

    auto chosenHero = Sprite::create("Hero/FightHero/ShunDe.png");

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

Hero* ShunDe::createAI()
{
    auto player = new(std::nothrow) ShunDe;

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

    auto chosenHero = Sprite::create("Hero/FightHero/ShunDe.png");

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

void ShunDe::ultimateSkill()
{
    auto skill = Sprite::create("Hero/FightHero/polar-bear.png");

    skill->setPosition(this->getPosition());

    this->getParent()->addChild(skill);
}