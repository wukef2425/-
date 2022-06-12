#include "HaoQing.h"
#include "Consts.h"
#include "Entity/AI.h"

Hero* HaoQing::createAI()
{
    auto player = AI::create("Hero/FightHero/HaoQing.png");

    player->health_ = HaoQingHealthInit;//��ǰ����

    player->healthInit_ = HaoQingHealthInit;//�������

    player->attack_ = HaoQingAttack;//����ֵ

    player->defend_ = HaoQingDefend;//����ֵ

    return player;
}

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

void HaoQing::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/HaoQing-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    Hero::bindPhysicsBodyAndTag(useSkill, EnemyBulletAndPlayerBitmask, HaoQingUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// �����ͷ����confirm_��ԭ
}

void HaoQing::attackHero(Vec2 playerPosition, Vec2 touchWorldPosition)
{
    /* ����currentBullet�����ó�ʼλ�� */
    auto currentBullet = Sprite::create("Hero/Bullet/HaoQing-bullet-usual.png");// ��Ϊ�ӵ��Ǵ�һ��ɾһ���ģ�����ֻ�ܷ���onTouchBegan�ڲ�
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