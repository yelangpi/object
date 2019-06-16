#include "GameScene2.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"Model/Hero.h"
#include "Order.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * GameScene2::createScene(std::string name1, std::string name2, chat_client* _client, char FLAG)
{
	auto scene = Scene::create();
	auto layer = GameScene2::createWithName(name1, name2, _client, FLAG);

	scene->addChild(layer, 0);
	return scene;
}

bool GameScene2::initWithName(std::string name1, std::string name2, chat_client* _client, char FLAG)
{
	if (!Layer::init())
	{
		return false;
	}
	Vec2 v1 = Director::getInstance()->getWinSize();
	order.FLAG = FLAG;
	if (FLAG == 'B') {
		this->_PlayerName = name1;
		this->_EnemyName = name2;
	}
	if (FLAG == 'R') {
		this->_PlayerName = name2;
		this->_EnemyName = name1;
	}
	initMap();
	initAnimation();
	initHero(FLAG);
	initSkill();
	initTower();
	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene2::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene2::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	//创建一个客户端，当前这个init函数里为gamescene生成一个客户端
	//然后通过这个客户端来传信息
	client = _client;
	scheduleUpdate();

	return true;
}
//
GameScene2 * GameScene2::createWithName(std::string name1, std::string name2, chat_client* _client, char FLAG)
{
	GameScene2 *pRet = new(std::nothrow) GameScene2();
	if (pRet && pRet->initWithName(name1, name2, _client, FLAG))
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
//对player是调用这么一个函数
void GameScene2::Answering(const Order& tmpOrder) {
	int status[8] = { 0 };
	if (preOrder.KEY_W && !tmpOrder.KEY_W)
		status[0] = 2;
	else if (!preOrder.KEY_W&&tmpOrder.KEY_W)
		status[0] = 1;
	//
	if (preOrder.KEY_S && !tmpOrder.KEY_S)
		status[1] = 2;
	else if (!preOrder.KEY_S&&tmpOrder.KEY_S)
		status[1] = 1;
	//
	if (preOrder.KEY_A && !tmpOrder.KEY_A)
		status[2] = 2;
	else if (!preOrder.KEY_A&&tmpOrder.KEY_A)
		status[2] = 1;
	//
	if (preOrder.KEY_D && !tmpOrder.KEY_D)
		status[3] = 2;
	else if (!preOrder.KEY_D&&tmpOrder.KEY_D)
		status[3] = 1;
	//
	if (preOrder.KEY_J && !tmpOrder.KEY_J)
		status[4] = 2;
	else if (!preOrder.KEY_J&&tmpOrder.KEY_J)
		status[4] = 1;
	//
	if (preOrder.KEY_1 && !tmpOrder.KEY_1)
		status[5] = 2;
	else if (!preOrder.KEY_1&&tmpOrder.KEY_1)
		status[5] = 1;
	//
	if (preOrder.KEY_2 && !tmpOrder.KEY_2)
		status[6] = 2;
	else if (!preOrder.KEY_2&&tmpOrder.KEY_2)
		status[6] = 1;
	//
	if (preOrder.KEY_3 && !tmpOrder.KEY_3)
		status[7] = 2;
	else if (!preOrder.KEY_3&&tmpOrder.KEY_3)
		status[7] = 1;
	preOrder = tmpOrder;
	this->YLP_W(status[0]);
	this->YLP_S(status[1]);
	this->YLP_A(status[2]);
	this->YLP_D(status[3]);
	this->YLP_J(status[4]);
	this->YLP_1(status[5]);
	this->YLP_2(status[6]);
	this->YLP_3(status[7]);
}
//然后对enemy是调用这么一个函数
void GameScene2::AnsweringEnemy(const Order& tmpOrder) {
	int status[8] = { 0 };
	if (preOrderEnemy.KEY_W && !tmpOrder.KEY_W)
		status[0] = 2;
	else if (!preOrderEnemy.KEY_W&&tmpOrder.KEY_W)
		status[0] = 1;
	//
	if (preOrderEnemy.KEY_S && !tmpOrder.KEY_S)
		status[1] = 2;
	else if (!preOrderEnemy.KEY_S&&tmpOrder.KEY_S)
		status[1] = 1;
	//
	if (preOrderEnemy.KEY_A && !tmpOrder.KEY_A)
		status[2] = 2;
	else if (!preOrderEnemy.KEY_A&&tmpOrder.KEY_A)
		status[2] = 1;
	//
	if (preOrderEnemy.KEY_D && !tmpOrder.KEY_D)
		status[3] = 2;
	else if (!preOrderEnemy.KEY_D&&tmpOrder.KEY_D)
		status[3] = 1;
	//
	if (preOrderEnemy.KEY_J && !tmpOrder.KEY_J)
		status[4] = 2;
	else if (!preOrderEnemy.KEY_J&&tmpOrder.KEY_J)
		status[4] = 1;
	//
	if (preOrderEnemy.KEY_1 && !tmpOrder.KEY_1)
		status[5] = 2;
	else if (!preOrderEnemy.KEY_1&&tmpOrder.KEY_1)
		status[5] = 1;
	//
	if (preOrderEnemy.KEY_2 && !tmpOrder.KEY_2)
		status[6] = 2;
	else if (!preOrderEnemy.KEY_2&&tmpOrder.KEY_2)
		status[6] = 1;
	//
	if (preOrderEnemy.KEY_3 && !tmpOrder.KEY_3)
		status[7] = 2;
	else if (!preOrderEnemy.KEY_3&&tmpOrder.KEY_3)
		status[7] = 1;
	preOrderEnemy = tmpOrder;
	this->YLP_ENEMY_W(status[0]);
	this->YLP_ENEMY_S(status[1]);
	this->YLP_ENEMY_A(status[2]);
	this->YLP_ENEMY_D(status[3]);
	this->YLP_ENEMY_J(status[4]);
	this->YLP_ENEMY_1(status[5]);
	this->YLP_ENEMY_2(status[6]);
	this->YLP_ENEMY_3(status[7]);
}

//记得修改接包的部分 Order改了
void GameScene2::update(float delta)
{
	//接收一个从服务器里接到的包
	Order tmpOrder;
	//发送消息
	chat_message send = order.orderToMessage();
	client->write(send);
	//接收消息
	client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();
		//获得了一个指令，这个指令包含了对象和模拟的键盘操作
		tmpOrder = messageToOrder(tmpStr);
		CCLOG(tmpStr.c_str());
		if (tmpOrder.FLAG == order.FLAG) {
			this->Answering(tmpOrder);
		}
		else
			this->AnsweringEnemy(tmpOrder);

	}
	client->t_lock.unlock();
	/*
		0 W
		1 S
		2 A
		3 D
		4 J
		5 ONE
		6 TWO
		7 THR
	*/


	_player->Move(delta);
	_enemy->Move(delta);
	if (!_soldier.empty())
	{
		for (auto i = _soldier.begin(); i != _soldier.end(); )
		{
			if ((*i)->isDie())
			{
				(*i)->setVisible(false);
				(*i)->_HPbox->setVisible(false);
				(*i)->_HPrectangle->setVisible(false);
				if (std::find(enemy_flag.begin(), enemy_flag.end(), *i) != enemy_flag.end())
					enemy_flag.erase(std::find(enemy_flag.begin(), enemy_flag.end(), *i));
				if (std::find(player_flag.begin(), player_flag.end(), *i) != player_flag.end())
					player_flag.erase(std::find(player_flag.begin(), player_flag.end(), *i));
				i = _soldier.erase(i);
			}
			else
			{
				(*i)->Move(delta);
				i++;
			}
		}
	}
	long long now_time = GetCurrentTime();
	doFlying();
	doButterfly();
	doRangeSkill();
	doShield();
	SkillTime();

	initSoldier();
	doImpactWave();
	towerAttack();
	MoveMap(delta);
	doHP();
if (_player->isDie() && now_time > _player->revive_time)
	{
		_enemy->setExp(_enemy->getExp() + 100);
		_player->setPosition(_player->born_position);
		_player->setVisible(true);
		_player->setCurrentHp(_player->getHp());
		_player->isV = true;
	}
	if (_enemy->isDie() && now_time > _enemy->revive_time)
	{
		_player->setExp(_enemy->getExp() + 100);
		_enemy->setPosition(_enemy->born_position);
		_enemy->setVisible(true);
		_enemy->setCurrentHp(_enemy->getHp());
		_enemy->isV = true;
	}
	soldierAI();
	//enemyAI();
	if (_redcrystal->isDie())
	{
		if (_player->getFlag() == Flag::RED)
		{
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, EndScene::createWithBool(0)));
		}
		else
		{
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, EndScene::createWithBool(1)));
		}
	}
	if (_bluecrystal->isDie())
	{
		if (_player->getFlag() == Flag::BLUE)
		{
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, EndScene::createWithBool(0)));
		}
		else
		{
			Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(3, EndScene::createWithBool(1)));
		}
	}
	if (_player->isDie())
	{
		TT->setVisible(1);
		TT->setString(std::to_string((_player->revive_time - now_time) / 1000+1) );
	}

	else
	{
		TT->setVisible(0);
	}
	std::string s1 = std::to_string(_enemy->head);
	std::string s2 = std::to_string(_player->head);
	std::string ss = s1 + ':' + s2;
	ZZ->setString(ss);
	std::string s3 = std::to_string(_player->getMoney());
	std::string s4 = "money:" + s3;
	MM->setString(s4);
}
//status 0->无响应
//		1 按下
//      2 松开
void GameScene2::YLP_W(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = true;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left-Down");
			_player->WalkWithDirection("Left-Up");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right-Down");
			_player->WalkWithDirection("Right-Up");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Down");
			_player->WalkWithDirection("Up");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left");
			_player->WalkWithDirection("Left-Up");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right");
			_player->WalkWithDirection("Right-Up");
			return;
		}
		_player->WalkWithDirection("Up");
		return;
	}
	else if (status == 2) {
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W])
			return;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left-Up");
			_player->WalkWithDirection("Left");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right-Up");
			_player->WalkWithDirection("Right");
			return;
		}

		_player->StopWalking("Up");
	}
}
void GameScene2::YLP_S(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = true;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left-Up");
			_player->WalkWithDirection("Left-Down");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right-Up");
			_player->WalkWithDirection("Right-Down");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Up");
			_player->WalkWithDirection("Down");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right");
			_player->WalkWithDirection("Right-Down");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left");
			_player->WalkWithDirection("Left-Down");
			return;
		}

		_player->WalkWithDirection("Down");
		return;
	}
	else if (status == 2) {
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S])
			return;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left-Down");
			_player->WalkWithDirection("Left");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right-Down");
			_player->WalkWithDirection("Right");
			return;
		}
		_player->StopWalking("Down");
	}
}
void GameScene2::YLP_A(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = true;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Right-Up");
			_player->WalkWithDirection("Left-Up");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Right-Down");
			_player->WalkWithDirection("Left-Down");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right");
			_player->WalkWithDirection("Left");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Up");
			_player->WalkWithDirection("Left-Up");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Down");
			_player->WalkWithDirection("Left-Down");
			return;
		}

		_player->WalkWithDirection("Left");
		return;
	}
	else if (status == 2) {
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
			return;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Left-Down");
			_player->WalkWithDirection("Down");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Left-Up");
			_player->WalkWithDirection("Up");
			return;
		}
		_player->StopWalking("Left");
	}
}
void GameScene2::YLP_D(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = true;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Left-Up");
			_player->WalkWithDirection("Right-Up");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Left-Down");
			_player->WalkWithDirection("Right-Down");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left");
			_player->WalkWithDirection("Right");
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Up");
			_player->WalkWithDirection("Right-Up");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Down");
			_player->WalkWithDirection("Right-Down");
			return;
		}

		_player->WalkWithDirection("Right");
		return;
	}
	else if (status == 2) {
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
			return;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Right-Down");
			_player->WalkWithDirection("Down");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Right-Up");
			_player->WalkWithDirection("Up");
			return;
		}
		_player->StopWalking("Right");
	}
}
void GameScene2::YLP_J(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		playerAttack();
		return;
	}
	else if (status == 2) {
		return;
	}
}
void GameScene2::YLP_1(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		playerAttack_1();
		return;
	}
	else if (status == 2) {
		return;
	}
}
void GameScene2::YLP_2(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		playerAttack_2();
		return;
	}
	else if (status == 2) {
		return;
	}
}
void GameScene2::YLP_3(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		playerAttack_3();
		return;
	}
	else if (status == 2) {
		return;
	}
}
//
void GameScene2::YLP_ENEMY_W(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = true;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left-Down");
			_enemy->WalkWithDirection("Left-Up");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right-Down");
			_enemy->WalkWithDirection("Right-Up");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Down");
			_enemy->WalkWithDirection("Up");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left");
			_enemy->WalkWithDirection("Left-Up");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right");
			_enemy->WalkWithDirection("Right-Up");
			return;
		}
		_enemy->WalkWithDirection("Up");
		return;
	}
	else if (status == 2) {
		if (!_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W])
			return;
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left-Up");
			_enemy->WalkWithDirection("Left");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right-Up");
			_enemy->WalkWithDirection("Right");
			return;
		}

		_enemy->StopWalking("Up");
	}
}
void GameScene2::YLP_ENEMY_S(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = true;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left-Up");
			_enemy->WalkWithDirection("Left-Down");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right-Up");
			_enemy->WalkWithDirection("Right-Down");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Up");
			_enemy->WalkWithDirection("Down");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right");
			_enemy->WalkWithDirection("Right-Down");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left");
			_enemy->WalkWithDirection("Left-Down");
			return;
		}

		_enemy->WalkWithDirection("Down");
		return;
	}
	else if (status == 2) {
		if (!_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S])
			return;
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left-Down");
			_enemy->WalkWithDirection("Left");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right-Down");
			_enemy->WalkWithDirection("Right");
			return;
		}
		_enemy->StopWalking("Down");
	}
}
void GameScene2::YLP_ENEMY_A(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = true;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Right-Up");
			_enemy->WalkWithDirection("Left-Up");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Right-Down");
			_enemy->WalkWithDirection("Left-Down");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_enemy->StopWalking("Right");
			_enemy->WalkWithDirection("Left");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Up");
			_enemy->WalkWithDirection("Left-Up");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Down");
			_enemy->WalkWithDirection("Left-Down");
			return;
		}

		_enemy->WalkWithDirection("Left");
		return;
	}
	else if (status == 2) {
		if (!_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
			return;
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Left-Down");
			_enemy->WalkWithDirection("Down");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Left-Up");
			_enemy->WalkWithDirection("Up");
			return;
		}
		_enemy->StopWalking("Left");
	}
}
void GameScene2::YLP_ENEMY_D(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		if (!isAp) {
			isAp = true;
			_soldiertime = GetCurrentTime() + 5000;
		}
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = true;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Left-Up");
			_enemy->WalkWithDirection("Right-Up");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] && _enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Left-Down");
			_enemy->WalkWithDirection("Right-Down");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_enemy->StopWalking("Left");
			_enemy->WalkWithDirection("Right");
			_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Up");
			_enemy->WalkWithDirection("Right-Up");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Down");
			_enemy->WalkWithDirection("Right-Down");
			return;
		}

		_enemy->WalkWithDirection("Right");
		return;
	}
	else if (status == 2) {
		if (!_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
			return;
		_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_enemy->StopWalking("Right-Down");
			_enemy->WalkWithDirection("Down");
			return;
		}
		if (_enemy->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_enemy->StopWalking("Right-Up");
			_enemy->WalkWithDirection("Up");
			return;
		}
		_enemy->StopWalking("Right");
	}
}
void GameScene2::YLP_ENEMY_J(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		enemyAttack();
		return;
	}
	else if (status == 2) {
		return;
	}
}
void GameScene2::YLP_ENEMY_1(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		enemyAttack_1();
		return;
	}
	else if (status == 2) {
		return;
	}
}
void GameScene2::YLP_ENEMY_2(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		enemyAttack_2();
		return;
	}
	else if (status == 2) {
		return;
	}
}
void GameScene2::YLP_ENEMY_3(int status) {
	if (status == 0) {
		return;
	}
	else if (status == 1) {
		enemyAttack_3();
		return;
	}
	else if (status == 2) {
		return;
	}
}

