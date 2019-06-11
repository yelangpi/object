#pragma once
#ifndef _MODEL_H
#define _MODEL_H

#include"cocos2d.h"
#include<string>
#include<map>
//��һ����Ӫ���� ������Ӫ
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
//С��������Ļ��࣬�̳��Ծ�����
//���԰��� Ѫ�� ��ֵ ��Ӫ ���� ����
class Model :public cocos2d::Sprite {
	//Ѫ��
	CC_SYNTHESIZE(float, _hp, Hp);
	//��ǰѪ��
	CC_SYNTHESIZE(float, _currentHp, CurrentHp);
	//��ֵ
	CC_SYNTHESIZE(float, _mp, Mp);
	//��ǰ��ֵ
	CC_SYNTHESIZE(float, _currentMp, CurrentMp);
	//��������
	CC_SYNTHESIZE(float, _magicAttack, MagicAttack);
	//������
	CC_SYNTHESIZE(float, _physicsAttack, PhysicsAttack);
	//��������
	CC_SYNTHESIZE(float, _magicDefence, MagicDefence);
	//�������
	CC_SYNTHESIZE(float, _physicsDefence, PhysicsDefence);
	//��Ӫ
	CC_SYNTHESIZE(Flag, _flag, Flag);
	//buff��
	CC_SYNTHESIZE(Buff, _buff, Buff);
	//����
	CC_SYNTHESIZE(float, _movingRate, MovingRate);
	std::string _name;
public:
	Model();
	virtual ~Model();
	//���ڳ�ʼ��
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
