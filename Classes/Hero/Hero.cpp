/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"
#include "Consts.h"
#include "Scene/FightScene.h"


/******************************************����״̬*************************************************/

/* �Ƿ��� */
bool Hero::isAlive()
{
	return isAlive_;
}
/* killerʹinjuredSprite�ܵ�damage���˺� */
void Hero::receiveDamage(int damage, Hero*& injuredSprite, Hero*& killer)
{
	injuredSprite->health_ -= (damage - defend_);// �������ƺ���̫��35�Ĺ�����һ�¾����ˣ�

	killer->chargeForUlitmateSkill(damage - injuredSprite->defend_);

	if (health_ <= 0)
	{ 
		die(injuredSprite, killer);
		injuredSprite->getParent()->unschedule(CC_SCHEDULE_SELECTOR(FightScene::createAI));
		injuredSprite->removeFromParentAndCleanup(true);
	}
}
/* killerɱ����diedSprite */
void Hero::die(Hero*& diedSprite, Hero*& killer)
{
	auto energy = Hero::createEnergy(diedSprite, killer);

	diedSprite->getParent()->addChild(energy);

	isAlive_ = false;
}
/* energyGenerator����������energyReceiver */
Hero* Hero::createEnergy(Hero*& energyGenerator, Hero*& energyReceiver)
{
	auto energy = new(std::nothrow) Hero;

	if (energy == nullptr)
	{
		return nullptr;
	}

	auto tmp = Sprite::create("Hero/energy.png");

	if (tmp != nullptr)
	{
		//energy->bindPhysicsBodyAndTag(tmp, EnemyBulletAndPlayerBitmask, PlayerTag);// ������������position����

		energy->setPosition(energyGenerator->getPosition());

		energy->addChild(tmp);

		auto moveTo = MoveTo::create(0.1f, energyReceiver->getPosition());
		auto removeSelf = RemoveSelf::create();
		energy->runAction(Sequence::create(moveTo, removeSelf, nullptr));

		auto blink = cocos2d::Blink::create(0.5f, 3);
		energyReceiver->runAction(blink);

		energy->autorelease();

		return energy;
	}

	return nullptr;
}

/******************************************����״̬*************************************************/

/* �����չ���ֵ */
int Hero::dealDamage()
{
	return attack_;
}
/* ���к���û */
bool Hero::isUltimateSkillReady()
{
	return ultimateReady_;
}
/* �����г���charge������ */
void Hero::chargeForUlitmateSkill(int charge)
{
	ultimateProgress_ += charge;
	if (ultimateProgress_ >= ultiFull)
	{
		ultimateReady_ = true;
		ultimateProgress_ -= ultiFull;
	}
}
void Hero::ultimateSkill()
{
	;
}
void Hero::clearUltimateSkillProgress()
{
	ultimateReady_ = false;
}

void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// �����ã�����ᱻ�ͷŵ�
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() * 0.5f, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask����ײ��body���� ��һ������������
	physicsBody->setContactTestBitmask(bitmask);// ��һ���������������ײ��ʱ��֪ͨ
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}