#include "SanYue.h"
#include "Consts.h"
#include "Entity/AI.h"

Hero* SanYue::createAI()
{
    auto player = AI::create("Hero/FightHero/SanYue.png");

    player->health_ = SanYueHealthInit;//��ǰ����

    player->healthInit_ = SanYueHealthInit;//�������

    player->attack_ = SanYueAttack;//����ֵ

    player->defend_ = SanYueDefend;//����ֵ

    return player;
}

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

void SanYue::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/SanYue-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    Hero::bindPhysicsBodyAndTag(useSkill, EnemyBulletAndPlayerBitmask, SanYueUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}

void SanYue::attackHero(Vec2 playerPosition, Vec2 touchWorldPosition)
{
    /* ����currentBullet�����ó�ʼλ�� */
    auto currentBullet = Sprite::create("Hero/Bullet/SanYue-bullet-usual.png");// ��Ϊ�ӵ��Ǵ�һ��ɾһ���ģ�����ֻ�ܷ���onTouchBegan�ڲ�
    currentBullet->setPosition(playerPosition);// ��ʼλ���Ǵ�currentPlayer����

    /* ��currentBullet���������� */
    Hero::bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

    /* ������Ⱦ�� */
    this->getParent()->addChild(currentBullet);

    Vec2 offset = touchWorldPosition - playerPosition;
    offset.normalize();// currentPlayerλ��ָ�����touchλ�õĵ�λ����

    /* ����һЩ���� */
    auto actionMove = MoveBy::create(1.5f, offset * ShootSpeed);// 1.5�뵽��Ŀ�ĵ�
    auto actionRemove = RemoveSelf::create();// ɾ������

    /* ��currentBullet��������һϵ�ж��� */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}