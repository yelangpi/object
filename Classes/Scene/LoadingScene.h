#ifndef __SCENE_LOADINGSCENE_H__
#define __SCENE_LOADINGSCENE_H__

#include "cocos2d.h"
class LoadingScene : public cocos2d::Layer
{
private:
	virtual void update(float delta);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	CREATE_FUNC(LoadingScene);
};

#endif