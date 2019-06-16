#include "StartScene.h"
#include"PrepareScene1.h"
#include"PrepareScene2.h"
#include"SettingScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}
bool StartScene::init()
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
	auto closeItem = MenuItemImage::create(
		"button/button7.png",
		"button/button8.png",
		CC_CALLBACK_1(StartScene::CloseCallback, this));
	closeItem->setPosition(v1.x / 2, v1.y / 5);
	//
	auto settingsItem = MenuItemImage::create(
		"button/button5.png",
		"button/button6.png",
		CC_CALLBACK_1(StartScene::SettingCallback, this));
	settingsItem->setPosition(v1.x / 2, v1.y / 5 * 2);
	//
	auto prepareItem = MenuItemImage::create(
		"button/button3.png",
		"button/button4.png",
		CC_CALLBACK_1(StartScene::PrepareCallback2, this));
	prepareItem->setPosition(v1.x / 2, v1.y / 5 * 3);
	//
	auto prepareItem2 = MenuItemImage::create(
		"button/button1.png",
		"button/button2.png",
		CC_CALLBACK_1(StartScene::PrepareCallback, this));
	prepareItem2->setPosition(v1.x / 2, v1.y / 5 * 4);
	//
	auto menu = Menu::create(closeItem, settingsItem, prepareItem, prepareItem2,NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
	return true;
}
void StartScene::CloseCallback(Ref * psender)
{
	Director::getInstance()->end();
}

void StartScene::SettingCallback(Ref * psender)
{
	Director::getInstance()->pushScene(TransitionFade::create(3, SettingScene::createScene()));
}

void StartScene::PrepareCallback(Ref * psender)
{
	Director::getInstance()->pushScene(TransitionFade::create(3, PrepareScene1::createScene()));
}

void StartScene::PrepareCallback2(Ref * psender)
{
	Director::getInstance()->pushScene(TransitionFade::create(3, PrepareScene2::createScene()));
}
