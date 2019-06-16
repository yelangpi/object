#ifndef __SCENE_SETTINGSCENE_H_
#define __SCENE_SETTINGSCENE_H_
#include "cocos2d.h"
class SettingScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void backCallBack(Ref* Psender);
	CREATE_FUNC(SettingScene);
private:
};
#endif