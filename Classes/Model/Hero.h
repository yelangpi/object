#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include"Model/Model.h"
#include<map>
#include<string>
class Hero:public Model
{
public:
	
	void WalkWithDirection(std::string diret);
	void StopWalking(std::string s);
	bool init(std::string name);
	void initWithProperty(std::string name);
	//记录所有反复的运动
	std::map<std::string, cocos2d::RepeatForever*> reActions;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	static Hero*CreateWithName(std::string name);
	void Move(float delta);
	long long _attackTime = 0.0f;
	long long _attackTime1 = 0.0f;
	long long _attackTime2 = 0.0f;
	long long _attackTime3 = 0.0f;
};
#endif