void GameScene2::onEnterTransitionDidFinish()
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playBackgroundMusic("sound/File0001.wav", true);
}
void GameScene2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	if (!_player->isDie() && GetCurrentTime() > _player->getEndTime()) {
		switch (keycode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_W:

			order.KEY_W = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:

			order.KEY_S = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:

			order.KEY_D = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:

			order.KEY_A = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			order.KEY_J = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			order.KEY_1 = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			order.KEY_2 = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
			order.KEY_3 = true;
			break;
		default:
			break;
		}
	}
}
void GameScene2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		order.KEY_W = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		order.KEY_S = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		order.KEY_D = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		order.KEY_A = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		order.KEY_J = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		order.KEY_1 = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		order.KEY_2 = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		order.KEY_3 = false;
		break;
	default:
		break;
	}
}

void GameScene2::LoadingYaSeAnimation()
{
	std::string dir[8] = { "Up","Down","Left","Right","Left-Up","Left-Down","Right-Up","Right-Down" };
	Animation* animation_00[8];
	for (int i = 0; i < 8; i++)
	{
		animation_00[i] = Animation::create();
		for (int j = 0; j <= Dirction_Animation_Attack_Number[std::make_pair("YaSe", dir[i])]; j++)
		{
			animation_00[i]->addSpriteFrameWithFile(StringUtils::format("%s/%s/Attack/%s/000%d.PNG", "YaSe", "YaSe", dir[i].c_str(), j));
		}
		animation_00[i]->setDelayPerUnit(0.25f);
		animation_00[i]->setLoops(1);
		AnimationCache::getInstance()->addAnimation(animation_00[i], StringUtils::format("%s_attack_%s", "YaSe", dir[i].c_str()));
	}
}
void GameScene2::LoadingAnimation(std::string sprite_name)
{
	std::string dir[8] = { "Up","Down","Left","Right","Left-Up","Left-Down","Right-Up","Right-Down" };
	Animation* animation_00[8];
	for (int i = 0; i < 8; i++)
	{
		animation_00[i] = Animation::create();
		for (int j = 1; j <= Dirction_Animation_Walk_Number[std::make_pair(sprite_name, dir[i])]; j++)
		{
			animation_00[i]->addSpriteFrameWithFile(StringUtils::format("%s/%s/Walk/%s/000%d.PNG", sprite_name.c_str(), sprite_name.c_str(), dir[i].c_str(), j));
		}
		animation_00[i]->setDelayPerUnit(0.25f);
		animation_00[i]->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(animation_00[i], StringUtils::format("%s_%s", sprite_name.c_str(), dir[i].c_str()));
	}
}

