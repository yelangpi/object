#ifndef __RANGESKILL_H__
#define __RANGESKILL_H__
#include"cocos2d.h"
#include"Model/Soldier.h"
#include"Model/Hero.h"
#include"Model/Model.h"
class RangeSkill :public cocos2d::Sprite
{
	CC_SYNTHESIZE(float, _injure, Injure);
	CC_SYNTHESIZE(long long, _endtime, Endtime);
	CC_SYNTHESIZE(Model*, _owner, Owner);
	CREATE_FUNC(RangeSkill);
	static RangeSkill* createWithName(std::string name);
	bool initWithName(std::string name);
public:
	
};
#endif