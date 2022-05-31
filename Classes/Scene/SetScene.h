#pragma once
#ifndef __SET_SCENE_H__
#define __SET_SCENE_H__

#include "cocos2d.h"

class SetScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void SetScene::initDecoration();
    
    void SetScene::initRuleBooks();//����˵��
    
    void SetScene::ruleBooksCallback(Ref* pSender);

    void SetScene::initVolumeSound();//������Ч

    void SetScene::volumeSoundCallback(Ref* pSender);

    void SetScene::initReturnMenu();//������ҳ��

    void SetScene::menuReturnCallback(Ref* pSender);

    CREATE_FUNC(SetScene);

protected:

    cocos2d::Menu* ruleButton_;

    cocos2d::Menu* vosoButton_;

    cocos2d::Menu* returnButton_;

};

#endif // #define __SET_SCENE_H__