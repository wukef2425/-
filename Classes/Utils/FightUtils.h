#pragma once
#ifndef _FIGHT_UTILS_H_
#define _FIGHT_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
/*��¼ս����һЩ״̬
* ѡ��������ͼ
* Ӣ�۵������Լ�ʣ���Ӣ����
*/
class FightUtils
{
public:
	/*ö�����е�ͼ*/
	enum AllMap
	{
		MapA,
		MapB,
		MapC
	};
	/*ö������Ӣ��*/
	enum AllHero
	{
		ChangYi,
		YunHe,
		HaoQing,
		SanYue,
		ShunDe
	};
	/*��̬��Ա�������洢�л�����ʱ�õ�����Ϣ*/
	static AllMap _map;
	static AllHero _hero;		//���ʹ�õ�brawl
	static INT32 _heroNumber;	//brawler����

	/*��������*/
	static bool _musicOn;			//��¼�Ƿ񲥷�����
	static bool _effectOn;			//��¼�Ƿ񲥷���Ч


};

#endif // !_FIGHT_UTILS_H_