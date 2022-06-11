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

	int dieTag_ = AIDieTag;// 区分计分板是否要减人

	bool isAlive_ = true;// 是否存活

	bool ultimateReady_ = false;// 大招好了没

	bool confirm_ = false;// 是否确认施放大招

	float attack_;// 攻击值

	float defend_;// 防御值

	ControlSlider* _hpSlider;//血条
	float health_;// 当前生命
	float healthInit_;//初始生命

	ControlSlider* _mpSlider;// 蓝条
	float bullet_ = bulletFull;// 当前弹药
	float bulletInit_ = bulletFull;// 初始弹药

	ControlSlider* _spSlider;// 技能条
	float skill_ = 0;// 当前积攒怒气值
	float skillInit_ = ultiFull;// 最大技能值

public:

	/* 生命状态 */

	bool isAlive();

	void receiveDamage(float damage, Hero*& injuredSprite, Hero*& killer);

	void receiveDamage(float damage, Hero*& injuredSprite);

	void die(Hero*& diedSprite, Hero*& killer);

	void die(Hero*& diedSprite);

	Hero* createEnergy(Hero*& energyGenerator, Hero*& energyReceiver);

	void recoverHealth();

	/* 攻击状态 */

	float dealDamage();

	float currentBullet();

	bool isUltimateSkillReady();

	void chargeForUlitmateSkill(float charge);

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