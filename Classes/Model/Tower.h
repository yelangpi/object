#pragma once
#ifndef __TOWER_H__
#define __TOWER_H_
#include "cocos2d.h"
#include"Model/Model.h"
#include<string>
class Tower :public Model
{
public:
	bool init(std::string name);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	static Tower*CreateWithName(std::string name);
	void initWithProperty();
	long long _attackTime = 0.0f;
};
#endif