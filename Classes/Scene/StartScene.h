#ifndef __SCENE_STARTSCENE_H__
#define __SCENE_STARTSCENE_H__
#include "cocos2d.h"
class StartScene : public cocos2d::Layer
{
private:
	
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void CloseCallback(Ref* psender);
	void SettingCallback(Ref* psender);
	void PrepareCallback(Ref* psender);
	void PrepareCallback2(Ref* psender);
	CREATE_FUNC(StartScene);
};

#endif
