#include "SanYue.h"
#include "Consts.h"

SanYue* SanYue::createPlayer()
{
    auto player = new(std::nothrow) SanYue;

    if (!player)
    {
        return nullptr;
    }
    player->dieTag_ = PlayerDieTag;

    player->health_ = SanYueHealthInit;//��ǰ����

    player->healthInit_ = SanYueHealthInit;//�������

    player->attack_ = SanYueAttack;//����ֵ

    player->defend_ = SanYueDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/SanYue.png");

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

Hero* SanYue::createAI()
{
    auto player = new(std::nothrow) SanYue;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = SanYueHealthInit;//��ǰ����

    player->healthInit_ = SanYueHealthInit;//�������

    player->attack_ = SanYueAttack;//����ֵ

    player->defend_ = SanYueDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/SanYue.png");

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

void SanYue::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/SanYue-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}