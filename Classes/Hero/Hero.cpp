/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"

bool Hero::isAlive()
{
	return isAlive_;
}

void Hero::die()
{
	isAlive_ = false;
}

void Hero::receiveDamage(int damage)
{

	health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		die();
	}
}

void Hero::dealDamage(int damage)
{
	;
}

void Hero::ultimateSkill(int damage)
{
	;
}

void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// �����ã�����ᱻ�ͷŵ�
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize()/10, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask����ײ��body���� ��һ������������
	physicsBody->setContactTestBitmask(bitmask);// ��һ���������������ײ��ʱ��֪ͨ
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}