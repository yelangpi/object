#include "LoadingScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"StartScene.h"
using namespace CocosDenshion;
USING_NS_CC;
void LoadingScene::update(float delta)
{
	static float n = 0.0f;
	n += delta;
	if (n > 1.5f)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(3,StartScene::createScene()));	
		n = 0.0f;
	}
}
cocos2d::Scene * LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//background
	
	Vec2 v1 = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("LoadingScene/tianmei.jpg");
	Vec2 v2 = background->getContentSize();
	background->setScale(v1.y / v2.y);
	background->setPosition(v1.x/2, v1.y/2);
	this->addChild(background, 0);
	//music
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("sound/yinxiao363.mp3");
	
	scheduleUpdate();

	
	return true;
}

void LoadingScene::onEnterTransitionDidFinish()
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playBackgroundMusic("sound/File0001.wav", true);
}
