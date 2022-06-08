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

	bool ultimateProgress_ = false;// ���н�����

	int health_;// ��ǰ����

	int bullet_;// ��ǰ��ҩ

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

};

#endif