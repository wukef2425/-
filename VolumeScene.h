#pragma once
#ifndef __VOLUME_SCENE__H__
#define __VOLUME_SCENE__H__
#include "cocos2d.h"

USING_NS_CC;
class VolumeScene : public cocos2d::Scene
{
public:
    virtual bool init();

    static cocos2d::Scene* scene();
    
    void VolumeScene::settingSceneCallback(Ref* pSender);

    void VolumeScene::initVolumeControl();//��������

    CREATE_FUNC(VolumeScene);


private:

    cocos2d::Menu* pMenu;

};

#endif // __Gamepause_H__
