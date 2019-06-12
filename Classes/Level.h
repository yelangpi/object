#pragma once
#ifndef _LEVEL_H
#define _LEVEL_H
#include"Model/Model.h"
#include<vector>
#include<string>
//ÿһ���ȼ���Ӧ���е�����ȫ�������������LevelData������
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
//�������еļ���ʱ������ֵ
class LevelControl {
public:
	explicit LevelControl(std::string _name);
	LevelData* getData(unsigned level);
private:
	std::vector<LevelData> _data;
};

#endif