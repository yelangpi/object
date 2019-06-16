#include "SettingScene.h"
USING_NS_CC;
cocos2d::Scene * SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
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
	auto setting = Sprite::create("SettingScene/SettingScene.png");
	setting->setScale(2.0);
	setting->setPosition(v1.x / 2, v1.y / 2);
	this->addChild(setting, 0);
	//
	auto backItem = MenuItemImage::create(
		"button/button9.png",
		"button/button10.png",
		CC_CALLBACK_1(SettingScene::backCallBack, this));
	Vec2 v3 = backItem->getContentSize();
	backItem->getSelectedImage()->setScale(0.7);
	backItem->setScale(1.0);
	backItem->setPosition(v3.x / 2, v1.y - v3.y / 2);
	auto menu = Menu::createWithItem(backItem);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
	return true;
}

void SettingScene::backCallBack(Ref* Psender)
{
	Director::getInstance()->popScene();
}