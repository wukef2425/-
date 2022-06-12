#pragma once
#ifndef __Gamepause__H__
#define __Gamepause__H__
#include "cocos2d.h"


USING_NS_CC;
class Gamepause : public cocos2d::Scene
{
public:
    virtual bool init();

    static cocos2d::Scene* scene();

    //������Ϸ
    void Gamepause::menuContinueCallback(Ref* pSender);
    //���¿�ʼ��Ϸ
    void Gamepause::menuRestartCallback(Ref* pSender);
    //��������
    void Gamepause::menuLoginCallback(Ref* pSender);

    CREATE_FUNC(Gamepause);


private:

    cocos2d::Menu* pMenu;

};

#endif // __Gamepause_H__