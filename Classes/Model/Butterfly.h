#ifndef __BUTTERFLY_H__
#define __BUTTERFLY_H__
#include"cocos2d.h"
#include"Model/Soldier.h"
#include"Model/Hero.h"
#include"Model/Model.h"
class Butterfly :public cocos2d::Sprite
{
	CC_SYNTHESIZE(float, _injure, Injure);
	CC_SYNTHESIZE(long long, _nowtime, Nowtime);
	CC_SYNTHESIZE(Model*, _owner, Owner);
	CREATE_FUNC(Butterfly);
	static Butterfly* createWithName(std::string name);
	bool initWithName(std::string name);
	std::string _direction;
public:
	const std::string& getDirection();
	void setDirection(const std::string);
	std::vector<Model*>target;
	void DoSomethingAwesome();

};
#endif