void GameScene2::playerAttack()
{
	if (_player->getName() == "DaJi")
	{
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			f->target.push_back(_enemy);
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 500 * 500)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime >= 500 && GetEnemy) {
			_player->_attackTime = GetCurrentTime();
			if (_player->getEndTime() < GetCurrentTime() + 250)
				_player->setEndTime(GetCurrentTime() + 250);
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			f->setInjure(_player->getPhysicsAttack());
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 10);
		}
	}
	else if (_player->getName() == "YaSe")
	{
		auto dir = _player->Now_Direction;
		_player->stopAllActions();
		Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack_%s", _player->getName().c_str(), dir.c_str()));
		Animate *action = Animate::create(animation);
		_player->runAction(action);
		if (_player->getEndTime() < GetCurrentTime() + 1000)
			_player->setEndTime(GetCurrentTime() + 1000);
		if (!_enemy->isDie())
		{
			Vec2 v1 = _player->getPosition();
			Vec2 v2 = _enemy->getPosition();
			Vec2 v = v2 - v1;
			auto dir = _player->Now_Direction;
			if (v1.getDistance(v2) < 200)
			{
				if (dir == "Left")
				{
					if ((v.getAngle() >= 3.14 / 2 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 2))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - _player->getPhysicsAttack() + _enemy->getPhysicsDefence());
					}
				}
			}
		}
		for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
		{
			Vec2 v1 = _player->getPosition();
			Vec2 v2 = (*i)->getPosition();
			Vec2 v = v2 - v1;
			auto dir = _player->Now_Direction;
			if (v1.getDistance(v2) < 200)
			{
				if (dir == "Left")
				{
					if ((v.getAngle() >= 3.14 / 2 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 2))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _player->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
			}
		}
	}
	else if (_player->getName() == "HouYi")
	{
		bool GetEnemy = false;
		Model* cc;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("HouYi/HouYi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 600 * 600)
		{
			f->target.push_back(_enemy);
			if (!GetEnemy)cc = _enemy;
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 600 * 600)
				{

					f->target.push_back(*i);
					if (!GetEnemy)cc = *i;
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime >= 500 && GetEnemy)
		{
			_player->_attackTime = GetCurrentTime();
			_player->stopAllActions();
			if (_player->getEndTime() < GetCurrentTime() + 250)
				_player->setEndTime(GetCurrentTime() + 250);
			Vec2 v1 = _player->getPosition();
			Vec2 v2 = cc->getPosition();
			Vec2 v = v2 - v1;
			float an = v.getAngle();
			std::string str;
			if (an >= -3.14 / 4 && an <= 3.14 / 4)
			{
				str = "Right";
			}
			else if (an >= 3.14 / 4 && an <= 3 * 3.14 / 4)
			{
				str = "Up";
			}
			else if ((an >= 3 * 3.14 / 4 && an <= 3.14) || (an >= -3.14 && an <= -3 * 3.14 / 4))
			{
				str = "Left";
			}
			else if (an >= -3 * 3.14 / 4 && an <= -3.14 / 4)
			{
				str = "Down";
			}
			_player->initWithFile(StringUtils::format("HouYi/HouYi/Walk/%s/0000.PNG", str.c_str()));
			_player->Now_Direction = str;
			f->initWithFile(cocos2d::StringUtils::format("HouYi/HouYi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			f->setInjure(_player->getPhysicsAttack());
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 10);
		}
	}
}
void GameScene2::playerAttack_1()
{
	//冷却时间   8 seconds
	if (_player->getName() == "DaJi")
	{
		ImpactWave*f = ImpactWave::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/ImpactWave/%s/0000.PNG", _player->Now_Direction.c_str()));
		long long now_time = GetCurrentTime();
		if (now_time - _player->_attackTime1 >= 8000)
		{
			_player->_attackTime1 = now_time;
			f->setFlag(_player->getFlag());
			f->setEndtime(now_time + 1500);
			f->setDirection(_player->Now_Direction);
			cocos2d::Vec2 ballposition = _player->getPosition();
			float x = 5.0f;
			if (f->_direction == "Left")
			{
				ballposition.x -= x;
			}
			else if (f->_direction == "Right")
			{
				ballposition.x += x;
			}
			else if (f->_direction == "Up")
			{
				ballposition.y += x;
			}
			else if (f->_direction == "Down")
			{
				ballposition.y -= x;
			}
			else if (f->_direction == "Left-Up")
			{
				ballposition.x -= x;
				ballposition.y += x;
			}
			else if (f->_direction == "Left-Down")
			{
				ballposition.x -= x;
				ballposition.y -= x;
			}
			else if (f->_direction == "Right-Up")
			{
				ballposition.x += x;
				ballposition.y += x;
			}
			else if (f->_direction == "Right-Down")
			{
				ballposition.x += x;
				ballposition.y -= x;
			}
			if (!_enemy->isDie())
			{
				f->target.push_back(_enemy);
				if (f->_direction == "Up" || f->_direction == "Down")
				{
					f->target_length.push_back(999999);
				}
				else
				{
					f->target_length.push_back(999999);

				}
			}
			if (!enemy_flag.empty())
			{
				for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				{
					f->target.push_back(*i);
					if (f->_direction == "Up" || f->_direction == "Down")
					{
						f->target_length.push_back(999999);
					}
					else
					{
						f->target_length.push_back(999999);

					}
				}
			}
			f->setPosition(ballposition);
			f->setVisible(true);
			f->setInjure(_player->getPhysicsAttack()*1.5);
			_tileMap->addChild(f, 10);
			_ImpactWave.push_back(f);
		}
	}
	else if (_player->getName() == "YaSe")
	{
		long long now_time = GetCurrentTime();
		if (now_time - _player->_attackTime1 >= 8000)
		{
			_player->setPhysicsAttack(_player->getPhysicsAttack() + 5);
			_player->_attackTime1 = now_time;
		}
	}
	else if (_player->getName() == "HouYi")
	{
		long long now_time = GetCurrentTime();
		if (now_time - _player->_attackTime1 > 8000)
		{
			_player->_attackTime1 = now_time;
		}
		else return;
		auto dir = _player->Now_Direction;
		Vec2 v = _player->getPosition();
		if (dir == "Left")
		{
			v.x -= 100;
		}
		else if (dir == "Right")
		{
			v.x += 100;
		}
		else if (dir == "Up")
		{
			v.y += 100;
		}
		else if (dir == "Down")
		{
			v.y -= 100;
		}
		else if (dir == "Left-Up")
		{
			v.x -= 100 / 1.414;
			v.y += 100 / 1.414;
		}
		else if (dir == "Left-Down")
		{
			v.x -= 100 / 1.414;
			v.y -= 100 / 1.414;
		}
		else if (dir == "Right-Up")
		{
			v.x += 100 / 1.414;
			v.y += 100 / 1.414;
		}
		else if (dir == "Right-Down")
		{
			v.x += 100 / 1.414;
			v.y -= 100 / 1.414;
		}
		_player->setPosition(v);
	}
}
void GameScene2::playerAttack_2()
{
	//冷却时间 12 seconds
	if (_player->getName() == "DaJi")
	{
		bool isDo = false;
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName("DaJi/DaJi/Skill2/0001.PNG");
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			f->target.push_back(_enemy);
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 500 * 500)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime2 >= 12000 && GetEnemy)
		{
			isDo = true;
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			f->setInjure(_player->getPhysicsAttack() * 2);
			_tileMap->addChild(f, 10);
		}
		if (isDo)
		{
			_player->_attackTime2 = GetCurrentTime();
		}
	}
	else if (_player->getName() == "YaSe")
	{
		if (GetCurrentTime() - _player->_attackTime2 >= 12000)
		{
			Shield* f1 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai.PNG");
			_player->_attackTime2 = GetCurrentTime();
			f1->setNowtime(GetCurrentTime() + 34);
			f1->setEndtime(GetCurrentTime() + 3034);
			f1->setOwner(_player);
			f1->setDirection("Up");
			f1->setVisible(false);
			_Shield.push_back(f1);
			_tileMap->addChild(f1, 10);
			if (!_enemy->isDie())
				f1->target.push_back(_enemy);
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				f1->target.push_back(*i);
			Shield* f2 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai2.PNG");
			f2->setNowtime(GetCurrentTime() + 34);
			f2->setEndtime(GetCurrentTime() + 3034);
			f2->setOwner(_player);
			f2->setDirection("Down");
			f2->setVisible(false);
			_Shield.push_back(f2);
			_tileMap->addChild(f2, 10);
			if (!_enemy->isDie())
				f2->target.push_back(_enemy);
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				f2->target.push_back(*i);
			Shield* f3 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai3.PNG");
			f3->setNowtime(GetCurrentTime() + 34);
			f3->setEndtime(GetCurrentTime() + 3034);
			f3->setOwner(_player);
			f3->setDirection("Left");
			f3->setVisible(false);
			_Shield.push_back(f3);
			_tileMap->addChild(f3, 10);
			if (!_enemy->isDie())
				f3->target.push_back(_enemy);
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				f3->target.push_back(*i);
			Shield* f4 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai6.PNG");
			f4->setNowtime(GetCurrentTime() + 34);
			f4->setEndtime(GetCurrentTime() + 3034);
			f4->setOwner(_player);
			f4->setDirection("Right");
			f4->setVisible(false);
			_Shield.push_back(f4);
			_tileMap->addChild(f4, 10);
			if (!_enemy->isDie())
				f4->target.push_back(_enemy);
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				f4->target.push_back(*i);
			f4->setInjure(0.8*_player->getPhysicsAttack());
			f4->setInjure(0.8*_player->getPhysicsAttack());
			f4->setInjure(0.8*_player->getPhysicsAttack());
			f4->setInjure(0.8*_player->getPhysicsAttack());
		}
	}
	else if (_player->getName() == "HouYi")
	{
		bool GetEnemy = false;
		Model* cc;
		RangeSkill* f = RangeSkill::createWithName("HouYi/HouYi/Attack3/0000.png");
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			GetEnemy = true;
			cc = _enemy;
		}
		if (!enemy_flag.empty() && !GetEnemy)
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 300 * 300)
				{
					cc = (*i);
					GetEnemy = true;
					break;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime2 >= 12000 && GetEnemy)
		{
			f->setEndtime(GetCurrentTime() + 300);
			f->setOpacity(120);
			f->setVisible(true);
			f->setScale(0.5f);
			f->setPosition(cc->getPosition());
			if ((!_enemy->isDie()) && (_enemy->getPosition().x - f->getPosition().x)*(_enemy->getPosition().x - f->getPosition().x) + (_enemy->getPosition().y - f->getPosition().y)*(_enemy->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width / 4)
			{
				_enemy->setCurrentHp(_enemy->getCurrentHp() - 1.1*_player->getPhysicsAttack());
			}
			if (!enemy_flag.empty())
			{
				for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				{
					if (((*i)->getPosition().x - f->getPosition().x)*((*i)->getPosition().x - f->getPosition().x) + ((*i)->getPosition().y - f->getPosition().y)*((*i)->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width / 4)
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 1.1*_player->getPhysicsAttack());

					}
				}
			}
			_RangeSkill.push_back(f);
			_player->_attackTime2 = GetCurrentTime();
			_tileMap->addChild(f, 10);
		}
	}
}
void GameScene2::playerAttack_3()
{
	//冷却时间  18 seconds
	if (_player->getName() == "DaJi")
	{
		bool isDo = false;
		for (int a = 1; a <= 5; a++) {
			bool GetEnemy = false;
			FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
			if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 600 * 600)
			{
				f->target.push_back(_enemy);
				GetEnemy = true;

			}
			if (!enemy_flag.empty())
			{
				for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				{
					if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 600 * 600)
					{
						f->target.push_back(*i);
						GetEnemy = true;
					}
				}
			}
			if (GetCurrentTime() - _player->_attackTime3 >= 18000 && GetEnemy) {
				isDo = true;
				f->setNowtime(GetCurrentTime() + 34 + (a - 1) * 200);
				f->setOwner(_player);
				_Scheduleflying.push_back(f);
				f->setVisible(false);
				f->setInjure(0.6*_player->getPhysicsAttack());
				_tileMap->addChild(f, 10);
			}
		}
		if (isDo)
			_player->_attackTime3 = GetCurrentTime();
	}
	else if (_player->getName() == "YaSe")
	{
		if (GetCurrentTime() - _player->_attackTime3 >= 18000)
		{

			Vec2 v1 = _player->getPosition();
			Vec2 v2 = _enemy->getPosition();
			if (v1.getDistance(v2) < 500 && !_enemy->isDie())
			{
				_player->_attackTime3 = GetCurrentTime();
				_player->setPosition(v2);
				_enemy->setCurrentHp(_enemy->getCurrentHp() - 300);
			}
		}
	}
	else if (_player->getName() == "HouYi")
	{
		Butterfly* f = Butterfly::createWithName(cocos2d::StringUtils::format("HouYi/HouYi/Attack2/%s/0000.PNG", _player->Now_Direction.c_str()));
		if (GetCurrentTime() - _player->_attackTime3 >= 18000) {
			_player->_attackTime3 = GetCurrentTime();
			f->setNowtime(GetCurrentTime() + 34);
			f->setDirection(_player->Now_Direction);
			_ScheduleButterfly.push_back(f);
			f->setVisible(false);
			f->setOwner(_player);
			f->setInjure(500);
			_tileMap->addChild(f, 10);
		}
	}
}

