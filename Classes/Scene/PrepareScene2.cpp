#include "PrepareScene2.h"
USING_NS_CC;
cocos2d::Scene* PrepareScene2::createScene()
{
	auto scene = Scene::create();
	auto layer = PrepareScene2::create();
	scene->addChild(layer);
	return scene;
}

bool PrepareScene2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto background = Sprite::create("PrepareScene1/background.png");
	Vec2 v1 = Director::getInstance()->getVisibleSize();
	Vec2 v2 = background->getContentSize();
	background->setScale(v1.x / v2.x);
	background->setPosition(v1.x / 2, v1.y / 2);
	this->addChild(background, 0);
	//
	auto BackItem2 = MenuItemImage::create(
		"button/button9.png",
		"button/button10.png",
		CC_CALLBACK_1(PrepareScene2::backCallBack, this));
	Vec2 v3 = BackItem2->getContentSize();
	BackItem2->setPosition(v3.x / 2 * 0.5, v1.y - v3.y / 2 * 0.5);
	BackItem2->setScale(0.5);
	auto menu2 = Menu::createWithItem(BackItem2);
	menu2->setPosition(0, 0);
	this->addChild(menu2, 1);
	//
	return true;
}

void PrepareScene2::backCallBack(Ref * Psender)
{
	Director::getInstance()->popScene();
}