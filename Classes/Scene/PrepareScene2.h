#ifndef __SCENE_PREPARESCENE2_H__
#define __SCENE_PREPARESCENE2_H__
#include "cocos2d.h"
class PrepareScene2 :public cocos2d::Layer
{
private:
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void backCallBack(Ref* Psender);
	CREATE_FUNC(PrepareScene2);
};
#endif