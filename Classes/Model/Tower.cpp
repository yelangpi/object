#include "Tower.h"
USING_NS_CC;
bool Tower::init(std::string name)
{
	this->initWithProperty();
	if (!this->Sprite::initWithFile(name))
	{
		return false;
	}
	return true;
}

Tower * Tower::CreateWithName(std::string name)
{
	Tower *pRet = new(std::nothrow) Tower();
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

void Tower::initWithProperty()
{
	setHp(600);
	setCurrentHp(600);
	setMp(0);
	setCurrentMp(0);
	setMagicAttack(0);
	setPhysicsAttack(10);
	setMagicDefence(0);
	setPhysicsDefence(0);
	setMovingRate(360);
}
