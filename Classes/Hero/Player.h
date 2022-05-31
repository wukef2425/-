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

    /* 用于监听键盘 使player移动 */
    void listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void Player::update(float delta) override;

private:

    enum Key { W, A, S, D};

    bool keyPressed[4] = {};

    /* 获取屏幕大小并按比例设置player位置 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();

    float x = winSize.width * 0.5f;

    float y = winSize.height * 0.5f;
    
    /* 设置步长 */
    float step = 10.f;
};

#endif // #define __PLAYER_H__