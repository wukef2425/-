/**
* @file Hero.h
* @author wukef
*/

#ifndef __Consts_H__
#define __Consts_H__

/* ���� */
#define OriginalPlayerNum 2
/* ���� */
#define YunHeNumber 1
#define ChangYiNumber 2
#define HaoQingNumber 3
#define ShunDeNumber 4
#define SanYueNumber 5

/* bitmasks */
#define PlayerBulletAndEnemyBitmask  0x1 //0001
#define EnemyBulletAndPlayerBitmask  0x2 //0010



/* tags */
#define PlayerBulletTag 1
#define EnemyBulletTag 2

#define PlayerTag 3
#define EnemyTag 4

#define EnergyTag 5
#define EnergyBoxTag 6

#define YunHeUtimateSkillTag 7



/* ����die��ʱ���������ּƷְ�Ҫ��Ҫ���� */
#define HeroDieTag 101
#define EnergyBoxDieTag 102



/* AI���� */
#define ShootSpeed 1000
#define AIShootCycle 1.f



/* smoke���� */
#define SmokeSpeed 10.f
#define SmokeDamage 10.f



/* UIλ�� */
#define HpSliderPosY 50
#define MpSliderPosY 45
#define SpSliderPosY 40


/* HERO */
#define HealthRecovery 0.05f
#define BulletRecovery 0.01f
#define PlayerStep 15.f
//ͨ��
#define bulletFull 5.f
#define ultiFull 100.f

#define EnergyBoxHealthInit 100
#define EnergyBoxDefend 10

#define ChangYiHealthInit 80
#define ChangYiAttack 35
#define ChangYiDefend 2

#define HaoQingHealthInit 200
#define HaoQingAttack 12
#define HaoQingDefend 10

#define SanYueHealthInit 120
#define SanYueAttack 30
#define SanYueDefend 8

#define ShunDeHealthInit 100
#define ShunDeAttack 30
#define ShunDeDefend 12

#define YunHeHealthInit 110
#define YunHeAttack 33
#define YunHeDefend 10



/* ʰȡenergy��õ����� */
#define EnergyHealthBonus 10.f
#define EnergyAttackBonus 2
#define EnergyDefendBonus 2



#endif