/**
* @file Player.h
* @author wukef
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Hero/Hero.h"

class Player : public Hero
{
private:

    enum Key { W, A, S, D, E };

    bool keyPressed[5] = {};
    
    /* ���ò��� */
    float step = 10.f;

    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;

public:

    /* ���ڼ������� ʹplayer�ƶ� */
    void listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void update(float delta) override;
    //Vec2 Player::returnPosition();
};

#endif // #define __PLAYER_H__