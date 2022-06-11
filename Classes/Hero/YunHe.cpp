#include "YunHe.h"
#include "Consts.h"

YunHe* YunHe::createPlayer()
{
    auto player = new(std::nothrow) YunHe;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = YunHeHealthInit;//��ǰ����

    player->healthInit_ = YunHeHealthInit;//�������

    player->attack_ = YunHeAttack;//����ֵ

    player->defend_ = YunHeDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/YunHe.png");

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

Hero* YunHe::createAI()
{
    auto player = new(std::nothrow) YunHe;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = YunHeHealthInit;//��ǰ����

    player->healthInit_ = YunHeHealthInit;//�������

    player->attack_ = YunHeAttack;//����ֵ

    player->defend_ = YunHeDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/FightHero/YunHe.png");

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

void YunHe::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/YunHe-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    auto physicsBody = PhysicsBody::createBox(useSkill->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(PlayerBulletAndEnemyBitmask);// bitmask����ײ��body���� ��һ������������
    physicsBody->setContactTestBitmask(PlayerBulletAndEnemyBitmask);// ��һ���������������ײ��ʱ��֪ͨ
    useSkill->setPhysicsBody(physicsBody);
    useSkill->setTag(YunHeUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}