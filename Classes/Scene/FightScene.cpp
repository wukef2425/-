/*Fight������ҪҪ���ص�������
1.UI������������Ϸʱ��/����Ѫ������/��������/��/��ľ��棬�����Ƕ�̬�ɱ仯��
2.��������ͨ�����/����/��������������ﶯ�����иı�
3.ÿһ��Ԫ�����ڵĲ㣺��ͼ 0���ϰ������ 1�����ò� 5��������
4.�ֽ��ߣ�������Χ����������

*/
#include "cocos2d.h"
#include "FightScene.h"

USING_NS_CC;

Scene* FightScene::createScene()
{
    return FightScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FightScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
   //��֪��Ϊʲô����tmx��ʱ�����Ǽ��ش���̫������
	//auto* SnowMap = TMXTiledMap::create("Map/SnowMap.tmx");
	//addChild(SnowMap, 0);

    return true;
}

