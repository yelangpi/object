#include "Butterfly.h"

Butterfly * Butterfly::createWithName(std::string name)
{
	Butterfly *pRet = new(std::nothrow) Butterfly();
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

bool Butterfly::initWithName(std::string name)
{
	if (!this->Sprite::initWithFile(name))
	{

		return false;
	}
	return true;
}

const std::string & Butterfly::getDirection()
{
	return _direction;
}

void Butterfly::setDirection(const std::string direction)
{
	_direction = direction;
}

void Butterfly::DoSomethingAwesome()
{
	cocos2d::Vec2 ballposition = this->getOwner()->getPosition();
	float x = 5.0f;
	if (this->_direction == "Left")
	{
		ballposition.x -= x;
	}
	else if (this->_direction == "Right")
	{
		ballposition.x += x;
	}
	else if (this->_direction == "Up")
	{
		ballposition.y += x;
	}
	else if (this->_direction == "Down")
	{
		ballposition.y -= x;
	}
	else if (this->_direction == "Left-Up")
	{
		ballposition.x -= x;
		ballposition.y += x;
	}
	else if (this->_direction == "Left-Down")
	{
		ballposition.x -= x;
		ballposition.y -= x;
	}
	else if (this->_direction == "Right-Up")
	{
		ballposition.x += x;
		ballposition.y += x;
	}
	else if (this->_direction == "Right-Down")
	{
		ballposition.x += x;
		ballposition.y -= x;
	}
	this->setPosition(ballposition);
	this->setVisible(true);
}
