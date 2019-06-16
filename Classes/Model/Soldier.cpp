#include "Soldier.h"
USING_NS_CC;
bool Soldier::init(std::string name)
{
	this->initWithProperty();
	if (!this->Sprite::initWithFile(name))
	{
		return false;
	}
	return true;
}

Soldier * Soldier::CreateWithName(std::string name)
{
	Soldier *pRet = new(std::nothrow) Soldier();
	if (pRet && pRet->init(name))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void Soldier::initWithProperty()
{
	setHp(100);
	setCurrentHp(100);
	setMp(0);
	setCurrentMp(0);
	setMagicAttack(0);
	setPhysicsAttack(10);
	setMagicDefence(0);
	setPhysicsDefence(0);
	setMovingRate(360);
}

void Soldier::Move(float delta)
{
	if (!this->isDie() && GetCurrentTime() > this->getEndTime())
	{
		if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
		{
			//WalkWithDirection("Left-Up");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x - 6 / 1.414, vec.y + 6 / 1.414));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
		{
			//WalkWithDirection("Left-Down");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x - 6 / 1.414, vec.y - 6 / 1.414));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
		{
			//WalkWithDirection("Right-Up");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x + 6 / 1.414, vec.y + 6 / 1.414));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
		{
			//WalkWithDirection("Right-Down");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x + 6/1.414, vec.y - 6 / 1.414));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W])
		{
			//WalkWithDirection("Up");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x, vec.y + 6));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S])
		{
			//WalkWithDirection("Down");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x, vec.y - 6));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
		{
			//WalkWithDirection("Right");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x + 6, vec.y));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
		{
			//WalkWithDirection("Left");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x - 6, vec.y));
			return;
		}
		else
		{
			//StopWalking();
		}
	}
}