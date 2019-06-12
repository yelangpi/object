#pragma once
#ifndef _LEVEL_H
#define _LEVEL_H
#include"Model/Model.h"
#include<vector>
#include<string>
//每一个等级所应该有的数据全部都储存在这个LevelData类里面
struct LevelData {
	float _hp = 0.0;
	float _mp = 0.0;
	float _magicAttack = 0.0;
	float _physicsAttack = 0.0;
	float _magicDefence = 0.0;
	float _physicsDefence = 0.0;
	float _movingRate = 0.0;
	float _attackRadius = 0.0;
};
//管理所有的级别时的属性值
class LevelControl {
public:
	explicit LevelControl(std::string _name);
	LevelData* getData(unsigned level);
private:
	std::vector<LevelData> _data;
};

#endif