//
void GameScene2::enemyAttack()
{
	if (_enemy->getName() == "DaJi")
	{
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _enemy->Now_Direction.c_str()));
		if ((!_player->isDie()) && (_player->getPosition().x - _enemy->getPosition().x)*(_player->getPosition().x - _enemy->getPosition().x) + (_player->getPosition().y - _enemy->getPosition().y)*(_player->getPosition().y - _enemy->getPosition().y) <= 500 * 500)
		{
			f->target.push_back(_player);
			GetEnemy = true;

		}
		if (!player_flag.empty())
		{
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _enemy->getPosition().x)*((*i)->getPosition().x - _enemy->getPosition().x) + ((*i)->getPosition().y - _enemy->getPosition().y)*((*i)->getPosition().y - _enemy->getPosition().y) <= 500 * 500)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _enemy->_attackTime >= 500 && GetEnemy) {
			_enemy->_attackTime = GetCurrentTime();
			if (_enemy->getEndTime() < GetCurrentTime() + 250)
				_enemy->setEndTime(GetCurrentTime() + 250);
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_enemy);
			f->setInjure(_enemy->getPhysicsAttack());
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 1);
		}
	}
	else if (_enemy->getName() == "YaSe")
	{
		auto dir = _enemy->Now_Direction;
		_enemy->stopAllActions();
		Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack_%s", _enemy->getName().c_str(), dir.c_str()));
		Animate *action = Animate::create(animation);
		_enemy->runAction(action);
		if (_enemy->getEndTime() < GetCurrentTime() + 1000)
			_enemy->setEndTime(GetCurrentTime() + 1000);
		if (!_player->isDie())
		{
			Vec2 v1 = _enemy->getPosition();
			Vec2 v2 = _player->getPosition();
			Vec2 v = v2 - v1;
			auto dir = _enemy->Now_Direction;
			if (v1.getDistance(v2) < 200)
			{
				if (dir == "Left")
				{
					if ((v.getAngle() >= 3.14 / 2 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 2))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());

					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());

					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());

					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());

					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());

					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - _enemy->getPhysicsAttack() + _player->getPhysicsDefence());

					}
				}
			}
		}
		for (auto i = player_flag.begin(); i != player_flag.end(); i++)
		{
			Vec2 v1 = _enemy->getPosition();
			Vec2 v2 = (*i)->getPosition();
			Vec2 v = v2 - v1;
			auto dir = _enemy->Now_Direction;
			if (v1.getDistance(v2) < 200)
			{
				if (dir == "Left")
				{
					if ((v.getAngle() >= 3.14 / 2 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 2))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());

					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - _enemy->getPhysicsAttack() + (*i)->getPhysicsDefence());
					}
				}
			}
		}
	}
	else if (_enemy->getName() == "HouYi")
	{
		bool GetEnemy = false;
		Model* cc;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("HouYi/HouYi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
		if ((!_player->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 600 * 600)
		{
			f->target.push_back(_player);
			if (!GetEnemy)cc = _player;
			GetEnemy = true;

		}
		if (!player_flag.empty())
		{
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _enemy->getPosition().x)*((*i)->getPosition().x - _enemy->getPosition().x) + ((*i)->getPosition().y - _enemy->getPosition().y)*((*i)->getPosition().y - _enemy->getPosition().y) <= 600 * 600)
				{
					f->target.push_back(*i);
					if (!GetEnemy)cc = *i;
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _enemy->_attackTime >= 500 && GetEnemy)
		{
			_enemy->_attackTime = GetCurrentTime();
			_enemy->stopAllActions();
			if (_enemy->getEndTime() < GetCurrentTime() + 250)
				_enemy->setEndTime(GetCurrentTime() + 250);
			Vec2 v1 = _enemy->getPosition();
			Vec2 v2 = cc->getPosition();
			Vec2 v = v2 - v1;
			float an = v.getAngle();
			std::string str;
			if (an >= -3.14 / 4 && an <= 3.14 / 4)
			{
				str = "Right";
			}
			else if (an >= 3.14 / 4 && an <= 3 * 3.14 / 4)
			{
				str = "Up";
			}
			else if ((an >= 3 * 3.14 / 4 && an <= 3.14) || (an >= -3.14 && an <= -3 * 3.14 / 4))
			{
				str = "Left";
			}
			else if (an >= -3 * 3.14 / 4 && an <= -3.14 / 4)
			{
				str = "Down";
			}
			_enemy->initWithFile(StringUtils::format("HouYi/HouYi/Walk/%s/0000.PNG", str.c_str()));
			_enemy->Now_Direction = str;
			f->initWithFile(cocos2d::StringUtils::format("HouYi/HouYi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_enemy);
			f->setInjure(_enemy->getPhysicsAttack());
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 1);
		}
	}
}
void GameScene2::enemyAttack_1()
{
	//冷却时间   8 seconds
	if (_enemy->getName() == "DaJi")
	{
		ImpactWave*f = ImpactWave::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/ImpactWave/%s/0000.PNG", _enemy->Now_Direction.c_str()));
		long long now_time = GetCurrentTime();
		if (now_time - _enemy->_attackTime1 >= 8000)
		{
			_enemy->_attackTime1 = now_time;
			f->setFlag(_enemy->getFlag());
			f->setEndtime(now_time + 1500);
			f->setDirection(_enemy->Now_Direction);
			cocos2d::Vec2 ballposition = _enemy->getPosition();
			float x = 5.0f;
			if (f->_direction == "Left")
			{
				ballposition.x -= x;
			}
			else if (f->_direction == "Right")
			{
				ballposition.x += x;
			}
			else if (f->_direction == "Up")
			{
				ballposition.y += x;
			}
			else if (f->_direction == "Down")
			{
				ballposition.y -= x;
			}
			else if (f->_direction == "Left-Up")
			{
				ballposition.x -= x;
				ballposition.y += x;
			}
			else if (f->_direction == "Left-Down")
			{
				ballposition.x -= x;
				ballposition.y -= x;
			}
			else if (f->_direction == "Right-Up")
			{
				ballposition.x += x;
				ballposition.y += x;
			}
			else if (f->_direction == "Right-Down")
			{
				ballposition.x += x;
				ballposition.y -= x;
			}
			if (!_player->isDie())
			{
				f->target.push_back(_player);
				if (f->_direction == "Up" || f->_direction == "Down")
				{
					f->target_length.push_back(999999);
				}
				else
				{
					f->target_length.push_back(999999);

				}
			}
			if (!player_flag.empty())
			{
				for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				{
					f->target.push_back(*i);
					if (f->_direction == "Up" || f->_direction == "Down")
					{
						f->target_length.push_back(999999);
					}
					else
					{
						f->target_length.push_back(999999);

					}
				}
			}
			f->setPosition(ballposition);
			f->setVisible(true);
			f->setInjure(_enemy->getPhysicsAttack()*1.5);
			_tileMap->addChild(f, 10);
			_ImpactWave.push_back(f);
		}
	}
	else if (_enemy->getName() == "YaSe")
	{
		long long now_time = GetCurrentTime();
		_player->_attackTime1 = now_time;
		if (now_time - _enemy->_attackTime1 >= 8000)
		{
			_enemy->setPhysicsAttack(_enemy->getPhysicsAttack() + 5);
		}
	}
	else if (_enemy->getName() == "HouYi")
	{
		long long now_time = GetCurrentTime();
		if (now_time - _enemy->_attackTime1 > 8000)
		{
			_enemy->_attackTime1 = now_time;
		}
		else return;
		auto dir = _enemy->Now_Direction;
		Vec2 v = _enemy->getPosition();
		if (dir == "Left")
		{
			v.x -= 100;
		}
		else if (dir == "Right")
		{
			v.x += 100;
		}
		else if (dir == "Up")
		{
			v.y += 100;
		}
		else if (dir == "Down")
		{
			v.y -= 100;
		}
		else if (dir == "Left-Up")
		{
			v.x -= 100 / 1.414;
			v.y += 100 / 1.414;
		}
		else if (dir == "Left-Down")
		{
			v.x -= 100 / 1.414;
			v.y -= 100 / 1.414;
		}
		else if (dir == "Right-Up")
		{
			v.x += 100 / 1.414;
			v.y += 100 / 1.414;
		}
		else if (dir == "Right-Down")
		{
			v.x += 100 / 1.414;
			v.y -= 100 / 1.414;
		}
		_enemy->setPosition(v);
	}
}
void GameScene2::enemyAttack_2()
{
	//冷却时间 12 seconds
	if (_enemy->getName() == "DaJi")
	{
		bool isDo = false;
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName("DaJi/DaJi/Skill2/0001.PNG");
		if ((!_player->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 300 * 300)
		{
			f->target.push_back(_player);
			GetEnemy = true;

		}
		if (!player_flag.empty())
		{
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _enemy->getPosition().x)*((*i)->getPosition().x - _enemy->getPosition().x) + ((*i)->getPosition().y - _enemy->getPosition().y)*((*i)->getPosition().y - _enemy->getPosition().y) <= 300 * 300)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime2 >= 12000 && GetEnemy)
		{
			isDo = true;
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_enemy);
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			f->setInjure(2 * _enemy->getPhysicsAttack());
			_tileMap->addChild(f, 10);
		}
		if (isDo)
		{
			_enemy->_attackTime2 = GetCurrentTime();
		}
	}
	else if (_enemy->getName() == "YaSe")
	{
		if (GetCurrentTime() - _enemy->_attackTime2 >= 12000)
		{
			Shield* f1 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai.PNG");
			_enemy->_attackTime2 = GetCurrentTime();
			f1->setNowtime(GetCurrentTime() + 34);
			f1->setEndtime(GetCurrentTime() + 3034);
			f1->setOwner(_enemy);
			f1->setDirection("Up");
			f1->setVisible(false);
			_Shield.push_back(f1);
			_tileMap->addChild(f1, 10);
			if (!_player->isDie())
				f1->target.push_back(_player);
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				f1->target.push_back(*i);
			Shield* f2 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai2.PNG");
			f2->setNowtime(GetCurrentTime() + 34);
			f2->setEndtime(GetCurrentTime() + 3034);
			f2->setOwner(_enemy);
			f2->setDirection("Down");
			f2->setVisible(false);
			_Shield.push_back(f2);
			_tileMap->addChild(f2, 10);
			if (!_player->isDie())
				f2->target.push_back(_player);
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				f2->target.push_back(*i);
			Shield* f3 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai3.PNG");
			f3->setNowtime(GetCurrentTime() + 34);
			f3->setEndtime(GetCurrentTime() + 3034);
			f3->setOwner(_enemy);
			f3->setDirection("Left");
			f3->setVisible(false);
			_Shield.push_back(f3);
			_tileMap->addChild(f3, 10);
			if (!_player->isDie())
				f3->target.push_back(_player);
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				f3->target.push_back(*i);
			Shield* f4 = Shield::createWithName("YaSe/YaSe/dunpai/dunpai6.PNG");
			f4->setNowtime(GetCurrentTime() + 34);
			f4->setEndtime(GetCurrentTime() + 3034);
			f4->setOwner(_enemy);
			f4->setDirection("Right");
			f4->setVisible(false);
			_Shield.push_back(f4);
			_tileMap->addChild(f4, 10);
			if (!_player->isDie())
				f4->target.push_back(_player);
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				f4->target.push_back(*i);
			f1->setInjure(0.8*_enemy->getPhysicsAttack());
		}
	}
	else if (_enemy->getName() == "HouYi")
	{
		bool GetEnemy = false;
		Model* cc;
		RangeSkill* f = RangeSkill::createWithName("HouYi/HouYi/Attack3/0000.png");
		if ((!_player->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			GetEnemy = true;
			cc = _player;
		}
		if (!player_flag.empty() && !GetEnemy)
		{
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _enemy->getPosition().x)*((*i)->getPosition().x - _enemy->getPosition().x) + ((*i)->getPosition().y - _enemy->getPosition().y)*((*i)->getPosition().y - _enemy->getPosition().y) <= 300 * 300)
				{
					cc = (*i);
					GetEnemy = true;
					break;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime2 >= 12000 && GetEnemy)
		{
			f->setEndtime(GetCurrentTime() + 300);
			f->setOpacity(120);
			f->setVisible(true);
			f->setScale(0.5f);
			f->setPosition(cc->getPosition());
			if ((!_player->isDie()) && (_player->getPosition().x - f->getPosition().x)*(_player->getPosition().x - f->getPosition().x) + (_player->getPosition().y - f->getPosition().y)*(_player->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width / 4)
			{
				_player->setCurrentHp(_player->getCurrentHp() - 1.1*_enemy->getPhysicsAttack());
			}
			if (!player_flag.empty())
			{
				for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				{
					if (((*i)->getPosition().x - f->getPosition().x)*((*i)->getPosition().x - f->getPosition().x) + ((*i)->getPosition().y - f->getPosition().y)*((*i)->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width / 4)
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 1.1*_enemy->getPhysicsAttack());

					}
				}
			}
			_RangeSkill.push_back(f);
			_enemy->_attackTime2 = GetCurrentTime();
			_tileMap->addChild(f, 10);
		}
	}
}
void GameScene2::enemyAttack_3()
{
	//冷却时间  18 seconds
	if (_enemy->getName() == "DaJi")
	{
		bool isDo = false;
		for (int a = 1; a <= 5; a++) {
			bool GetEnemy = false;
			FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _enemy->Now_Direction.c_str()));
			if ((!_player->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 300 * 300)
			{
				f->target.push_back(_player);
				GetEnemy = true;

			}
			if (!player_flag.empty())
			{
				for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				{
					if (((*i)->getPosition().x - _enemy->getPosition().x)*((*i)->getPosition().x - _enemy->getPosition().x) + ((*i)->getPosition().y - _enemy->getPosition().y)*((*i)->getPosition().y - _enemy->getPosition().y) <= 300 * 300)
					{
						f->target.push_back(*i);
						GetEnemy = true;
					}
				}
			}
			if (GetCurrentTime() - _enemy->_attackTime3 >= 18000 && GetEnemy) {
				isDo = true;
				f->setNowtime(GetCurrentTime() + 34 + (a - 1) * 200);
				f->setOwner(_enemy);
				_Scheduleflying.push_back(f);
				f->setVisible(false);
				f->setInjure(0.6*_enemy->getPhysicsAttack());
				_tileMap->addChild(f, 10);
			}
		}
		if (isDo)
			_enemy->_attackTime3 = GetCurrentTime();
	}
	else if (_enemy->getName() == "YaSe")
	{
		if (GetCurrentTime() - _player->_attackTime3 >= 18000)
		{

			Vec2 v1 = _enemy->getPosition();
			Vec2 v2 = _player->getPosition();
			if (v1.getDistance(v2) < 500 && !_player->isDie())
			{
				_enemy->_attackTime3 = GetCurrentTime();
				_enemy->setPosition(v2);
				_player->setCurrentHp(_player->getCurrentHp() - 300);
			}
		}
	}
	else if (_enemy->getName() == "HouYi")
	{
		Butterfly* f = Butterfly::createWithName(cocos2d::StringUtils::format("HouYi/HouYi/Attack2/%s/0000.PNG", _enemy->Now_Direction.c_str()));
		if (GetCurrentTime() - _enemy->_attackTime3 >= 18000) {
			_enemy->_attackTime3 = GetCurrentTime();
			f->setNowtime(GetCurrentTime() + 34);
			f->setDirection(_enemy->Now_Direction);
			_ScheduleButterfly.push_back(f);
			f->setVisible(false);
			f->setOwner(_enemy);
			_player->setCurrentHp(_player->getCurrentHp() - 500);
			_tileMap->addChild(f, 10);
		}
	}
}

