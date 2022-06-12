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

	ControlSlider* _hpSlider;//Ѫ��

	ControlSlider* _mpSlider;// ����
	float bullet_ = bulletFull;// ��ǰ��ҩ
	float bulletInit_ = bulletFull;// ��ʼ��ҩ

	ControlSlider* _spSlider;// ������
	float skill_ = 0;// ��ǰ����ŭ��ֵ
	float skillInit_ = ultiFull;// �����ֵ

	/* ���ò��� */
    float step = PlayerStep;

	/* ��ȡ��Ļ��С������������playerλ�� */
	cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

	float x = winSize.width * 0.5f;
	float initX = winSize.width * 0.5f;
	float y = winSize.height * 0.5f;
	float initY = winSize.height * 0.5f;

public:
	/* ����״̬ */
	int dieTag_ = AIDieTag;// ���ּƷְ��Ƿ�Ҫ����Ĭ��AI
	float attack_;// ����ֵ
	float defend_;// ����ֵ
	float health_;// ��ǰ����
	float healthInit_;//��ʼ����

	bool isAlive();

	void receiveDamage(float damage, Hero*& injuredSprite, Hero*& killer);

	void receiveDamage(float damage, Hero*& injuredSprite);

	void die(Hero*& diedSprite, Hero*& killer);

	void die(Hero*& diedSprite);

	Hero* createEnergy(Hero*& energyGenerator, Hero*& energyReceiver);

	void recoverHealth();

	void recoverHealth(Hero* heroToBerecovered, float recoverAmount);

	int getDieTag();

	/* ����״̬ */

	float dealDamage();

	float currentBullet();

	bool isUltimateSkillReady();

	void chargeForUlitmateSkill(float charge);

	void confirmToReleaseUltimateSkill();

	bool isReleaseConfirmed();
	
	virtual void ultimateSkill(Vec2 touchWorldPosition);

	virtual void attackHero(Vec2 playerPosition, Vec2 touchWorldPosition);

	void clearUltimateSkillProgress();

	static void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	void recoverBullet();

	void recoverBulletAndUpgrade(Hero* heroToBeRecovered, float attackUp, float ultiUp);
	
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