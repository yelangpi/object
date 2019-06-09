#ifndef __FLYINGBOX_H__
#define __FLYINGBOX_H__
#include"cocos2d.h"
#include"Model.h"
#include"Model/Soldier.h"
#include"Model/Hero.h"
class FlyingBox:public cocos2d::Sprite
{
	CC_SYNTHESIZE(float, _injure, Injure);
	CC_SYNTHESIZE(long long, _nowtime, Nowtime);
	CC_SYNTHESIZE(Model*, _owner, Owner);
	CREATE_FUNC(FlyingBox);
	static FlyingBox* createWithName(std::string name);
	bool initWithName(std::string name);
public:
	std::vector<Model*>target;
	void DoSomethingAwesome();

};
#endif