void GameScene2::towerAttack()
{
	long long now_time = GetCurrentTime();
	if (!_tower.empty())
	{
		for (auto i = _tower.begin(); i != _tower.end(); i++)
		{
			(*i)->doHP();
			bool GetEnemy = false;
			float xx = _tileMap->getContentSize().height / 2;
			Model *target;
			Vec2 v1 = (*i)->getPosition();
			for (auto j = enemy_flag.begin(); j != enemy_flag.end(); j++)
			{
				if ((*j)->getFlag() == (*i)->getFlag())
					break;
				Vec2 v2 = (*j)->getPosition();
				Vec2 v3 = v1 - v2;
				float yy = v3.getLength();
				if (yy < xx)
				{
					GetEnemy = true;
					target = (*j);
					break;
				}

			}
			if (!GetEnemy) {
				for (auto j = player_flag.begin(); j != player_flag.end(); j++)
				{
					if ((*j)->getFlag() == (*i)->getFlag())
						break;
					Vec2 v2 = (*j)->getPosition();
					Vec2 v3 = v1 - v2;
					float yy = v3.getLength();
					if (yy < xx)
					{
						GetEnemy = true;
						target = (*j);
						break;
					}

				}
			}
			if (!GetEnemy && !_player->isDie())
			{
				if (_player->getFlag() != (*i)->getFlag())
				{
					Vec2 v2 = _player->getPosition();
					Vec2 v3 = v1 - v2;
					float yy = v3.getLength();
					if (yy < xx)
					{
						GetEnemy = true;
						target = _player;
					}
				}
			}
			if (!GetEnemy && !_enemy->isDie())
			{
				if (_enemy->getFlag() != (*i)->getFlag())
				{
					Vec2 v2 = _enemy->getPosition();
					Vec2 v3 = v1 - v2;
					float yy = v3.getLength();
					if (yy < xx)
					{
						GetEnemy = true;
						target = _enemy;
					}
				}
			}
			if (now_time > (*i)->_attackTime&&GetEnemy)
			{
				(*i)->_attackTime = now_time + 2000;
				FlyingBox* f = FlyingBox::createWithName("TileMap/pao.png");
				f->setNowtime(GetCurrentTime() + 34);
				f->setOwner(*i);
				_Scheduleflying.push_back(f);
				f->setVisible(false);
				f->target.push_back(target);
				f->setInjure((*i)->getPhysicsAttack());
				_tileMap->addChild(f, 10);
			}
		}
	}
	if (!_tower.empty())
	{
		for (auto i = _tower.begin(); i != _tower.end();)
		{
			if ((*i)->isDie())
			{
				(*i)->setVisible(false);
				(*i)->_HPbox->setVisible(false);
				(*i)->_HPrectangle->setVisible(false);
				if (std::find(enemy_flag.begin(), enemy_flag.end(), *i) != enemy_flag.end())
					enemy_flag.erase(std::find(enemy_flag.begin(), enemy_flag.end(), *i));
				if (std::find(player_flag.begin(), player_flag.end(), *i) != player_flag.end())
					player_flag.erase(std::find(player_flag.begin(), player_flag.end(), *i));
				i = _tower.erase(i);
			}
			else i++;
		}
	}
}

void GameScene2::soldierAttack(Soldier * soldier)
{
	long long now_time = GetCurrentTime();
	bool GetEnemy = false;
	Model *target;
	Vec2 v1 = soldier->getPosition();
	for (auto j = enemy_flag.begin(); j != enemy_flag.end(); j++)
	{
		if ((*j)->getFlag() == soldier->getFlag())
			break;
		Vec2 v2 = (*j)->getPosition();
		Vec2 v3 = v1 - v2;
		float yy = v3.getLength();
		if (yy < 600)
		{
			GetEnemy = true;
			target = (*j);
			break;
		}

	}
	if (!GetEnemy) {
		for (auto j = player_flag.begin(); j != player_flag.end(); j++)
		{
			if ((*j)->getFlag() == soldier->getFlag())
				break;
			Vec2 v2 = (*j)->getPosition();
			Vec2 v3 = v1 - v2;
			float yy = v3.getLength();
			if (yy < 600)
			{
				GetEnemy = true;
				target = (*j);
				break;
			}

		}
	}
	if (!GetEnemy && !_player->isDie())
	{
		if (_player->getFlag() != soldier->getFlag())
		{
			Vec2 v2 = _player->getPosition();
			Vec2 v3 = v1 - v2;
			float yy = v3.getLength();
			if (yy < 600)
			{
				GetEnemy = true;
				target = _player;
			}
		}
	}
	if (!GetEnemy && !_enemy->isDie())
	{
		if (_enemy->getFlag() != soldier->getFlag())
		{
			Vec2 v2 = _enemy->getPosition();
			Vec2 v3 = v1 - v2;
			float yy = v3.getLength();
			if (yy < 600)
			{
				GetEnemy = true;
				target = _enemy;
			}
		}
	}
	if (now_time > soldier->_attackTime&&GetEnemy)
	{
		soldier->_attackTime = now_time + 1000;
		FlyingBox* f;
		if (soldier->_name == 1)
			f = FlyingBox::createWithName("XiaoBin/blue/xiaobingqiu.png");
		else
		{
			if (soldier->getFlag() == Flag::BLUE)
			{
				f = FlyingBox::createWithName("XiaoBin/blue/bulletleft.PNG");
			}
			else
			{
				f = FlyingBox::createWithName("XiaoBin/blue/bulletright.PNG");
			}
		}
		f->setNowtime(GetCurrentTime() + 34);
		f->setOwner(soldier);
		_Scheduleflying.push_back(f);
		f->setVisible(false);
		f->target.push_back(target);
		f->setInjure(soldier->getPhysicsAttack());
		_tileMap->addChild(f, 10);
	}
}

bool GameScene2::out_of_windows(cocos2d::Vec2 v)
{
	Vec2 w = this->_tileMap->getContentSize();
	if (v.x < 0)
	{
		return true;
	}
	if (v.y < 0)
	{
		return true;
	}
	if (v.x > w.x)
	{
		return true;
	}
	if (v.y > w.y)
	{
		return true;
	}
	return false;
}

void GameScene2::MoveMap(float delta)
{
	Vec2 v = Director::getInstance()->getWinSize();
	Vec2 p1 = _player->getPosition();
	Vec2 p = Vec2(p1.x*v.y / _tileMap->getContentSize().height, p1.y*v.y / _tileMap->getContentSize().height);
	int x = MAX(p.x, v.x / 2);
	x = MIN(x, _tileMap->getContentSize().width*v.y / _tileMap->getContentSize().height - v.x / 2);
	if (now_x == 0 || v.x / 2 - x - now_x > 0.01 || now_x + x - v.x / 2 > 0.01)
	{
		_tileMap->setPosition(v.x / 2 - x, 0);
		now_x = v.x / 2 - x;
	}
}

void GameScene2::doRangeSkill()
{
	long long now_t = GetCurrentTime();
	if (!_RangeSkill.empty())
	{
		for (auto i = _RangeSkill.begin(); i != _RangeSkill.end();)
		{
			if (now_t > (*i)->getEndtime())
			{
				(*i)->setVisible(false);
				(*i)->removeFromParent();
				i = _RangeSkill.erase(i);
			}
			else
				i++;
		}
	}
}

