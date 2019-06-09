#include "FlyingBox.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"base/ccUTF8.h"
FlyingBox * FlyingBox::createWithName(std::string name)
{
	FlyingBox *pRet = new(std::nothrow) FlyingBox(); 
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
bool FlyingBox::initWithName(std::string name)
{

	if (!this->Sprite::initWithFile(name))
	{
		
		return false;
	}
	return true;
}

void FlyingBox::DoSomethingAwesome()
{
	cocos2d::Vec2 ballposition = this->getOwner()->getPosition();
	float x = 5.0f;
	if (this->getOwner()->Now_Direction == "Left")
	{
		ballposition.x -= x;
	}
	else if (this->getOwner()->Now_Direction == "Right")
	{
		ballposition.x += x;
	}
	else if (this->getOwner()->Now_Direction == "Up")
	{
		ballposition.y += x;
	}
	else if (this->getOwner()->Now_Direction == "Down")
	{
		ballposition.y -= x;
	}
	else if (this->getOwner()->Now_Direction == "Left-Up")
	{
		ballposition.x -= x;
		ballposition.y += x;
	}
	else if (this->getOwner()->Now_Direction == "Left-Down")
	{
		ballposition.x -= x;
		ballposition.y -= x;
	}
	else if (this->getOwner()->Now_Direction == "Right-Up")
	{
		ballposition.x += x;
		ballposition.y += x;
	}
	else if (this->getOwner()->Now_Direction == "Right-Down")
	{
		ballposition.x += x;
		ballposition.y -= x;
	}
	this->setPosition(ballposition);
	this->setVisible(true);
}
