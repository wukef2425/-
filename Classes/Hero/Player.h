/**
* @file Player.h
* @author wukef
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Hero/Hero.h"

class Player : public Hero
{
public:

    static Player* Player::create(const std::string& filename);

    /* ���ڼ������� ʹplayer�ƶ� */
    void listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void Player::update(float delta) override;

private:

    enum Key { W, A, S, D};

    bool keyPressed[4] = {};

    /* ��ȡ��Ļ��С������������playerλ�� */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;
    
    /* ���ò��� */
    float step = 10.f;
};

#endif // #define __PLAYER_H__