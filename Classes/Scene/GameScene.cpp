#include "GameScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"Model/Hero.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * GameScene::createScene(std::string name1,std::string name2)
{
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::createWithName(name1,name2);
	auto FixedLayer = Layer::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	layer->FixedLayer = FixedLayer;
	scene->addChild(layer,0);
	scene->addChild(FixedLayer,1);
	return scene;
}

bool GameScene::initWithName(std::string name1,std::string name2)
{
	if (!Layer::init())
	{
		return false;
	}
	Vec2 v1 = Director::getInstance()->getWinSize();
	_tileMap = TMXTiledMap::create("TileMap/TileMap.tmx");
	Vec2 v2 = _tileMap->getContentSize();
	_tileMap->setScale(v1.y / v2.y);
	_tileMap->setAnchorPoint(Vec2::ZERO);
	_tileMap->getMapSize();
	_tileMap->setPosition(Vec2(0,0));
	_tileMap->getLayer("background")->setVisible(true);
	_tileMap->getLayer("red")->setVisible(true);
	_tileMap->getLayer("blue")->setVisible(true);
	this->addChild(_tileMap, 0);

	//
	this->_PlayerName = name1;
	this->_EnemyName = name2;
	//
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
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Up")] = 0;
	Dirction_Animation_Attack_Number[std::make_pair("YaSe", "Down")] = 0;
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
	//
	
	auto player = Hero::CreateWithName(_PlayerName);
	auto enemy = Hero::CreateWithName(_EnemyName);
	_player = player;
	_enemy = enemy;
	_player->setPosition(v1.x / 2, v1.y / 4);
	_enemy->setPosition(v1.x / 2, v1.y / 4 * 3);
	
	
	_tileMap->addChild(player, 6);
	_tileMap->addChild(enemy, 6);
	
	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	scheduleUpdate();

	return true;
}
void GameScene::onEnterTransitionDidFinish()
{
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playBackgroundMusic("sound/File0001.wav", true);
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
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
		playerAttack();
		return;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		playerAttack_1();
		return;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		playerAttack_2();
		return;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		playerAttack_3();
		return;
		break;
	default:
		break;
	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
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

GameScene * GameScene::createWithName(std::string name1,std::string name2)
{
	GameScene *pRet = new(std::nothrow) GameScene(); 
	if (pRet && pRet->initWithName(name1,name2)) 
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

void GameScene::update(float delta)
{
	_player->Move(delta);
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
				if (!(*j)->isDie())
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
				if (abs((*i)->getPosition().x - _enemy->getPosition().x) <= 20 && abs((*i)->getPosition().y - _enemy->getPosition().y) <= 20) {

					(*i)->setVisible(false);
					(*i)->removeFromParent();
					i = _flying.erase(i);
				}
				else
					++i;
			}
			else
				i = _flying.erase(i);
		}
	
	}
	MoveMap(delta);
}
void GameScene::LoadingYaSeAnimation()
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
		animation_00[i]->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(animation_00[i], StringUtils::format("%s_attack_%s", "YaSe", dir[i].c_str()));
	}
	Animation* animation_01[8];
	for (int i = 0; i < 8; i++)
	{
		animation_01[i] = Animation::create();
		for (int j = 0; j <= Dirction_Animation_Attack_Number[std::make_pair("YaSe", dir[i])]; j++)
		{
			animation_01[i]->addSpriteFrameWithFile(StringUtils::format("%s/%s/Skill1/%s/000%d.PNG", "YaSe", "YaSe", dir[i].c_str(), j));
		}
		animation_01[i]->setDelayPerUnit(0.25f);
		animation_01[i]->setLoops(-1);
		AnimationCache::getInstance()->addAnimation(animation_01[i], StringUtils::format("%s_skill1_%s", "YaSe", dir[i].c_str()));
	}
}
void GameScene::LoadingAnimation(std::string sprite_name)
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

void GameScene::playerAttack()
{
	if (_player->getName() == "DaJi")
	{
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 300 * 300)
		{
			f->target.push_back(_enemy);
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 300 * 300)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime >= 500 && GetEnemy) {
			_player->_attackTime = GetCurrentTime();
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 1);
		}
	}
	else if (_player->getName() == "YaSe")
	{

	}
	else if (_player->getName() == "HouYi")
	{
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("HouYi/HouYi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			f->target.push_back(_enemy);
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 300 * 300)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime >= 300 && GetEnemy) {
			_player->_attackTime = GetCurrentTime();
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 1);
		}
	}
}
void GameScene::playerAttack_1()
{

}
void GameScene::playerAttack_2()
{
	if (_player->getName() == "DaJi")
	{
		bool isDo = false;
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName("DaJi/DaJi/Skill2/0001.PNG");
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 300 * 300)
		{
			f->target.push_back(_enemy);
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 300 * 300)
				{
					f->target.push_back(*i);
					GetEnemy = true;
				}
			}
		}
		if (GetCurrentTime() - _player->_attackTime2 >= 15000 && GetEnemy)
		{
			isDo = true;
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 1);
		}
		if (isDo)
		{
		_player->_attackTime2 = GetCurrentTime();
		}
	}
	else if (_player->getName() == "YaSe")
	{

	}
	else if (_player->getName() == "HouYi")
	{

	}
}
void GameScene::playerAttack_3()
{
	if (_player->getName() == "DaJi")
	{
		bool isDo = false;
		for (int a = 1; a <= 5; a++) {
			bool GetEnemy = false;
			FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
			if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 300 * 300)
			{
				f->target.push_back(_enemy);
				GetEnemy = true;

			}
			if (!enemy_flag.empty())
			{
				for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				{
					if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 300 * 300)
					{
						f->target.push_back(*i);
						GetEnemy = true;
					}
				}
			}
			if (GetCurrentTime() - _player->_attackTime3 >= 15000 && GetEnemy) {
				isDo = true;
				f->setNowtime(GetCurrentTime() + 34+(a-1)*200);
				f->setOwner(_player);
				_Scheduleflying.push_back(f);
				f->setVisible(false);
				_tileMap->addChild(f, 1);
			}
		}
		if(isDo)
		_player->_attackTime3 = GetCurrentTime();
	}
	else if (_player->getName() == "YaSe")
	{

	}
	else if (_player->getName() == "HouYi")
	{

	}
}

void GameScene::MoveMap(float delta)
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

