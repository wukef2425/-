/**
*@file StartLoginScene.cpp
* @author wyf
*/
#include "StartLoginScene.h"
#include "StartMenuScene.h"

USING_NS_CC;

Scene* StartLoginScene::createScene()
{
    return StartLoginScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartLoginScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //���ñ���ͼƬ
    auto* background = Sprite::create("Scene/MyLoginScene.jpg");        //���������࣬����ͼƬΪbackground.jpg
    background->setScale(1.05f);
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //�ñ���ͼ�������ʾ
    addChild(background, 0);

    //��һЩ���߰����С���
    auto* agetip = Sprite::create("AgeTip.jpg");        //������ʾ
    agetip->setScale(0.7f);
    if (agetip == nullptr)
    {
        problemLoading("'AgeTip.jpg'");
    }
    else
    {
        agetip->setPosition(visibleSize.width - (agetip->getContentSize().width*2)/3, visibleSize.height - (agetip->getContentSize().height * 2) / 3);        //��������ʾ�����Ͻ�
        addChild(agetip, 1);
    }
    
    auto* gamelogo = Sprite::create("GameLogo.png");        //��Ϸlogo
    
    if (gamelogo == nullptr)
    {
        problemLoading("'GameLogo.png'");
    }
    else
    {
        gamelogo->setPosition((2 * gamelogo->getContentSize().width) / 3, visibleSize.height - (2*gamelogo->getContentSize().height) / 3);        //����Ϸlogo�����Ͻ�
        addChild(gamelogo, 2);
    }

    //���ص�¼��ť
    auto LoginItem = MenuItemImage::create(
        "Login.png",
        "Login.png",
        CC_CALLBACK_1(StartLoginScene::menuCloseCallback, this));
    LoginItem->setScale(0.6f);//�õ�¼��ť��С�ߴ�
    if (LoginItem == nullptr ||
        LoginItem->getContentSize().width <= 0 ||
        LoginItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2 ;
        float y = origin.y + visibleSize.height/5;
        LoginItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object����ʵ�Ҳ���Ϊɶ����ֱ������
    auto menu = Menu::create(LoginItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    



    return true;
}

void StartLoginScene::menuCloseCallback(Ref* pSender)
{
    //���µ�¼��ť���л���menuҳ��
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StartMenuScene::createScene()));

}