/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"
#include "Consts.h"

bool Hero::isUltimateSkillReady()
{
	return ultimateProgress_;
}

bool Hero::isAlive()
{
	return isAlive_;
}

void Hero::receiveDamage(int damage, Hero*& sprite)
{

	health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		// �������������������getPosition��ʧЧ������map������
		auto energy = cocos2d::Sprite::create("Hero/energy.png");
		energy->setPosition(sprite->getPosition());
		sprite->getParent()->addChild(energy);

		isAlive_ = false;
	}
	//auto blink = cocos2d::Blink::create(0.5f, 3);// �и��ʳ��ִ����˻����ӵ���bug����
	//sprite->runAction(blink);
}

void Hero::dealDamage(int damage)
{
	;
}

void Hero::ultimateSkill()
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