void GameScene2::doFlying()
{
	long long now_time = GetCurrentTime();
	if (!_Scheduleflying.empty())
	{
		for (auto i = _Scheduleflying.begin(); i != _Scheduleflying.end();)
		{

			if (now_time > (*i)->getNowtime())
			{
				(*i)->DoSomethingAwesome();
				_flying.push_back(*i);
				i = _Scheduleflying.erase(i);
			}
			else
				++i;
		}

	}
	if (!_flying.empty())
	{
		for (auto i = _flying.begin(); i != _flying.end();)
		{
			bool FindTarget = false;
			Model*Target;
			for (auto j = (*i)->target.begin(); j != (*i)->target.end(); j++)
			{
				if ((*j) != nullptr || !(*j)->isDie())
				{
					FindTarget = true;
					Target = *j;
					break;
				}
			}
			if (FindTarget)
			{
				Vec2 f1 = (*i)->getPosition();
				Vec2 f2 = Target->getPosition();
				Vec2 f3 = f2 - f1;
				f3.x /= sqrt(f3.x*f3.x + f3.y*f3.y) / 10;
				f3.y /= sqrt(f3.x*f3.x + f3.y*f3.y) / 10;
				(*i)->setPosition(f3 + f1);
				if (abs((*i)->getPosition().x - Target->getPosition().x) <= 20 && abs((*i)->getPosition().y - Target->getPosition().y) <= 20)
				{
					Target->setCurrentHp(Target->getCurrentHp() - (*i)->getInjure());
					(*i)->setVisible(false);
					(*i)->removeFromParent();
					i = _flying.erase(i);
				}
				else
					++i;
			}
			else
			{
				(*i)->setVisible(false);
				(*i)->removeFromParent();
				i = _flying.erase(i);
			}
		}

	}
}

void GameScene2::doButterfly()
{
	long long now_time = GetCurrentTime();
	if (!_ScheduleButterfly.empty())
	{
		for (auto i = _ScheduleButterfly.begin(); i != _ScheduleButterfly.end();)
		{

			if (now_time > (*i)->getNowtime())
			{
				(*i)->DoSomethingAwesome();
				_Butterfly.push_back(*i);
				i = _ScheduleButterfly.erase(i);
			}
			else
				++i;
		}

	}
	if (!_Butterfly.empty())
	{
		for (auto i = _Butterfly.begin(); i != _Butterfly.end();)
		{
			if ((*i)->getOwner() == _player)
			{
				if (abs((*i)->getPosition().x - _enemy->getPosition().x) <= 50 && abs((*i)->getPosition().y - _enemy->getPosition().y) <= 50)
				{

					_enemy->setCurrentHp(_enemy->getCurrentHp() - (*i)->getInjure());
					(*i)->setVisible(false);
					(*i)->removeFromParent();
					i = _Butterfly.erase(i);
				}
				else if (out_of_windows((*i)->getPosition()))
				{
					(*i)->setVisible(false);
					(*i)->removeFromParent();
					i = _Butterfly.erase(i);
				}
				else
				{
					std::string dir = (*i)->getDirection();
					Vec2 pos = (*i)->getPosition();
					if (dir == "Left")
					{
						pos.x -= 7;
					}
					else if (dir == "Right")
					{
						pos.x += 7;
					}
					else if (dir == "Up")
					{
						pos.y += 7;
					}
					else if (dir == "Down")
					{
						pos.y -= 7;
					}
					else if (dir == "Left-Up")
					{
						pos.y += 4.95;
						pos.x -= 4.95;
					}
					else if (dir == "Right-Up")
					{
						pos.y += 4.95;
						pos.x += 4.95;
					}
					else if (dir == "Left-Down")
					{
						pos.y -= 4.95;
						pos.x -= 4.95;
					}
					else if (dir == "Right-Down")
					{
						pos.y -= 4.95;
						pos.x += 4.95;
					}
					(*i)->setPosition(pos);
					i++;
				}
			}
			else if ((*i)->getOwner() == _enemy)
			{
				if (abs((*i)->getPosition().x - _player->getPosition().x) <= 50 && abs((*i)->getPosition().y - _player->getPosition().y) <= 50)
				{
					_player->setCurrentHp(_player->getCurrentHp() - (*i)->getInjure());
					(*i)->setVisible(false);
					(*i)->removeFromParent();
					i = _Butterfly.erase(i);
				}
				else if (out_of_windows((*i)->getPosition()))
				{
					(*i)->setVisible(false);
					(*i)->removeFromParent();
					i = _Butterfly.erase(i);
				}
				else
				{
					std::string dir = (*i)->getDirection();
					Vec2 pos = (*i)->getPosition();
					if (dir == "Left")
					{
						pos.x -= 7;
					}
					else if (dir == "Right")
					{
						pos.x += 7;
					}
					else if (dir == "Up")
					{
						pos.y += 7;
					}
					else if (dir == "Down")
					{
						pos.y -= 7;
					}
					else if (dir == "Left-Up")
					{
						pos.y += 4.95;
						pos.x -= 4.95;
					}
					else if (dir == "Right-Up")
					{
						pos.y += 4.95;
						pos.x += 4.95;
					}
					else if (dir == "Left-Down")
					{
						pos.y -= 4.95;
						pos.x -= 4.95;
					}
					else if (dir == "Right-Down")
					{
						pos.y -= 4.95;
						pos.x += 4.95;
					}
					(*i)->setPosition(pos);
					i++;
				}
			}
		}

	}
}

void GameScene2::doImpactWave()
{
	if (!_ImpactWave.empty()) {
		for (auto i = _ImpactWave.begin(); i != _ImpactWave.end();)
		{
			long long now_time = GetCurrentTime();
			auto k = (*i)->target_length.begin();
			auto j = (*i)->target.begin();
			if ((*i)->_direction == "Up" || (*i)->_direction == "Down")
			{
				if (!(*i)->target.empty())
				{
					for (; j != (*i)->target.end(); j++, k++)
					{
						int xx = *k;
						int yy = (*j)->getPosition().y - (*i)->getPosition().y;
						if (xx > 99998)xx = yy;
						if (xx*yy < 0 && (*j)->getPosition().x<(*i)->getPosition().x + (*i)->getContentSize().width && (*j)->getPosition().x >(*i)->getPosition().x - (*i)->getContentSize().width)
						{
							if (xx*yy == 0)
								(*j)->setCurrentHp((*j)->getCurrentHp() - (*i)->getInjure() / 2);
							else
								(*j)->setCurrentHp((*j)->getCurrentHp() - (*i)->getInjure());
						}
						*k = yy;
					}
				}
			}
			else
			{
				if (!(*i)->target.empty())
				{
					for (; j != (*i)->target.end(); j++, k++)
					{
						int xx = *k;
						int yy = (*j)->getPosition().x - (*i)->getPosition().x;
						if (xx > 99998)xx = yy;
						Vec2  v1 = (*j)->getPosition();
						Vec2  v2 = (*i)->getPosition();
						Size sz = (*i)->getContentSize();
						if (xx*yy <= 0 && (*j)->getPosition().y<(*i)->getPosition().y + (*i)->getContentSize().height && (*j)->getPosition().y >(*i)->getPosition().y - (*i)->getContentSize().height)
						{
							if (xx*yy == 0)
								(*j)->setCurrentHp((*j)->getCurrentHp() - (*i)->getInjure() / 2);
							else
								(*j)->setCurrentHp((*j)->getCurrentHp() - (*i)->getInjure());
						}
						*k = yy;
					}
				}
			}
			if (now_time > (*i)->getEndtime())
			{
				(*i)->setVisible(false);
				(*i)->removeFromParent();
				i = _ImpactWave.erase(i);
			}
			else
			{
				auto dir = (*i)->_direction;
				auto pos = (*i)->getPosition();
				if (dir == "Left")
				{
					pos.x -= 7;
				}
				else if (dir == "Right")
				{
					pos.x += 7;
				}
				else if (dir == "Up")
				{
					pos.y += 7;
				}
				else if (dir == "Down")
				{
					pos.y -= 7;
				}
				else if (dir == "Left-Up")
				{
					pos.y += 4.95;
					pos.x -= 4.95;
				}
				else if (dir == "Right-Up")
				{
					pos.y += 4.95;
					pos.x += 4.95;
				}
				else if (dir == "Left-Down")
				{
					pos.y -= 4.95;
					pos.x -= 4.95;
				}
				else if (dir == "Right-Down")
				{
					pos.y -= 4.95;
					pos.x += 4.95;
				}
				(*i)->setPosition(pos);
				i++;
			}
		}

	}
}

void GameScene2::doShield()
{
	long long now_time = GetCurrentTime();

	for (auto i = _Shield.begin(); i != _Shield.end();)
	{
		(*i)->setVisible(true);
		auto dir = (*i)->getDirection();
		Vec2 v = (*i)->getOwner()->getPosition();
		if (dir == "Left")
		{
			v.x -= 50;
		}
		else if (dir == "Right")
		{
			v.x += 50;
		}
		else if (dir == "Up")
		{
			v.y += 50;
		}
		else if (dir == "Down")
		{
			v.y -= 50;
		}
		(*i)->setPosition(v);
		if (now_time > (*i)->getNowtime())
		{
			(*i)->setNowtime((*i)->getNowtime() + 1000);
			for (auto j = (*i)->target.begin(); j != (*i)->target.end(); j++)
			{
				Vec2 v1 = (*j)->getPosition();
				float xx = v1.getDistance(v);
				Size sz = (*j)->getContentSize();
				float yy = MAX(sz.width / 2, sz.height / 2);
				if (xx < yy)
				{
					(*j)->setCurrentHp((*j)->getCurrentHp() - (*i)->getInjure());
				}
			}
		}
		if (now_time > (*i)->getEndtime())
		{
			(*i)->setVisible(false);
			(*i)->removeFromParent();
			i = _Shield.erase(i);
		}
		else i++;
	}

}


void GameScene2::initMap()
{
	Vec2 v1 = Director::getInstance()->getWinSize();
	_tileMap = TMXTiledMap::create("TileMap/TileMap.tmx");
	Vec2 v2 = _tileMap->getContentSize();
	_tileMap->setScale(v1.y / v2.y);
	_tileMap->setAnchorPoint(Vec2::ZERO);
	_tileMap->getMapSize();
	_tileMap->setPosition(Vec2(0, 0));
	_tileMap->getLayer("background")->setVisible(true);
	_tileMap->getLayer("red")->setVisible(true);
	_tileMap->getLayer("blue")->setVisible(true);
	_tileMap->getLayer("collidable")->setVisible(false);
	this->addChild(_tileMap, 0);
}

void GameScene2::initAnimation()
{
	//DaJi
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Up")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Down")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Left")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Right")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Left-Up")] = 2;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Left-Down")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Right-Up")] = 2;
	Dirction_Animation_Walk_Number[std::make_pair("DaJi", "Right-Down")] = 3;
	//YaSe
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Up")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Down")] = 4;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Left")] = 4;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Right")] = 4;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Left-Up")] = 4;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Left-Down")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Right-Up")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("YaSe", "Right-Down")] = 4;
	//
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Up")] = 5;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Down")] = 4;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Left")] = 4;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Right")] = 5;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Left-Up")] = 4;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Left-Down")] = 4;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Right-Up")] = 6;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Right-Down")] = 4;
	//
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Up")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Down")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Left")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Right")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Left-Up")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Left-Down")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Right-Up")] = 0;
	Dirction_Animation_Skill1_Number[std::make_pair("YaSe", "Right-Down")] = 0;
	//

	//HouYi
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Up")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Down")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Left")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Right")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Left-Up")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Left-Down")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Right-Up")] = 3;
	Dirction_Animation_Walk_Number[std::make_pair("HouYi", "Right-Down")] = 4;
	//
	LoadingAnimation("DaJi");
	LoadingAnimation("YaSe");
	LoadingAnimation("HouYi");
	LoadingYaSeAnimation();
	//

}

