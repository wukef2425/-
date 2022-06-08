/**
* @file Player.cpp
* @author wukef
*/

#include "Player.h"
#include "Consts.h"
#include "Scene/FightScene.h"

void Player::listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    using K = cocos2d::EventKeyboard::KeyCode;// ȫif��elseif����ʵ��ͬʱ��������

    if (keyCode == K::KEY_D)
    {
        keyPressed[D] = true;
    }
    if (keyCode == K::KEY_A)
    {
        keyPressed[A] = true;
    }
    if (keyCode == K::KEY_W)
    {
        keyPressed[W] = true;
    }
    if (keyCode == K::KEY_S)
    {
        keyPressed[S] = true;
    }
}

void Player::listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    using K = cocos2d::EventKeyboard::KeyCode;

    if (keyCode == K::KEY_D)
    {
        keyPressed[D] = false;
    }
    if (keyCode == K::KEY_A)
    {
        keyPressed[A] = false;
    }
    if (keyCode == K::KEY_W)
    {
        keyPressed[W] = false;
    }
    if (keyCode == K::KEY_S)
    {
        keyPressed[S] = false;
    }
}

/*������ҵ���Ϣ����������λ�ã�����λ����barrier/grass���Լ���ͷ����*/
void Player::update(float delta)
{
    if (keyPressed[W])
    {
        y += step;
    }
    if (keyPressed[A])
    {
        x -= step;
    }
    if (keyPressed[S])
    {
        y -= step;
    }
    if (keyPressed[D])
    {
        x += step;
    }

    //�Ҹ����������괫�ص�fight
    setPosition(x, y);
}

/*
* 
Vec2 Player::returnPosition()
{
    return Vec2(x, y);
}

*/

