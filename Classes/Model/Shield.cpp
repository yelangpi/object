#include"Model/Shield.h"
Shield * Shield::createWithName(std::string name)
{
	Shield *pRet = new(std::nothrow) Shield();
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

bool Shield::initWithName(std::string name)
{
	if (!this->Sprite::initWithFile(name))
	{

		return false;
	}
	return true;
}

const std::string & Shield::getDirection()
{
	return _direction;
}

void Shield::setDirection(const std::string direction)
{
	_direction = direction;
}


