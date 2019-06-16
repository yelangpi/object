#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include"Model/Model.h"
#include"Level.h"
#include<map>
#include<string>
class Hero:public Model
{
public:
	CC_SYNTHESIZE(int, _level, Level);
	CC_SYNTHESIZE(int, _exp, Exp);
	CC_SYNTHESIZE(int, _money, Money);
	void WalkWithDirection(std::string diret);
	void StopWalking(std::string s);
	bool init(std::string name);
	void initWithProperty(std::string name);
	cocos2d::Vec2 born_position;
	long long revive_time;
	bool isV = true;
	int head = 0;
	//记录所有反复的运动
	std::map<std::string, cocos2d::RepeatForever*> reActions;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	static Hero*CreateWithName(std::string name);
	void Move(float delta);
	void doHP();
	bool initHP = false;
	long long _attackTime = 0.0f;
	long long _attackTime1 = 0.0f;
	long long _attackTime2 = 0.0f;
	long long _attackTime3 = 0.0f;
};
#endif

