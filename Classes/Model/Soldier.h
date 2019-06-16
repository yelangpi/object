#pragma once
#ifndef __SOLDIER_H__
#define __SOLDIER_H_
#include "cocos2d.h"
#include"Model/Model.h"
#include<string>
class Soldier :public Model
{
public:
	bool init(std::string name);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	static Soldier*CreateWithName(std::string name);
	void initWithProperty();
	void Move(float delta);
	int _name;
	long long _attackTime = 0.0f;
};
#endif