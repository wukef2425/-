/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"
#include "Consts.h"


bool Hero::isUltimateSkillReady()
{
	return ultimateProgress_;
}

bool Hero::isAlive()
{
	return isAlive_;
}

void Hero::receiveDamage(int damage, Hero*& sprite)
{

	health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		// �������������������getPosition��ʧЧ������map������
		auto energy = cocos2d::Sprite::create("Hero/energy.png");
		energy->setPosition(sprite->getPosition());
		sprite->getParent()->addChild(energy);

		isAlive_ = false;
	}
	//auto blink = cocos2d::Blink::create(0.5f, 3);// �и��ʳ��ִ����˻����ӵ���bug����
	//sprite->runAction(blink);
}

void Hero::dealDamage(int damage)
{
	;
}

void Hero::ultimateSkill()
{
	;
}

void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// �����ã�����ᱻ�ͷŵ�
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize()/10, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask����ײ��body���� ��һ������������
	physicsBody->setContactTestBitmask(bitmask);// ��һ���������������ײ��ʱ��֪ͨ
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}
/************************************************Ѫ��������**********************************************************************/
//to wkf ������Ѫ���Ѿ���ƺ��ˣ�Ȼ�����ڵ���������ô����
//�뷨�ǿ������player���ӽڵ㵫���Ҳ�������� ��������position������ص��������position�й�����
//���Ҳ���Ե���fightscene���棬�����������漰������һЩ��Ϣ�ĵ���

//Ѫ��HP
void Hero::initHpSlider() {

	_hpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bloodHp.png", "Hero/FightHero/sliderThumb.png");

	_hpSlider->setEnabled(false);//�û������޷��ı����ֵ
	_hpSlider->setMaximumValue(healthInit_);//���û����������ֵ
	_hpSlider->setMinimumValue(0);//���û���������Сֵ
	_hpSlider->setValue(health_);//���û������ĵ�ǰֵ
	_hpSlider->setPosition(getHpSliderPos());//����Ѫ����λ��
	this->addChild(_hpSlider);
}

Point Hero::getHpSliderPos() {

	//�����Ҫ��Ƴ�����Ϊ�����getposition
	return Point(0, 0);
}

void Hero::update_hp() {

	if (_hpSlider < 0)
		_hpSlider = 0;
	if (_hpSlider) {
		_hpSlider->setValue(health_);
		_hpSlider->setPosition(getHpSliderPos());
	}

}
//����MP
void Hero::initMpSlider() {

	_mpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bulletMp.png", "Hero/FightHero/sliderThumb.png");

	_mpSlider->setEnabled(false);//�û������޷��ı����ֵ
	_mpSlider->setMaximumValue(bulletInit_);//���û����������ֵ
	_mpSlider->setMinimumValue(0);//���û���������Сֵ
	_mpSlider->setValue(bullet_);//���û������ĵ�ǰֵ
	_mpSlider->setPosition(getMpSliderPos());//����������λ��
	this->addChild(_mpSlider);

}

Point Hero::getMpSliderPos() {

	//�����Ҫ��Ƴ�����Ϊ�����getposition
	return Point(0, 0);
}

void Hero::update_mp() {

	if (_mpSlider < 0)
		_mpSlider = 0;
	if (_mpSlider) {
		_mpSlider->setValue(bullet_);
		_mpSlider->setPosition(getMpSliderPos());
	}

}

//������Ƹ������������ܴ����õ�
//ŭ��ֵSP
void Hero::initSpSlider() {

	_spSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/heroSp.png", "Hero/FightHero/sliderThumb.png");

	_spSlider->setEnabled(false);//�û������޷��ı����ֵ
	_spSlider->setMaximumValue(skillInit_);//���û����������ֵ
	_spSlider->setMinimumValue(0);//���û���������Сֵ
	_spSlider->setValue(skill_);//���û������ĵ�ǰֵ
	_spSlider->setPosition(getSpSliderPos());//����������λ��
	this->addChild(_spSlider);

}

Point Hero::getSpSliderPos() {

	//�����Ҫ��Ƴ�����Ϊ�����getposition
	return Point(0, 0);
}

void Hero::update_sp() {

	if (_spSlider < 0)
		_spSlider = 0;
	if (_spSlider) {
		_spSlider->setValue(skill_);
		_spSlider->setPosition(getSpSliderPos());
	}

}