#include "RangeSkill.h"

RangeSkill * RangeSkill::createWithName(std::string name)
{
	RangeSkill *pRet = new(std::nothrow) RangeSkill();
	if (pRet && pRet->initWithName(name))
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

bool RangeSkill::initWithName(std::string name)
{
	if (!this->Sprite::initWithFile(name))
	{

		return false;
	}
	return true;
}