void GameScene2::initHero(char FLAG)
{
	if (FLAG == 'B') {
		Vec2 v1 = Director::getInstance()->getWinSize();
		auto player = Hero::CreateWithName(_PlayerName);
		auto enemy = Hero::CreateWithName(_EnemyName);
		_player = player;
		_enemy = enemy;
		_player->setPosition(200, _tileMap->getContentSize().height / 2);
		_enemy->setPosition(_tileMap->getContentSize().width - 200, _tileMap->getContentSize().height / 2);
		_player->born_position = Vec2(100, _tileMap->getContentSize().height / 2);
		_enemy->born_position = Vec2(_tileMap->getContentSize().width - 100, _tileMap->getContentSize().height / 2);
		_player->setFlag(Flag::BLUE);
		_enemy->setFlag(Flag::RED);
		_tileMap->addChild(player, 10);
		_tileMap->addChild(enemy, 10);
	}
	else if (FLAG == 'R')
	{
		Vec2 v1 = Director::getInstance()->getWinSize();
		auto player = Hero::CreateWithName(_PlayerName);
		auto enemy = Hero::CreateWithName(_EnemyName);
		_player = player;
		_enemy = enemy;
		_enemy->setPosition(200, _tileMap->getContentSize().height / 2);
		_player->setPosition(_tileMap->getContentSize().width - 200, _tileMap->getContentSize().height / 2);
		_enemy->born_position = Vec2(100, _tileMap->getContentSize().height / 2);
		_player->born_position = Vec2(_tileMap->getContentSize().width - 100, _tileMap->getContentSize().height / 2);
		_enemy->setFlag(Flag::BLUE);
		_player->setFlag(Flag::RED);
		_tileMap->addChild(player, 10);
		_tileMap->addChild(enemy, 10);
	}
	TT = cocos2d::Label::createWithTTF("1", "fonts/Marker Felt.ttf", 60);
	Vec2 v = Director::getInstance()->getWinSize();
	TT->setPosition(v.x / 2, v.y / 2);
	TT->setVisible(false);
	this->addChild(TT, 11);
	ZZ = cocos2d::Label::createWithTTF("0:0", "fonts/Marker Felt.ttf", 40);
	ZZ->setPosition(v.x / 2, v.y - 100);
	ZZ->setVisible(true);
	this->addChild(ZZ, 11);
	MM = cocos2d::Label::createWithTTF("money:0", "fonts/Marker Felt.ttf", 40);
	MM->setPosition(v.x / 2, 100);
	MM->setVisible(true);
	this->addChild(MM, 11);
}

void GameScene2::initSkill()
{
	auto skill1 = Sprite::create(cocos2d::StringUtils::format("%s/jineng1.png", _player->getName().c_str()));
	auto skill2 = Sprite::create(cocos2d::StringUtils::format("%s/jineng2.png", _player->getName().c_str()));
	auto skill3 = Sprite::create(cocos2d::StringUtils::format("%s/jineng3.png", _player->getName().c_str()));
	Vec2 w = Director::getInstance()->getWinSize();
	Vec2 v = skill1->getContentSize();
	Vec2 v1 = Vec2(w.x - 7 * v.x / 2, v.y / 2);
	Vec2 v2 = Vec2(w.x - 4 * v.x / 2, v.y / 2);
	Vec2 v3 = Vec2(w.x - v.x / 2, v.y / 2);
	skill1->setPosition(v1);
	skill2->setPosition(v2);
	skill3->setPosition(v3);
	this->addChild(skill1, 1);
	this->addChild(skill2, 1);
	this->addChild(skill3, 1);
	Label* skilltime1 = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 30);
	Label* skilltime2 = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 30);
	Label* skilltime3 = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 30);
	skilltime1->setColor(cocos2d::Color3B(0, 0, 0));
	skilltime2->setColor(cocos2d::Color3B(0, 0, 0));
	skilltime3->setColor(cocos2d::Color3B(0, 0, 0));
	skilltime1->setPosition(v1);
	skilltime2->setPosition(v2);
	skilltime3->setPosition(v3);
	skilltime1->setVisible(false);
	skilltime2->setVisible(false);
	skilltime3->setVisible(false);
	this->addChild(skilltime1, 2);
	this->addChild(skilltime2, 2);
	this->addChild(skilltime3, 2);
	_skilltime1 = skilltime1;
	_skilltime2 = skilltime2;
	_skilltime3 = skilltime3;
}

void GameScene2::initHP()
{
	cocos2d::Sprite*HPbox = cocos2d::Sprite::create("xuetiao/xuetiao2.png");
	cocos2d::Sprite*HPrectangle = cocos2d::Sprite::create("xuetiao/xuetiao1.png");

}

void GameScene2::initTower()
{
	//获得对象数组  
	TMXObjectGroup* objG = _tileMap->getObjectGroup("things");
	//获得对象数组中的一个对象  
	auto object = objG->getObject("bluecrystal");
	//获得对象的坐标  
	float x = object["x"].asFloat();
	float y = object["y"].asFloat();
	//在对象上创建一个蓝塔 
	Tower* sprite1 = Tower::CreateWithName("TileMap/0007.png");
	sprite1->setFlag(Flag::BLUE);
	_bluecrystal = sprite1;
	_tileMap->addChild(sprite1, 9);
	//设置位置  
	sprite1->setPosition(Vec2(x + sprite1->getContentSize().width / 2, y + sprite1->getContentSize().height / 2));
	//获得对象数组  
	TMXObjectGroup* objG2 = _tileMap->getObjectGroup("things");
	//获得对象数组中的一个对象  
	auto object2 = objG2->getObject("bluetower");
	//获得对象的坐标  
	float x2 = object2["x"].asFloat();
	float y2 = object2["y"].asFloat();
	//在对象上创建一个蓝塔 
	Tower* sprite2 = Tower::CreateWithName("TileMap/0005.png");
	sprite2->setFlag(Flag::BLUE);
	_bluetower = sprite2;
	_tileMap->addChild(sprite2, 9);
	//设置位置  
	sprite2->setPosition(Vec2(x2 + sprite2->getContentSize().width / 2, y2 + sprite2->getContentSize().height / 2));
	//
	//获得对象数组  
	TMXObjectGroup* objG3 = _tileMap->getObjectGroup("things");
	//获得对象数组中的一个对象  
	auto object3 = objG3->getObject("redcrystal");
	//获得对象的坐标  
	float x3 = object3["x"].asFloat();
	float y3 = object3["y"].asFloat();
	//在对象上创建一个蓝塔 
	Tower* sprite3 = Tower::CreateWithName("TileMap/0006.png");
	sprite3->setFlag(Flag::RED);
	_redcrystal = sprite3;
	_tileMap->addChild(sprite3, 9);
	//设置位置  
	sprite3->setPosition(Vec2(x3 + sprite3->getContentSize().width / 2, y3 + sprite3->getContentSize().height / 2));
	//获得对象数组  
	TMXObjectGroup* objG4 = _tileMap->getObjectGroup("things");
	//获得对象数组中的一个对象  
	auto object4 = objG4->getObject("redtower");
	//获得对象的坐标  
	float x4 = object4["x"].asFloat();
	float y4 = object4["y"].asFloat();
	//在对象上创建一个蓝塔 
	Tower* sprite4 = Tower::CreateWithName("TileMap/0004.png");
	sprite3->setFlag(Flag::RED);
	_redtower = sprite4;
	_tileMap->addChild(sprite4, 9);
	//设置位置  
	sprite4->setPosition(Vec2(x4 + sprite4->getContentSize().width / 2, y4 + sprite4->getContentSize().height / 2));
	_tower.push_back(sprite1);
	_tower.push_back(sprite2);
	_tower.push_back(sprite3);
	_tower.push_back(sprite4);
	if (sprite1->getFlag() == _player->getFlag())
	{
		player_flag.push_back(sprite1);

	}
	else if (sprite1->getFlag() == _enemy->getFlag())
	{
		enemy_flag.push_back(sprite1);
	}
	if (sprite2->getFlag() == _player->getFlag())
	{
		player_flag.push_back(sprite2);

	}
	else if (sprite2->getFlag() == _enemy->getFlag())
	{
		enemy_flag.push_back(sprite2);
	}
	if (sprite3->getFlag() == _player->getFlag())
	{
		player_flag.push_back(sprite3);

	}
	else if (sprite3->getFlag() == _enemy->getFlag())
	{
		enemy_flag.push_back(sprite3);
	}
	if (sprite4->getFlag() == _player->getFlag())
	{
		player_flag.push_back(sprite4);

	}
	else if (sprite4->getFlag() == _enemy->getFlag())
	{
		enemy_flag.push_back(sprite4);
	}
}

void GameScene2::initSoldier()
{
	long long now_time = GetCurrentTime();
	if (now_time > _soldiertime)
	{
		_soldiertime = now_time + 20000;
		if (true)
		{
			Vec2 v = _redcrystal->getPosition();
			Vec2 sz = _redcrystal->getContentSize();
			Vec2 v1 = v - Vec2(0, sz.y / 2 + 50);
			Vec2 v2 = v + Vec2(0, sz.y / 2 + 50);
			Vec2 v3 = v1 + Vec2(100, 0);
			Vec2 v4 = v2 + Vec2(100, 0);
			Soldier* soldier1 = Soldier::CreateWithName("XiaoBin/blue/red1.PNG");
			soldier1->setPosition(v1);
			soldier1->_name = 1;
			soldier1->setFlag(Flag::RED);
			_tileMap->addChild(soldier1, 9);
			if (soldier1->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier1);

			}
			else if (soldier1->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier1);
			}
			_soldier.push_back(soldier1);
			Soldier* soldier2 = Soldier::CreateWithName("XiaoBin/blue/red3.PNG");
			soldier2->setPosition(v3);
			this->_name = 2;
			soldier2->setFlag(Flag::RED);
			_tileMap->addChild(soldier2, 9);
			if (soldier2->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier2);

			}
			else if (soldier2->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier2);
			}
			_soldier.push_back(soldier2);
			Soldier* soldier3 = Soldier::CreateWithName("XiaoBin/blue/red1.PNG");
			soldier3->setPosition(v2);
			soldier3->_name = 1;
			soldier3->setFlag(Flag::RED);
			_tileMap->addChild(soldier3, 9);
			_soldier.push_back(soldier3);
			if (soldier3->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier3);

			}
			else if (soldier3->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier3);
			}
			Soldier* soldier4 = Soldier::CreateWithName("XiaoBin/blue/red3.PNG");
			soldier4->_name = 2;
			soldier4->setPosition(v4);
			soldier4->setFlag(Flag::RED);
			_tileMap->addChild(soldier4, 9);
			if (soldier4->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier4);

			}
			else if (soldier4->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier4);
			}
			_soldier.push_back(soldier4);
		}
		if (true)
		{
			Vec2 v = _bluecrystal->getPosition();
			Vec2 sz = _bluecrystal->getContentSize();
			Vec2 v1 = v - Vec2(0, sz.y / 2 + 50);
			Vec2 v2 = v + Vec2(0, sz.y / 2 + 50);
			Vec2 v3 = v1 - Vec2(100, 0);
			Vec2 v4 = v2 - Vec2(100, 0);
			Soldier* soldier1 = Soldier::CreateWithName("XiaoBin/blue/blue1.PNG");
			soldier1->setPosition(v1);
			soldier1->_name = 1;
			soldier1->setFlag(Flag::BLUE);
			_tileMap->addChild(soldier1, 9);
			if (soldier1->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier1);

			}
			else if (soldier1->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier1);
			}
			_soldier.push_back(soldier1);
			Soldier* soldier2 = Soldier::CreateWithName("XiaoBin/blue/blue3.PNG");
			soldier2->setPosition(v3);
			this->_name = 2;
			soldier2->setFlag(Flag::BLUE);
			_tileMap->addChild(soldier2, 9);
			if (soldier2->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier2);

			}
			else if (soldier2->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier2);
			}
			_soldier.push_back(soldier2);
			Soldier* soldier3 = Soldier::CreateWithName("XiaoBin/blue/blue1.PNG");
			soldier3->setPosition(v2);
			soldier3->_name = 1;
			soldier3->setFlag(Flag::BLUE);
			_tileMap->addChild(soldier3, 9);
			if (soldier3->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier3);

			}
			else if (soldier3->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier3);
			}
			_soldier.push_back(soldier3);
			Soldier* soldier4 = Soldier::CreateWithName("XiaoBin/blue/blue3.PNG");
			soldier4->_name = 2;
			soldier4->setPosition(v4);
			soldier4->setFlag(Flag::BLUE);
			_tileMap->addChild(soldier4, 9);
			if (soldier4->getFlag() == _player->getFlag())
			{
				player_flag.push_back(soldier4);

			}
			else if (soldier4->getFlag() == _enemy->getFlag())
			{
				enemy_flag.push_back(soldier4);
			}
			_soldier.push_back(soldier4);
		}
	}
	if (!enemy_flag.empty())
	{
		for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
		{
			(*i)->doHP();
		}
	}
	if (!player_flag.empty())
	{
		for (auto i = player_flag.begin(); i != player_flag.end(); i++)
		{
			(*i)->doHP();
		}
	}
}

