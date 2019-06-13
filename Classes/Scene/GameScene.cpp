#include "GameScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"Model/Hero.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * GameScene::createScene(std::string name1,std::string name2)
{
	auto scene = Scene::create();
	auto layer = GameScene::createWithName(name1,name2);

	scene->addChild(layer,0);
	return scene;
}

bool GameScene::initWithName(std::string name1,std::string name2)
{
	if (!Layer::init())
	{
		return false;
	}
	Vec2 v1 = Director::getInstance()->getWinSize();
	this->_PlayerName = name1;
	this->_EnemyName = name2;
	initMap();
	initAnimation();
	initHero();
	initSkill();
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
	doFlying();
	doButterfly();
	doRangeSkill();
	SkillTime();
	doHP();
	doImpactWave();
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
					f->target_length.push_back(_enemy->getPosition().y - f->getPosition().y);
				}
				else
				{
					f->target_length.push_back(_enemy->getPosition().x - f->getPosition().x);

				}
			}
			if (!enemy_flag.empty())
			{
				for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
				{
					f->target.push_back(*i);
					if (f->_direction == "Up" || f->_direction == "Down")
					{
						f->target_length.push_back((*i)->getPosition().y - f->getPosition().y);
					}
					else
					{
						f->target_length.push_back((*i)->getPosition().x - f->getPosition().x);

					}
				}
			}
			f->setPosition(ballposition);
			f->setVisible(true);
			_tileMap->addChild(f, 10);
			_ImpactWave.push_back(f);
		}
	}
}
void GameScene::playerAttack_2()
{
	//冷却时间 12 seconds
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
		if (GetCurrentTime() - _player->_attackTime2 >= 12000 && GetEnemy)
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
		bool GetEnemy = false;
		Model* cc;
		RangeSkill* f = RangeSkill::createWithName("HouYi/HouYi/Attack3/0000.png");
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			GetEnemy = true;
			cc = _enemy;
		}
		if (!enemy_flag.empty()||GetEnemy)
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
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - f->getPosition().x)*(_enemy->getPosition().x - f->getPosition().x) + (_enemy->getPosition().y - f->getPosition().y)*(_enemy->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width/4)
		{
			
		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - f->getPosition().x)*((*i)->getPosition().x - f->getPosition().x) + ((*i)->getPosition().y - f->getPosition().y)*((*i)->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width / 4)
				{
					
				}
			}
		}
		_RangeSkill.push_back(f);
		_player->_attackTime2 = GetCurrentTime();
			_tileMap->addChild(f, 10);
		}
	}
}
void GameScene::playerAttack_3()
{
	//冷却时间  18 seconds
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
			if (GetCurrentTime() - _player->_attackTime3 >= 18000 && GetEnemy) {
				isDo = true;
				f->setNowtime(GetCurrentTime() + 34+(a-1)*200);
				f->setOwner(_player);
				_Scheduleflying.push_back(f);
				f->setVisible(false);
				_tileMap->addChild(f, 10);
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
		Butterfly* f = Butterfly::createWithName(cocos2d::StringUtils::format("HouYi/HouYi/Attack2/%s/0000.PNG", _player->Now_Direction.c_str()));
		if (GetCurrentTime() - _player->_attackTime3 >= 18000) {
			_player->_attackTime3 = GetCurrentTime();
			f->setNowtime(GetCurrentTime() + 34);
			f->setDirection(_player->Now_Direction);
			_ScheduleButterfly.push_back(f);
			f->setVisible(false);
			f->setOwner(_player);
			_tileMap->addChild(f, 10);
		}
	}
}

bool GameScene::out_of_windows(cocos2d::Vec2 v)
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

void GameScene::doRangeSkill()
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

void GameScene::doFlying()
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
				if (abs((*i)->getPosition().x - _enemy->getPosition().x) <= 20 && abs((*i)->getPosition().y - _enemy->getPosition().y) <= 20) 
				{
					Target->setCurrentHp(Target->getCurrentHp() - 100);
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

void GameScene::doButterfly()
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

			if (abs((*i)->getPosition().x - _enemy->getPosition().x) <= 50 && abs((*i)->getPosition().y - _enemy->getPosition().y) <= 50)
			{

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

void GameScene::doImpactWave()
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
						int yy = (*j)->getPosition().y-(*i)->getPosition().y;
						if (xx*yy < 0&&(*j)->getPosition().x<(*i)->getPosition().x+(*i)->getContentSize().width/2&& (*j)->getPosition().x > (*i)->getPosition().x - (*i)->getContentSize().width / 2)
						{
							(*j)->setCurrentHp((*j)->getCurrentHp() - 100);
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
						if (xx*yy < 0 && (*j)->getPosition().y<(*i)->getPosition().y + (*i)->getContentSize().height / 2 && (*j)->getPosition().y >(*i)->getPosition().y - (*i)->getContentSize().height / 2)
						{
							(*j)->setCurrentHp((*j)->getCurrentHp() - 100);
						}
						*k = yy;
					}
				}
			}
			if(now_time>(*i)->getEndtime())
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

void GameScene::initMap()
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
	this->addChild(_tileMap, 0);
}

void GameScene::initAnimation()
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
	//

}

void GameScene::initHero()
{
	Vec2 v1 = Director::getInstance()->getWinSize();
	auto player = Hero::CreateWithName(_PlayerName);
	auto enemy = Hero::CreateWithName(_EnemyName);
	_player = player;
	_enemy = enemy;
	_player->setPosition(v1.x / 2, v1.y / 4);
	_enemy->setPosition(v1.x / 2, v1.y / 4 * 3);
	_player->setFlag(Flag::BLUE);
	_enemy->setFlag(Flag::RED);
	_tileMap->addChild(player, 6);
	_tileMap->addChild(enemy, 6);
}

void GameScene::initSkill()
{
	auto skill1 = Sprite::create(cocos2d::StringUtils::format("%s/jineng1.png", _player->getName().c_str()));
	auto skill2 = Sprite::create(cocos2d::StringUtils::format("%s/jineng2.png", _player->getName().c_str()));
	auto skill3 = Sprite::create(cocos2d::StringUtils::format("%s/jineng3.png", _player->getName().c_str()));
	Vec2 w = Director::getInstance()->getWinSize();
	Vec2 v = skill1->getContentSize();
	Vec2 v1 = Vec2(w.x - 7*v.x / 2, v.y / 2);
	Vec2 v2 = Vec2(w.x - 4*v.x / 2, v.y / 2);
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

void GameScene::initHP()
{
	cocos2d::Sprite*HPbox = cocos2d::Sprite::create("xuetiao/xuetiao2.png");
	cocos2d::Sprite*HPrectangle= cocos2d::Sprite::create("xuetiao/xuetiao1.png");
	
}
void GameScene::SkillTime()
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

void GameScene::doHP()
{
	_player->doHP();
	_enemy->doHP();
}

