#include "PrepareScene1.h"
#include"GameScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * PrepareScene1::createScene()
{
	auto scene = Scene::create();
	auto layer = PrepareScene1::create();
	scene->addChild(layer);
	return scene;
}

bool PrepareScene1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto background = Sprite::create("PrepareScene1/background.png");
	Vec2 v1 = Director::getInstance()->getWinSize();
	Vec2 v4 = background->getContentSize();
	background->setScale(v1.x / v4.x);
	background->setPosition(v1.x / 2, v1.y / 2);
	this->addChild(background, 0);
	//
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadEffect("DaJi/chuchangmusic.mp3");
	audioengine->preloadEffect("HouYi/chuchangmusic.mp3");
	audioengine->preloadEffect("YaSe/chuchangmusic.mp3");
	//
	auto BackItem = MenuItemImage::create(
		"button/button9.png",
		"button/button10.png",
		CC_CALLBACK_1(PrepareScene1::BackCallback, this));
	Vec2 v2 = BackItem->getContentSize();
	BackItem->setPosition(v2.x / 2 * 0.5, v1.y - v2.y / 2 * 0.5);
	BackItem->setScale(0.5);
	//
	auto PlayerWord = Sprite::create("PrepareScene1/player.png");
	PlayerWord->setPosition(v1.x / 3, 7 * v1.y / 8);
	this->addChild(PlayerWord, 1);
	auto ComputerWord = Sprite::create("PrepareScene1/computer.png");
	ComputerWord->setScale(1.5);
	ComputerWord->setPosition(2 * v1.x / 3, 7 * v1.y / 8);
	this->addChild(ComputerWord, 1);
	//
	auto PlayerItem1 = MenuItemImage::create(
		"DaJi/touxiang.png",
		"DaJi/touxiang.png",
		CC_CALLBACK_1(PrepareScene1::playerCallback1, this));
	PlayerItem1->setScale(2.0);
	PlayerItem1->setPosition(v1.x / 3, 3 * v1.y / 4);
	_playerbutton1 = PlayerItem1;
	//
	auto PlayerItem2 = MenuItemImage::create(
		"HouYi/touxiang.png",
		"HouYi/touxiang.png",
		CC_CALLBACK_1(PrepareScene1::playerCallback2, this));
	PlayerItem2->setPosition(v1.x / 3, 2 * v1.y / 4);
	PlayerItem2->setScale(2.0);
	_playerbutton2 = PlayerItem2;
	//
	auto PlayerItem3 = MenuItemImage::create(
		"YaSe/touxiang.png",
		"YaSe/touxiang.png",
		CC_CALLBACK_1(PrepareScene1::playerCallback3, this));
	PlayerItem3->setPosition(v1.x / 3, v1.y / 4);
	PlayerItem3->setScale(2.0);
	_playerbutton3 = PlayerItem3;
	//
	auto PlayerSelected1 = Sprite::create("DaJi/touxiang-xuanzhong.png");
	PlayerSelected1->setScale(2.0);
	PlayerSelected1->setPosition(v1.x / 3, 3 * v1.y / 4);
	PlayerSelected1->setVisible(false);
	this->addChild(PlayerSelected1, 1);
	_playerselected1 = PlayerSelected1;
	//
	auto PlayerSelected2 = Sprite::create("HouYi/touxiang-xuanzhong.png");
	PlayerSelected2->setScale(2.0);
	PlayerSelected2->setPosition(v1.x / 3, 2 * v1.y / 4);
	PlayerSelected2->setVisible(false);
	this->addChild(PlayerSelected2, 1);
	_playerselected2 = PlayerSelected2;
	//
	auto PlayerSelected3 = Sprite::create("YaSe/touxiang-xuanzhong.png");
	PlayerSelected3->setScale(2.0);
	PlayerSelected3->setPosition(v1.x / 3, v1.y / 4);
	PlayerSelected3->setVisible(false);
	this->addChild(PlayerSelected3, 1);
	_playerselected3 = PlayerSelected3;
	//
	auto ComputerItem1 = MenuItemImage::create(
		"DaJi/touxiang.png",
		"DaJi/touxiang.png",
		CC_CALLBACK_1(PrepareScene1::computerCallback1, this));
	ComputerItem1->setPosition(2 * v1.x / 3, 3 * v1.y / 4);
	ComputerItem1->setScale(2.0);
	_computerbutton1 = ComputerItem1;
	//
	auto ComputerItem2 = MenuItemImage::create(
		"HouYi/touxiang.png",
		"HouYi/touxiang.png",
		CC_CALLBACK_1(PrepareScene1::computerCallback2, this));
	ComputerItem2->setPosition(2 * v1.x / 3, 2 * v1.y / 4);
	ComputerItem2->setScale(2.0);
	_computerbutton2 = ComputerItem2;
	//
	auto ComputerItem3 = MenuItemImage::create(
		"YaSe/touxiang.png",
		"YaSe/touxiang.png",
		CC_CALLBACK_1(PrepareScene1::computerCallback3, this));
	ComputerItem3->setPosition(2 * v1.x / 3, v1.y / 4);
	ComputerItem3->setScale(2.0);
	_computerbutton3 = ComputerItem3;
	//
	auto ComputerSelected1 = Sprite::create("DaJi/touxiang-xuanzhong.png");
	ComputerSelected1->setScale(2.0);
	ComputerSelected1->setPosition(2 * v1.x / 3, 3 * v1.y / 4);
	ComputerSelected1->setVisible(false);
	this->addChild(ComputerSelected1, 1);
	_computerselected1 = ComputerSelected1;
	//
	auto ComputerSelected2 = Sprite::create("HouYi/touxiang-xuanzhong.png");
	ComputerSelected2->setScale(2.0);
	ComputerSelected2->setPosition(2 * v1.x / 3, 2 * v1.y / 4);
	ComputerSelected2->setVisible(false);
	this->addChild(ComputerSelected2, 1);
	_computerselected2 = ComputerSelected2;
	//
	auto ComputerSelected3 = Sprite::create("YaSe/touxiang-xuanzhong.png");
	ComputerSelected3->setScale(2.0);
	ComputerSelected3->setPosition(2 * v1.x / 3, v1.y / 4);
	ComputerSelected3->setVisible(false);
	this->addChild(ComputerSelected3, 1);
	_computerselected3 = ComputerSelected3;
	//
	auto StartItem = MenuItemImage::create(
		"button/button1.png",
		"button/button2.png",
		CC_CALLBACK_1(PrepareScene1::StartGameCallback, this));
	StartItem->setPosition(v1.x / 2, v1.y / 8);
	StartItem->setEnabled(false);
	_startbutton = StartItem;
	//
	auto menu = Menu::create(BackItem, PlayerItem1, PlayerItem2, PlayerItem3, ComputerItem1, ComputerItem2, ComputerItem3, StartItem, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
	//
	return true;
}



