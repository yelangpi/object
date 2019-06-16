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
	this->setEndTime(0);
	this->setHp(LEVEL_HP(1));
	this->setMp(LEVEL_MP(1));
	this->setCurrentHp(LEVEL_HP(1));
	this->setCurrentMp(LEVEL_MP(1));
	this->setPhysicsAttack(LEVEL_ATTACK(1));
	this->setPhysicsDefence(LEVEL_DEFENCE(1));
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
	if (!this->isDie() && GetCurrentTime() > this->getEndTime())
	{
		if (keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
		{
			//WalkWithDirection("Left-Up");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x - 5/1.414, vec.y + 5 / 1.414));
			return;
		}
		else if (keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
		{
			//WalkWithDirection("Left-Down");
			auto vec = this->getPosition();
			this->setPosition(Vec2(vec.x - 5 / 1.414, vec.y - 5 / 1.414));
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
			this->setPosition(Vec2(vec.x + 5 / 1.414, vec.y - 5 / 1.414));
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
}

void Hero::doHP()
{
	if (!initHP)
	{
		cocos2d::Sprite*HPbox = cocos2d::Sprite::create("xuetiao/xuetiao2.png");
		cocos2d::Sprite*HPrectangle = cocos2d::Sprite::create("xuetiao/xuetiao1.png");
		cocos2d::Label* label= cocos2d::Label::createWithTTF("1", "fonts/Marker Felt.ttf", 30);
		_HPbox = HPbox;
		_HPrectangle = HPrectangle;
		_Level = label;
		initHP = true;
		this->getParent()->addChild(_Level, 10);
		this->getParent()->addChild(HPbox, 10);
		this->getParent()->addChild(HPrectangle, 10);
		_HPrectangle->setAnchorPoint(Vec2(0, 0));
	}
	if (!this->isDie())
	{
		Vec2 v1 = this->getPosition();
		Vec2 v2 = this->getContentSize();
		Vec2 v = Vec2(v1.x, v1.y + v2.y / 2 + 20);
		Vec2 v3 = _HPrectangle->getContentSize();
		_HPbox->setPosition(v);
		_HPrectangle->setPosition(v - 0.5*v3);
		_HPrectangle->setScaleX(this->getCurrentHp() / this->getHp());
		_HPbox->setVisible(true);
		_HPrectangle->setVisible(true);
		_Level->setPosition((v.x - 0.5*v3.x - 10), v.y - 0.5*v3.y);
		_Level->setVisible(true);
	}
	else
	{
		_HPbox->setVisible(false);
		_HPrectangle->setVisible(false);
		_Level->setVisible(false);
	}
	if (this->getCurrentHp() <= 0)
	{
		this->setCurrentHp(0);
		this->setVisible(false);
		if (isV)
		{
			head++;
			this->revive_time = GetCurrentTime() + 10000;
			isV = false;
		}
	}
	if (this->getExp() >= LEVEL(this->getLevel()+1))
	{
		this->setExp(0);
		this->setLevel(this->getLevel() + 1);
		this->setHp(this->getHp() + LEVEL_HP(this->getLevel()) - LEVEL_HP(this->getLevel() - 1));
		this->setMp(this->getMp() + LEVEL_MP(this->getLevel()) - LEVEL_MP(this->getLevel() - 1));
		this->setPhysicsAttack(this->getPhysicsAttack() + LEVEL_ATTACK(this->getLevel()) - LEVEL_ATTACK(this->getLevel() - 1));
		this->setPhysicsDefence(this->getPhysicsDefence() + LEVEL_DEFENCE(this->getLevel()) - LEVEL_DEFENCE(this->getLevel() - 1));
		_Level->setString(std::to_string(this->getLevel()));
	}
}

