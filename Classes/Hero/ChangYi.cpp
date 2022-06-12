#include "ChangYi.h"
#include "Consts.h"

/*������Ҫ�����Ļ��������У�����Ĺ�����ʽ������ĸ������ԣ�����Ĵ���*/
ChangYi* ChangYi::createPlayer()
{
    auto player = new(std::nothrow) ChangYi;

    if (!player)
    {
        return nullptr;
    }
    player->dieTag_ = PlayerDieTag;

    player->health_ = ChangYiHealthInit;//��ǰ����

    player->healthInit_ = ChangYiHealthInit;//�������

    player->attack_ = ChangYiAttack;//����ֵ

    player->defend_ = ChangYiDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/ChangYi.png");

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

Hero* ChangYi::createAI()
{
    auto player = new(std::nothrow) ChangYi;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = ChangYiHealthInit;//��ǰ����

    player->healthInit_ = ChangYiHealthInit;//�������

    player->attack_ = ChangYiAttack;//����ֵ

    player->defend_ = ChangYiDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/ChangYi.png");

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

void ChangYi::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/ChangYi-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    Hero::bindPhysicsBodyAndTag(useSkill, PlayerBulletAndEnemyBitmask, ChangYiUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}