void PrepareScene1::BackCallback(Ref * Psender)
{
	Director::getInstance()->popScene();
}

void PrepareScene1::playerCallback1(Ref * Psender)
{
	_playerbutton1->setVisible(false);
	_playerselected1->setVisible(true);
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("DaJi/chuchangmusic.mp3");
	if (_playernumber == 1)
	{
		_playerbutton1->setVisible(true);
		_playerselected1->setVisible(false);
	}
	else if (_playernumber == 2)
	{
		_playerbutton2->setVisible(true);
		_playerselected2->setVisible(false);
	}
	else if (_playernumber == 3)
	{
		_playerbutton3->setVisible(true);
		_playerselected3->setVisible(false);
	}
	_playernumber = 1;
	if (_playernumber&&_computernumber)
	{
		_startbutton->setEnabled(true);
	}
}
void PrepareScene1::playerCallback2(Ref * Psender)
{
	_playerbutton2->setVisible(false);
	_playerselected2->setVisible(true);
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("HouYi/chuchangmusic.mp3");
	if (_playernumber == 1)
	{
		_playerbutton1->setVisible(true);
		_playerselected1->setVisible(false);
	}
	else if (_playernumber == 2)
	{
		_playerbutton2->setVisible(true);
		_playerselected2->setVisible(false);
	}
	else if (_playernumber == 3)
	{
		_playerbutton3->setVisible(true);
		_playerselected3->setVisible(false);
	}
	_playernumber = 2;
	if (_playernumber&&_computernumber)
	{
		_startbutton->setEnabled(true);
	}
}
void PrepareScene1::playerCallback3(Ref * Psender)
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("YaSe/chuchangmusic.mp3");
	_playerbutton3->setVisible(false);
	_playerselected3->setVisible(true);
	if (_playernumber == 1)
	{
		_playerbutton1->setVisible(true);
		_playerselected1->setVisible(false);
	}
	else if (_playernumber == 2)
	{
		_playerbutton2->setVisible(true);
		_playerselected2->setVisible(false);
	}
	else if (_playernumber == 3)
	{
		_playerbutton3->setVisible(true);
		_playerselected3->setVisible(false);
	}
	_playernumber = 3;
	if (_playernumber&&_computernumber)
	{
		_startbutton->setEnabled(true);
	}
}

