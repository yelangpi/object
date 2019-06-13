#include"ImpactWave.h"

ImpactWave * ImpactWave::createWithName(std::string name)
{
	ImpactWave *pRet = new(std::nothrow) ImpactWave();
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

bool ImpactWave::initWithName(std::string name)
{
	if (!this->Sprite::initWithFile(name))
	{

		return false;
	}
	return true;
}

const std::string & ImpactWave::getDirection()
{
	return _direction;
}

void ImpactWave::setDirection(const std::string direction)
{
	_direction = direction;
}

