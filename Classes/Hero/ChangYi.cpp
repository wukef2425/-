#include "ChangYi.h"
#include "Consts.h"
#include "Entity/AI.h"

Hero* ChangYi::createAI()
{
    auto player = AI::create("Hero/FightHero/ChangYi.png");

    player->health_ = ChangYiHealthInit;//��ǰ����

    player->healthInit_ = ChangYiHealthInit;//�������

    player->attack_ = ChangYiAttack;//����ֵ

    player->defend_ = ChangYiDefend;//����ֵ

    return player;
}

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

void ChangYi::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/ChangYi-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    Hero::bindPhysicsBodyAndTag(useSkill, EnemyBulletAndPlayerBitmask, ChangYiUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}

void ChangYi::attackHero(Vec2 playerPosition,Vec2 touchWorldPosition)
{
    /* ����currentBullet�����ó�ʼλ�� */
    auto currentBullet = Sprite::create("Hero/Bullet/ChangYi-bullet-usual.png");
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