void PrepareScene1::computerCallback1(Ref * Psender)
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("DaJi/chuchangmusic.mp3");
	_computerbutton1->setVisible(false);
	_computerselected1->setVisible(true);
	if (_computernumber == 1)
	{
		_computerbutton1->setVisible(true);
		_computerselected1->setVisible(false);
	}
	else if (_computernumber == 2)
	{
		_computerbutton2->setVisible(true);
		_computerselected2->setVisible(false);
	}
	else if (_computernumber == 3)
	{
		_computerbutton3->setVisible(true);
		_computerselected3->setVisible(false);
	}
	_computernumber = 1;
	if (_playernumber&&_computernumber)
	{
		_startbutton->setEnabled(true);
	}
}
void PrepareScene1::computerCallback2(Ref * Psender)
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("HouYi/chuchangmusic.mp3");
	_computerbutton2->setVisible(false);
	_computerselected2->setVisible(true);
	if (_computernumber == 1)
	{
		_computerbutton1->setVisible(true);
		_computerselected1->setVisible(false);
	}
	else if (_computernumber == 2)
	{
		_computerbutton2->setVisible(true);
		_computerselected2->setVisible(false);
	}
	else if (_computernumber == 3)
	{
		_computerbutton3->setVisible(true);
		_computerselected3->setVisible(false);
	}
	_computernumber = 2;
	if (_playernumber&&_computernumber)
	{
		_startbutton->setEnabled(true);
	}
}
void PrepareScene1::computerCallback3(Ref * Psender)
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("YaSe/chuchangmusic.mp3");
	_computerbutton3->setVisible(false);
	_computerselected3->setVisible(true);
	if (_computernumber == 1)
	{
		_computerbutton1->setVisible(true);
		_computerselected1->setVisible(false);
	}
	else if (_computernumber == 2)
	{
		_computerbutton2->setVisible(true);
		_computerselected2->setVisible(false);
	}
	else if (_computernumber == 3)
	{
		_computerbutton3->setVisible(true);
		_computerselected3->setVisible(false);
	}
	_computernumber = 3;
	if (_playernumber&&_computernumber)
	{
		_startbutton->setEnabled(true);
	}
}
void PrepareScene1::StartGameCallback(Ref * Psender)
{
	std::string name[3] = { "DaJi","HouYi","YaSe" };
	Director::getInstance()->replaceScene(TransitionFade::create(3, GameScene::createScene(name[_playernumber - 1], name[_computernumber - 1])));
}