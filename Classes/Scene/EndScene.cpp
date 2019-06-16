#include"EndScene.h"
#include"StartScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
cocos2d::Scene * EndScene::createWithBool(bool c)
{
	auto scene = Scene::create();
	auto layer = EndScene::createb(c);
	scene->addChild(layer);
	return scene;
}

bool EndScene::initb(bool c)
{
	if (!Layer::init())
	{
		return false;
	}
	Vec2 v1 = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("StartScene/background.jpg");
	Vec2 v2 = background->getContentSize();
	background->setScale(v1.y / v2.y);
	background->setPosition(v1.x / 2, v1.y / 2);
	this->addChild(background, 0);
	//
	
	auto backItem = MenuItemImage::create(
		"button/button9.png",
		"button/button10.png",
		CC_CALLBACK_1(EndScene::backCallBack, this));
	Vec2 v3 = backItem->getContentSize();
	backItem->setScale(1.0);
	backItem->setPosition(v3.x / 2, v1.y - v3.y / 2);
	auto menu = Menu::createWithItem(backItem);
	menu->setPosition(0, 0);
	Sprite*sprite;
	if (c)
	{
		sprite = Sprite::create("shengli.png");
		auto audioengine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioengine->playEffect("victory.wav");
	}
	else
	{
		sprite = Sprite::create("shibai.png");
		auto audioengine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioengine->playEffect("defeat.wav");
	}
	sprite->setPosition(v1.x / 2, v1.y / 2);
	this->addChild(sprite, 2);
	this->addChild(menu, 1);
	return true;
}

EndScene * EndScene::createb(bool c)
{
	EndScene *pRet = new(std::nothrow) EndScene();
	if (pRet && pRet->initb(c)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = nullptr; 
		return nullptr; 
	} 
}

void EndScene::backCallBack(Ref* Psender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(3, StartScene::createScene()));
}