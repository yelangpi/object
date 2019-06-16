#pragma once
#ifndef __SCENE_ENDSCENE_H_
#define __SCENE_ENDSCENE_H_
#include "cocos2d.h"
class EndScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createWithBool(bool c);
	virtual bool initb(bool c);
	static EndScene* createb(bool c);
	void backCallBack(Ref* Psender);
private:
};
#endif