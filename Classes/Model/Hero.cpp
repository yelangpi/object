#include "Hero.h"
#include"Model/FlyingBox.h"
USING_NS_CC;


void Hero::WalkWithDirection(std::string diret)
{
	Now_Direction = diret;
	//this->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_%s", this->getName().c_str(), diret.c_str()));
	Animate *action = Animate::create(animation);
	
	auto repeatAction = RepeatForever::create(action);
	reActions[diret] = repeatAction;
	this->runAction(repeatAction);

}
void Hero::StopWalking(std::string s)
{
	this->stopAction(reActions[s]);
}

bool Hero::init(std::string name)
{
	this->setName(name);
	this->setDirction_image();
	this->initWithProperty(name);
	if (!this->Sprite::initWithFile(dirction_image["Left"]))
	{
		return false;
	}
	return true;
}

void Hero::initWithProperty(std::string name)
{
	if (name == "DaJi") 
	{
		setHp(3229);
		setCurrentHp(3229);
		setMp(490);
		setCurrentMp(490);
		setMagicAttack(0);
		setPhysicsAttack(170);
		setMagicDefence(50);
		setPhysicsDefence(86);
		setMovingRate(360);
	}
	else if (name=="YaSe")
	{
		setHp(0);
		setCurrentHp(0);
		setMp(0);
		setCurrentMp(0);
		setMagicAttack(0);
		setPhysicsAttack(0);
		setMagicDefence(0);
		setPhysicsDefence(0);
		setMovingRate(0);
	}
	else if (name=="HouYi")
	{
		setHp(0);
		setCurrentHp(0);
		setMp(0);
		setCurrentMp(0);
		setMagicAttack(0);
		setPhysicsAttack(0);
		setMagicDefence(0);
		setPhysicsDefence(0);
		setMovingRate(0);
	}
}

Hero * Hero::CreateWithName(std::string name)
{
	Hero *pRet = new(std::nothrow) Hero();
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
void Hero::Move(float delta)
{
	if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
	{
		//WalkWithDirection("Left-Up");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x - 2, vec.y + 2));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
	{
		//WalkWithDirection("Left-Down");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x - 2, vec.y - 2));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
	{
		//WalkWithDirection("Right-Up");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x + 2, vec.y + 2));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
	{
		//WalkWithDirection("Right-Down");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x + 2, vec.y - 2));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W])
	{
		//WalkWithDirection("Up");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x, vec.y + 5));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S])
	{
		//WalkWithDirection("Down");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x, vec.y - 5));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
	{
		//WalkWithDirection("Right");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x + 5, vec.y));
		return;
	}
	else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
	{
		//WalkWithDirection("Left");
		auto vec = this->getPosition();
		this->setPosition(Vec2(vec.x - 5, vec.y));
		return;
	}
	else
	{
		//StopWalking();
	}
}

