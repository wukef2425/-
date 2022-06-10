#include "cocos2d.h"
#include "Utils/CameraEffect.h"

CameraEffect * CameraEffect::create(cocos2d::Scene * scene)
{
	auto cameraEffect = new(std::nothrow) CameraEffect;

	if (cameraEffect == nullptr)
	{
		return nullptr;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	cocos2d::Camera* newCamera;

	if (scene->getCameras().empty())
	{
		newCamera = Camera::createOrthographic(winSize.width, winSize.height, 0, 1);// ���ƴ��ڴ�С
	}
	else
	{
		newCamera = scene->getCameras().front();
	}

	/* �������ǵ���� */
	newCamera->setCameraFlag(cocos2d::CameraFlag::DEFAULT);
	newCamera->setPosition(cocos2d::Vec2(-winSize.width * 0.5f, -winSize.height * 0.5f)); // ���ƾ�ͷλ��
	newCamera->setDepth(1);// ��������һ��
	cameraEffect->addChild(newCamera);

	/* ����UI������������ */
	cocos2d::Camera* newUICamera = Camera::createOrthographic(winSize.width, winSize.height, 0, 1);
	newUICamera->setCameraFlag(cocos2d::CameraFlag::USER1);// �����CameraFlag��UI���ᶯ
	newUICamera->setPosition(cocos2d::Vec2(0, 0));
	newUICamera->setDepth(2);// ��currentPlayer��һ��
	scene->addChild(newUICamera);

	cameraEffect->retain();
	cameraEffect->autorelease();

	return cameraEffect;

}

void CameraEffect::FollowPlayer(Player* player)
{
	if (player != nullptr)
	{
		player->addChild(this);
	}
}