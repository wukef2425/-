#include "HaoQing.h"
#include "Consts.h"

HaoQing* HaoQing::createPlayer()
{
    auto player = new(std::nothrow) HaoQing;

    if (!player)
    {
        return nullptr;
    }
    player->dieTag_ = PlayerDieTag;

    player->health_ = HaoQingHealthInit;//��ǰ����

    player->healthInit_ = HaoQingHealthInit;//�������

    player->attack_ = HaoQingAttack;//����ֵ

    player->defend_ = HaoQingDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/HaoQing.png");

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

Hero* HaoQing::createAI()
{
    auto player = new(std::nothrow) HaoQing;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = HaoQingHealthInit;//��ǰ����

    player->healthInit_ = HaoQingHealthInit;//�������

    player->attack_ = HaoQingAttack;//����ֵ

    player->defend_ = HaoQingDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/HaoQing.png");

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

void HaoQing::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/HaoQing-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}