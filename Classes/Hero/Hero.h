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

	friend class StatusBar;//״̬�� ���������͵�ҩ��������

	class HealthBar;//������

	class BulletBar;//��ҩ��

	bool isAlive_ = true;//�Ƿ���

	int health_;//��ǰ����

	int bullet_;//��ǰ��ҩ

	int maxHealth_;//�������

	int attack_;//����ֵ

	int defend_;//����ֵ

	int energy_;//�����Ժ�����������

public:

	bool isAlive();

	virtual void die();

	virtual void receiveDamage(int damage);

	virtual void dealDamage(int damage);

	virtual void ultimateSkill(int damage);

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	virtual ~Hero() = default;

};

#endif