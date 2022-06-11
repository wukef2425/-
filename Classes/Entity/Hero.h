/**
* @file Hero.h
* @author wukef & wyf
*/

#ifndef __Hero_H__
#define __Hero_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Consts.h"

USING_NS_CC_EXT;
USING_NS_CC;

class Hero :public cocos2d::Sprite
{
protected:

	bool isAlive_ = true;// �Ƿ���

	bool ultimateReady_ = false;// ���к���û

	bool confirm_ = false;// �Ƿ�ȷ��ʩ�Ŵ���

	int attack_;// ����ֵ

	int defend_;// ����ֵ

	ControlSlider* _hpSlider;//Ѫ��
	float health_;// ��ǰ����
	float healthInit_;//��ʼ����

	ControlSlider* _mpSlider;// ����
	float bullet_ = bulletFull;// ��ǰ��ҩ
	float bulletInit_ = bulletFull;// ��ʼ��ҩ

	ControlSlider* _spSlider;// ������
	float skill_ = 0;// ��ǰ����ŭ��ֵ
	float skillInit_ = ultiFull;// �����ֵ

public:

	/* ����״̬ */

	bool isAlive();

	void receiveDamage(int damage, Hero*& injuredSprite, Hero*& killer);

	void receiveDamage(int damage, Hero*& injuredSprite);

	void die(Hero*& diedSprite, Hero*& killer);

	void die(Hero*& diedSprite);

	Hero* createEnergy(Hero*& energyGenerator, Hero*& energyReceiver);

	void recoverHealth();

	/* ����״̬ */

	int dealDamage();

	float currentBullet();

	bool isUltimateSkillReady();

	void chargeForUlitmateSkill(int charge);

	void confirmToReleaseUltimateSkill();

	bool isReleaseConfirmed();
	
	virtual void ultimateSkill(Vec2 touchWorldPosition);

	void clearUltimateSkillProgress();

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	void recoverBullet();
	
	/* UI */
	
	void Hero::initHpSlider();
	Vec2 Hero::getHpSliderPos();
	void Hero::update_hp();

	void Hero::initMpSlider();
	Vec2 Hero::getMpSliderPos();
	void Hero::update_mp();

	void Hero::initSpSlider();
	Vec2 Hero::getSpSliderPos();
	void Hero::update_sp();


	virtual ~Hero() = default;

};

#endif