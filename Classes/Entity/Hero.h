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

	int attack_;// ����ֵ

	int defend_;// ����ֵ

	ControlSlider* _hpSlider;//Ѫ��
	int health_;// ��ǰ����
	int healthInit_;//��ʼ����

	ControlSlider* _mpSlider;// ����
	int bullet_ = bulletFull;// ��ǰ��ҩ
	int bulletInit_ = bulletFull;// ��ʼ��ҩ

	ControlSlider* _spSlider;// ������
	int skill_ = 0;// ��ǰ����ŭ��ֵ
	int skillInit_ = ultiFull;// �����ֵ

public:

	/* ����״̬ */

	bool isAlive();

	void receiveDamage(int damage, Hero*& injuredSprite, Hero*& killer);

	void die(Hero*& diedSprite, Hero*& killer);

	Hero* createEnergy(Hero*& energyGenerator, Hero*& energyReceiver);

	
	/* ����״̬ */

	int dealDamage();

	int currentBullet();

	bool isUltimateSkillReady();

	void chargeForUlitmateSkill(int charge);
	
	virtual void ultimateSkill();

	void clearUltimateSkillProgress();

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	
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