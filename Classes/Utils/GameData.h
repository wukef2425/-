#pragma once
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class GameData
{
public:

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

	static int getRemainingPlayer();

	static void deleteDiedPlayer();

private:

	static int remainingPlayer;//��ǰ����

};

#endif // !_GAME_DATA_