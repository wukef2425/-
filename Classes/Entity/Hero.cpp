/**
* @file Player.cpp
* @author wukef & wyf
*/

#include "Hero.h"
#include "Consts.h"
#include "Scene/FightScene.h"


/******************************************����״̬*************************************************/

/* �Ƿ��� */
bool Hero::isAlive()
{
	return isAlive_;
}
/* killerʹinjuredSprite�ܵ�damage���˺� */
void Hero::receiveDamage(float damage, Hero*& injuredSprite, Hero*& killer)
{
	injuredSprite->health_ -= (damage - defend_);

	killer->chargeForUlitmateSkill(damage - injuredSprite->defend_);

	if (health_ <= 0)
	{
		die(injuredSprite, killer);
	}
}
/* receiveDamage���� injuredSprite���� ������� */
void Hero::receiveDamage(float damage, Hero*& injuredSprite)
{
	injuredSprite->health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		die(injuredSprite);
	}
}
/* killerɱ����diedSprite */
void Hero::die(Hero*& diedSprite, Hero*& killer)
{
	if (true == isAlive_)// ������ܶ�������为��
	{
		auto energy = Hero::createEnergy(diedSprite, killer);

		diedSprite->getParent()->addChild(energy);

		isAlive_ = false;

		if (diedSprite->dieTag_ == AIDieTag)
		{
			GameData::deleteDiedPlayer();
		}
	}
}
/* die���� diedSprite���� ������� */
void Hero::die(Hero*& diedSprite)
{
	if (true == isAlive_)// ������ܶ�������为��
	{
		isAlive_ = false;

		if (diedSprite->dieTag_ == AIDieTag)
		{
			GameData::deleteDiedPlayer();
		}
	}
}
/* energyGenerator����������energyReceiver */
Hero* Hero::createEnergy(Hero*& energyGenerator, Hero*& energyReceiver)
{
	auto energy = new(std::nothrow) Hero;

	if (energy == nullptr)
	{
		return nullptr;
	}

	auto tmp = Sprite::create("Hero/energy.png");

	if (tmp != nullptr)
	{
		energy->setPosition(energyGenerator->getPosition());

		energy->addChild(tmp);

		auto moveTo = MoveTo::create(0.1f, energyReceiver->getPosition());
		auto removeSelf = RemoveSelf::create();
		energy->runAction(Sequence::create(moveTo, removeSelf, nullptr));

		auto blink = cocos2d::Blink::create(0.5f, 3);
		energyReceiver->runAction(blink);

		energyReceiver->healthInit_ += EnergyHealthBonus;
		energyReceiver->attack_ += EnergyAttackBonus;
		energyReceiver->defend_ += EnergyDefendBonus;

		energy->autorelease();

		return energy;
	}

	return nullptr;
}
void Hero::recoverHealth()
{
	if (health_ < healthInit_ && true == isAlive_)
	{
		health_ += HealthRecovery;
	}

}

/******************************************����״̬*************************************************/

/* �����չ���ֵ */
float Hero::dealDamage()
{
	return attack_;
}
/* ���ص�ǰ�ӵ���Ŀ */
float Hero::currentBullet()
{
	if (0 < bullet_ && bullet_ < 1.f)
	{
		bullet_ = 0;
	}
	else if (1.f < bullet_)
	{
		bullet_--;
	}
	return bullet_;
}
/* ���к���û */
bool Hero::isUltimateSkillReady()
{
	return ultimateReady_;
}
/* �����г���charge������ */
void Hero::chargeForUlitmateSkill(float charge)
{
	if (false == ultimateReady_)// ���л�û��ʱ���Լ������ܣ����ͷ�û������
	{
		skill_ += charge;
	}
	if (skill_ >= ultiFull)
	{
		ultimateReady_ = true;
	}
}
/* ȷ��ʩ�Ŵ��� */
void Hero::confirmToReleaseUltimateSkill()
{
	confirm_ = true;
}
/* �Ƿ�ȷ��ʩ�Ŵ��� */
bool Hero::isReleaseConfirmed()
{
	return confirm_;
}
/* ���У�������ʵ�֣�*/
void Hero::ultimateSkill(Vec2 touchWorldPosition)
{
	;
}
/* ���з���֮����������� */
void Hero::clearUltimateSkillProgress()
{
	skill_ -= ultiFull;
	ultimateReady_ = false;
}
/* ���������ɲ�tag */
void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// �����ã�����ᱻ�ͷŵ�
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() * 0.5f, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask����ײ��body���� ��һ������������
	physicsBody->setContactTestBitmask(bitmask);// ��һ���������������ײ��ʱ��֪ͨ
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}
void Hero::recoverBullet()
{
	if (bullet_ < bulletInit_ && true == isAlive_)
	{
		bullet_ += BulletRecovery;
	}

}

/************************************************Ѫ��������**********************************************************************/

//Ѫ��HP
void Hero::initHpSlider() 
{
	_hpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bloodHp.png", "Hero/FightHero/sliderThumb.png");

	_hpSlider->setEnabled(false);//�û������޷��ı����ֵ
	_hpSlider->setMaximumValue(healthInit_);//���û����������ֵ
	_hpSlider->setMinimumValue(0);//���û���������Сֵ
	_hpSlider->setValue(health_);//���û������ĵ�ǰֵ
	_hpSlider->setPosition(getHpSliderPos());//����Ѫ����λ��
	this->addChild(_hpSlider);
}

Vec2 Hero::getHpSliderPos() 
{
	return Vec2(0, HpSliderPosY);
}

void Hero::update_hp()
{
	if (_hpSlider < 0)
	{
		_hpSlider = 0;
	}
	if (_hpSlider) 
	{
		_hpSlider->setValue(health_);
		_hpSlider->setPosition(getHpSliderPos());
	}
}
//����MP
void Hero::initMpSlider() 
{
	_mpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bulletMp.png", "Hero/FightHero/sliderThumb.png");

	_mpSlider->setEnabled(false);//�û������޷��ı����ֵ
	_mpSlider->setMaximumValue(bulletInit_);//���û����������ֵ
	_mpSlider->setMinimumValue(0);//���û���������Сֵ
	_mpSlider->setValue(bullet_);//���û������ĵ�ǰֵ
	_mpSlider->setPosition(getMpSliderPos());//����������λ��
	this->addChild(_mpSlider);
}

Vec2 Hero::getMpSliderPos()
{
	return Vec2(0, MpSliderPosY);
}

void Hero::update_mp()
{
	if (_mpSlider < 0)
	{
		_mpSlider = 0;
	}
	if (_mpSlider) 
	{
		_mpSlider->setValue(bullet_);
		_mpSlider->setPosition(getMpSliderPos());
	}
}

//ŭ��ֵSP
void Hero::initSpSlider()
{
	_spSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/heroSp.png", "Hero/FightHero/sliderThumb.png");

	_spSlider->setEnabled(false);//�û������޷��ı����ֵ
	_spSlider->setMaximumValue(skillInit_);//���û����������ֵ
	_spSlider->setMinimumValue(0);//���û���������Сֵ
	_spSlider->setValue(skill_);//���û������ĵ�ǰֵ
	_spSlider->setPosition(getSpSliderPos());//����������λ��
	this->addChild(_spSlider);
}

Vec2 Hero::getSpSliderPos() 
{
	return Vec2(0, SpSliderPosY);
}

void Hero::update_sp()
{
	if (_spSlider < 0)
	{
		_spSlider = 0;
	}
	if (_spSlider) 
	{
		_spSlider->setValue(skill_);
		_spSlider->setPosition(getSpSliderPos());
	}
}