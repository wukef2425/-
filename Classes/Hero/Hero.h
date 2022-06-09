/**
* @file Hero.h
* @author wukef
*/

#ifndef __Hero_H__
#define __Hero_H__

#include "cocos2d.h"
USING_NS_CC;

class Hero :public cocos2d::Sprite
{
protected:

	friend class StatusBar;// ״̬�� ���������͵�ҩ��������

	class HealthBar;// ������

	class BulletBar;// ��ҩ��

	bool isAlive_ = true;// �Ƿ���

	bool ultimateReady_ = false;// ���к���û

	int ultimateProgress_ = 0;// ���н�����

	int health_;// ��ǰ����

	int bullet_;// ��ǰ��ҩ

	int maxHealth_;// �������

	int attack_;// ����ֵ

	int defend_;// ����ֵ

public:

	Hero* createEnergy(Hero*& energyGenerator, Hero*& energyReceiver);

	bool isAlive();

	void die(Hero*& diedSprite, Hero*& killer);

	int dealDamage();

	void chargeForUlitmateSkill(int charge);

	bool isUltimateSkillReady();

	void receiveDamage(int damage, Hero*& injuredSprite, Hero*& killer);

	virtual void ultimateSkill();

	void clearUltimateSkillProgress();

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	virtual ~Hero() = default;

};

#endif