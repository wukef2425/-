#pragma once
#ifndef _FIGHT_UTILS_H_
#define _FIGHT_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class FightUtils
{
public:
	/*ö������Ӣ��*/
	enum AllHero
	{
		ChangYi,
		YunHe,
		HaoQing,
		SanYue,
		ShunDe
	};

	/*������¼ս��������һϵ������
    ����ѡ��������ͼ������ʣ��ĸ������������Ѫ��*/

	static AllHero _hero;		//���ʹ�õ�brawl
	

};

#endif // !_FIGHT_UTILS_H_