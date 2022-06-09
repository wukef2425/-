/**
* @file Hero.h
* @author wukef
*/

#ifndef __Hero_H__
#define __Hero_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
USING_NS_CC;

class Hero :public cocos2d::Sprite
{
protected:

	friend class StatusBar;// ״̬�� ���������͵�ҩ��������

	class HealthBar;// ������

	class BulletBar;// ��ҩ��

	bool isAlive_ = true;// �Ƿ���

	bool ultimateProgress_ = false;// ���н�����

	ControlSlider* _hpSlider;//Ѫ��
	int health_;// ��ǰ����
	int healthInit_;//��ʼ����

	ControlSlider* _mpSlider;//����
	int bullet_;// ��ǰ��ҩ
	int bulletInit_;//��ʼ����

	ControlSlider* _spSlider;//������
	int skill_;// ��ǰ����ŭ��ֵ
	int skillInit_;//�����ֵ

	int maxHealth_;// �������

	int attack_;// ����ֵ

	int defend_;// ����ֵ

	int energy_;// �����Ժ�����������

	
public:

	Hero* create(const std::string& filename);

	bool isAlive();

	bool isUltimateSkillReady();

	void receiveDamage(int damage, Hero*& sprite);

	virtual void dealDamage(int damage);

	virtual void ultimateSkill();

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	virtual ~Hero() = default;

	void Hero::initHpSlider();
	Point Hero::getHpSliderPos();
	void Hero::update_hp();

	void Hero::initMpSlider();
	Point Hero::getMpSliderPos();
	void Hero::update_mp();

	void Hero::initSpSlider();
	Point Hero::getSpSliderPos();
	void Hero::update_sp();
};

#endif