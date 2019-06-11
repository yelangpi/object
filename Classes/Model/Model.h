#pragma once
#ifndef _MODEL_H
#define _MODEL_H

#include"cocos2d.h"
#include<string>
#include<map>
//建一个阵营的类 两个阵营
enum class Flag : std::int8_t {
	RED,
	BLUE
};
struct Buff {
	bool frozen;
	float red;
	float moveRate;
	float defence;
};
//小兵和人物的基类，继承自精灵类
//属性包含 血量 蓝值 阵营 攻击 防御
class Model :public cocos2d::Sprite {
	//血量
	CC_SYNTHESIZE(float, _hp, Hp);
	//当前血量
	CC_SYNTHESIZE(float, _currentHp, CurrentHp);
	//蓝值
	CC_SYNTHESIZE(float, _mp, Mp);
	//当前蓝值
	CC_SYNTHESIZE(float, _currentMp, CurrentMp);
	//法术攻击
	CC_SYNTHESIZE(float, _magicAttack, MagicAttack);
	//物理攻击
	CC_SYNTHESIZE(float, _physicsAttack, PhysicsAttack);
	//法术防御
	CC_SYNTHESIZE(float, _magicDefence, MagicDefence);
	//物理防御
	CC_SYNTHESIZE(float, _physicsDefence, PhysicsDefence);
	//阵营
	CC_SYNTHESIZE(Flag, _flag, Flag);
	//buff类
	CC_SYNTHESIZE(Buff, _buff, Buff);
	//移速
	CC_SYNTHESIZE(float, _movingRate, MovingRate);
	std::string _name;
public:
	Model();
	virtual ~Model();
	//用于初始化
	bool init();
	const std::string& getName();
	void setName(const std::string);
	virtual bool isDie();
	virtual void attacked(float delta);
	std::string Now_Direction = "Left";
	void setDirction_image();
protected:
	std::map<std::string,std::string> dirction_image;
};
#endif 