void GameScene2::SkillTime()
{
	long long now_time = GetCurrentTime();
	long long t1 = now_time - _player->_attackTime1;
	long long t2 = now_time - _player->_attackTime2;
	long long t3 = now_time - _player->_attackTime3;
	if (t1 < 8000)
	{
		_skilltime1->setVisible(true);
		int cc = -(t1 - 8000) / 1000 + 1;
		_skilltime1->setString(std::to_string(cc));
	}
	else
	{
		_skilltime1->setVisible(false);
	}
	if (t2 < 12000)
	{
		_skilltime2->setVisible(true);
		int cc = -(t2 - 12000) / 1000 + 1;
		_skilltime2->setString(std::to_string(cc));
	}
	else
	{
		_skilltime2->setVisible(false);
	}
	if (t3 < 18000)
	{
		_skilltime3->setVisible(true);
		int cc = -(t3 - 18000) / 1000 + 1;
		_skilltime3->setString(std::to_string(cc));
	}
	else
	{
		_skilltime3->setVisible(false);
	}
}

void GameScene2::doHP()
{

	_player->doHP();
	_enemy->doHP();
}

void GameScene2::soldierAI()
{
	if (!_soldier.empty())
	{
		for (auto i = _soldier.begin(); i != _soldier.end(); i++)
		{
			long long now_time = GetCurrentTime();
			bool GetEnemy = false;
			Model *target;
			Vec2 v1 = (*i)->getPosition();
			for (auto j = enemy_flag.begin(); j != enemy_flag.end(); j++)
			{
				if ((*j)->getFlag() == (*i)->getFlag())
					break;
				Vec2 v2 = (*j)->getPosition();
				Vec2 v3 = v1 - v2;
				float yy = v3.getLength();
				if (yy < 600)
				{
					GetEnemy = true;
					target = (*j);
					break;
				}

			}
			if (!GetEnemy) {
				for (auto j = player_flag.begin(); j != player_flag.end(); j++)
				{
					if ((*j)->getFlag() == (*i)->getFlag())
						break;
					Vec2 v2 = (*j)->getPosition();
					Vec2 v3 = v1 - v2;
					float yy = v3.getLength();
					if (yy < 600)
					{
						GetEnemy = true;
						target = (*j);
						break;
					}

				}
			}
			if (!GetEnemy && !_player->isDie())
			{
				if (_player->getFlag() != (*i)->getFlag())
				{
					Vec2 v2 = _player->getPosition();
					Vec2 v3 = v1 - v2;
					float yy = v3.getLength();
					if (yy < 600)
					{
						GetEnemy = true;
						target = _player;
					}
				}
			}
			if (!GetEnemy && !_enemy->isDie())
			{
				if (_enemy->getFlag() != (*i)->getFlag())
				{
					Vec2 v2 = _enemy->getPosition();
					Vec2 v3 = v1 - v2;
					float yy = v3.getLength();
					if (yy < 600)
					{
						GetEnemy = true;
						target = _enemy;
					}
				}
			}
			if (GetEnemy)
			{
				if ((*i)->getFlag() == Flag::BLUE)
					(*i)->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
				else if ((*i)->getFlag() == Flag::RED)
					(*i)->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
				soldierAttack(*i);
			}
			else
			{
				if ((*i)->getFlag() == Flag::BLUE)
					(*i)->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = true;
				else if ((*i)->getFlag() == Flag::RED)
					(*i)->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = true;
			}
		}
	}
}

/*
	程序是通过enemy和player来区分敌我的
*/
//void GameScene::enemyAI()
//{
//	static bool cc = 0;
//	if (_enemy->isDie())
//	{
//		if (cc)
//		{
//			enemy_onKeyReleased(cocos2d::EventKeyboard::KeyCode::KEY_A, _enemy);
//			cc = 0;
//		}
//		return;
//	}
//	long long now_time = GetCurrentTime();
//	bool GetEnemy = false;
//	Model *target;
//	Vec2 v1 = _enemy->getPosition();
//	if (!GetEnemy) {
//		for (auto j = player_flag.begin(); j != player_flag.end(); j++)
//		{
//			if ((*j)->getFlag() == _enemy->getFlag())
//				break;
//			Vec2 v2 = (*j)->getPosition();
//			Vec2 v3 = v1 - v2;
//			float yy = v3.getLength();
//			if (yy < 300)
//			{
//				GetEnemy = true;
//				target = (*j);
//				break;
//			}
//
//		}
//	}
//	if (!GetEnemy && !_player->isDie())
//	{
//		if (_player->getFlag() != _enemy->getFlag())
//		{
//			Vec2 v2 = _player->getPosition();
//			Vec2 v3 = v1 - v2;
//			float yy = v3.getLength();
//			if (yy < 300)
//			{
//				GetEnemy = true;
//				target = _player;
//			}
//		}
//	}
//	if (GetEnemy)
//	{
//		long long now_time = GetCurrentTime();
//		if (now_time - _enemy->_attackTime1 > 8000)
//		{
//			enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_1, _enemy);
//		}
//		else if (now_time - _enemy->_attackTime2 > 12000)
//		{
//			enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_2, _enemy);
//		}
//		else if(now_time - _enemy->_attackTime3 > 18000)
//		{
//			enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_3, _enemy);
//		}
//		else
//		{
//			
//			enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_J, _enemy);
//		}
//		cc = 0;
//	}
//	else
//	{
//		if (!cc)
//		{
//			enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A, _enemy);
//			cc = 1;
//		}
//	}
//}


void GameScene2::enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, Hero * _player)
{
	if (!_player->isDie() && GetCurrentTime() > _player->getEndTime())
	{
		switch (keycode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = true;
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
				_player->StopWalking("Left-Down");
				_player->WalkWithDirection("Left-Up");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
				_player->StopWalking("Right-Down");
				_player->WalkWithDirection("Right-Up");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
				_player->StopWalking("Down");
				_player->WalkWithDirection("Up");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
				_player->StopWalking("Left");
				_player->WalkWithDirection("Left-Up");
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
				_player->StopWalking("Right");
				_player->WalkWithDirection("Right-Up");
				return;
			}
			_player->WalkWithDirection("Up");
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = true;
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
				_player->StopWalking("Left-Up");
				_player->WalkWithDirection("Left-Down");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
				_player->StopWalking("Right-Up");
				_player->WalkWithDirection("Right-Down");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
				_player->StopWalking("Up");
				_player->WalkWithDirection("Down");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
				_player->StopWalking("Right");
				_player->WalkWithDirection("Right-Down");
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
				_player->StopWalking("Left");
				_player->WalkWithDirection("Left-Down");
				return;
			}

			_player->WalkWithDirection("Down");
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = true;
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
				_player->StopWalking("Left-Up");
				_player->WalkWithDirection("Right-Up");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
				_player->StopWalking("Left-Down");
				_player->WalkWithDirection("Right-Down");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
				_player->StopWalking("Left");
				_player->WalkWithDirection("Right");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
				_player->StopWalking("Up");
				_player->WalkWithDirection("Right-Up");
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
				_player->StopWalking("Down");
				_player->WalkWithDirection("Right-Down");
				return;
			}

			_player->WalkWithDirection("Right");
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = true;
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
				_player->StopWalking("Right-Up");
				_player->WalkWithDirection("Left-Up");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] && _player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
				_player->StopWalking("Right-Down");
				_player->WalkWithDirection("Left-Down");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
				_player->StopWalking("Right");
				_player->WalkWithDirection("Left");
				_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
				_player->StopWalking("Up");
				_player->WalkWithDirection("Left-Up");
				return;
			}
			if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
				_player->StopWalking("Down");
				_player->WalkWithDirection("Left-Down");
				return;
			}

			_player->WalkWithDirection("Left");
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			enemyAttack();
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			enemyAttack_1();
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			enemyAttack_2();
			return;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
			enemyAttack_3();
			return;
			break;
		default:
			break;
		}
	}
}
void GameScene2::enemy_onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, Hero * _player)
{
	switch (keycode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W])
			break;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left-Up");
			_player->WalkWithDirection("Left");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right-Up");
			_player->WalkWithDirection("Right");
			return;
		}

		_player->StopWalking("Up");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S])
			break;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			_player->StopWalking("Left-Down");
			_player->WalkWithDirection("Left");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			_player->StopWalking("Right-Down");
			_player->WalkWithDirection("Right");
			return;
		}
		_player->StopWalking("Down");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D])
			break;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Right-Down");
			_player->WalkWithDirection("Down");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Right-Up");
			_player->WalkWithDirection("Up");
			return;
		}
		_player->StopWalking("Right");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (!_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A])
			break;
		_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_A] = false;
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_D]) {
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_S]) {
			_player->StopWalking("Left-Down");
			_player->WalkWithDirection("Down");
			return;
		}
		if (_player->keys[cocos2d::EventKeyboard::KeyCode::KEY_W]) {
			_player->StopWalking("Left-Up");
			_player->WalkWithDirection("Up");
			return;
		}
		_player->StopWalking("Left");
		break;
	default:
		break;
	}
}
