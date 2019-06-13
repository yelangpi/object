#ifndef __SHIELD_H__
#define __SHIELD_H__
#include"cocos2d.h"
#include"Model/Soldier.h"
#include"Model/Hero.h"
#include"Model/Model.h"
class Shield :public cocos2d::Sprite
{
	CC_SYNTHESIZE(float, _injure, Injure);
	CC_SYNTHESIZE(long long, _endtime, Endtime);
	CC_SYNTHESIZE(long long, _nowtime, Nowtime);
	CC_SYNTHESIZE(Model*, _owner, Owner);
	CREATE_FUNC(Shield);
	static Shield* createWithName(std::string name);
	bool initWithName(std::string name);
	std::string _direction;
public:
	const std::string& getDirection();
	void setDirection(const std::string);
	std::vector<Model*>target;

};
#endif
