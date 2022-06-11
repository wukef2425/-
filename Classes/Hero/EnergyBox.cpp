#include "EnergyBox.h"
#include "Consts.h"

Hero* EnergyBox::createBox(Vec2 position)
{
    auto player = new(std::nothrow) EnergyBox;

    if (!player)
    {
        return nullptr;
    }

    player->dieTag_ = EnergyBoxDieTag;

    player->health_ = EnergyBoxHealthInit;//��ǰ����

    player->healthInit_ = EnergyBoxHealthInit;//�������

    player->defend_ = EnergyBoxDefend;//����ֵ

    auto chosenHero = Sprite::create("Hero/energy-box.png");

    if (chosenHero)
    {
        player->setPosition(position);

        player->bindPhysicsBodyAndTag(chosenHero, PlayerBulletAndEnemyBitmask, EnemyTag);

        player->addChild(chosenHero);

        player->autorelease();

        return player;
    }

    return nullptr;
}