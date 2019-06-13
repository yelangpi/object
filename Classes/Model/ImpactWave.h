#ifndef __IMPACTWAVE_H__
#define __IMPACTWAVE_H__
#include"cocos2d.h"
#include"Model/Soldier.h"
#include"Model/Hero.h"
#include"Model/Model.h"
class ImpactWave :public cocos2d::Sprite
{
	CC_SYNTHESIZE(float, _injure, Injure);
	CC_SYNTHESIZE(long long, _endtime, Endtime);
	CC_SYNTHESIZE(Flag, _flag, Flag);
	CREATE_FUNC(ImpactWave);
	static ImpactWave* createWithName(std::string name);
	bool initWithName(std::string name);
	std::string _direction;
public:
	const std::string& getDirection();
	void setDirection(const std::string);
	std::vector<Model*>target;
	std::vector<int>target_length;

};
#endif#pragma once
