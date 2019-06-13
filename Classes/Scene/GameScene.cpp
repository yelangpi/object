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
	if (!_player->isDie()&&GetCurrentTime()>_player->getEndTime())
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
	_enemy->Move(delta);
	long long now_time = GetCurrentTime();
	doFlying();
	doButterfly();
	doRangeSkill();
	doShield();
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
		animation_00[i]->setLoops(1);
		AnimationCache::getInstance()->addAnimation(animation_00[i], StringUtils::format("%s_attack_%s", "YaSe", dir[i].c_str()));
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
			if(_player->getEndTime()< GetCurrentTime() + 250)
			_player->setEndTime(GetCurrentTime() + 250);
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
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
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						_enemy->setCurrentHp(_enemy->getCurrentHp() - 100);
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
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
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
		if ((!_enemy->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			f->target.push_back(_enemy);
			if (!GetEnemy)cc = _enemy;
			GetEnemy = true;

		}
		if (!enemy_flag.empty())
		{
			for (auto i = enemy_flag.begin(); i != enemy_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _player->getPosition().x)*((*i)->getPosition().x - _player->getPosition().x) + ((*i)->getPosition().y - _player->getPosition().y)*((*i)->getPosition().y - _player->getPosition().y) <= 300 * 300)
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
			else if ((an >= 3*3.14 / 4 && an <= 3.14)|| (an >= -3.14 && an <= -3*3.14/4))
			{
				str = "Left";
			}
			else if (an >= -3*3.14 / 4 && an <= -3.14 / 4)
			{
				str = "Down";
			}
			_player->initWithFile(StringUtils::format("HouYi/HouYi/Walk/%s/0000.PNG",str.c_str()));
			_player->Now_Direction = str;
			f->initWithFile(cocos2d::StringUtils::format("HouYi/HouYi/Attack/%s/0000.PNG", _player->Now_Direction.c_str()));
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_player);
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 10);
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
	else if (_player->getName() == "YaSe")
	{

	}
	else if(_player->getName() == "HouYi")
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
			for(auto i=enemy_flag.begin();i!=enemy_flag.end();i++)
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
		if (!enemy_flag.empty()&&!GetEnemy)
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
		if (GetCurrentTime() - _player->_attackTime3 >= 18000)
		{
			
			Vec2 v1 = _player->getPosition();
			Vec2 v2 = _enemy->getPosition();
			if (v1.getDistance(v2) < 500&&_enemy->isDie())
			{
				_player->_attackTime3 = GetCurrentTime();
				_player->setPosition(v2);
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
			_tileMap->addChild(f, 10);
		}
	}
}

//
void GameScene::enemyAttack()
{
	if (_enemy->getName() == "DaJi")
	{
		bool GetEnemy = false;
		FlyingBox* f = FlyingBox::createWithName(cocos2d::StringUtils::format("DaJi/DaJi/Attack/%s/0000.PNG", _enemy->Now_Direction.c_str()));
		if ((!_player->isDie()) && (_player->getPosition().x - _enemy->getPosition().x)*(_player->getPosition().x - _enemy->getPosition().x) + (_player->getPosition().y - _enemy->getPosition().y)*(_player->getPosition().y - _enemy->getPosition().y) <= 300 * 300)
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
		if (GetCurrentTime() - _enemy->_attackTime >= 500 && GetEnemy) {
			_enemy->_attackTime = GetCurrentTime();
			if (_enemy->getEndTime() < GetCurrentTime() + 250)
				_enemy->setEndTime(GetCurrentTime() + 250);
			f->setNowtime(GetCurrentTime() + 34);
			f->setOwner(_enemy);
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
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						_player->setCurrentHp(_player->getCurrentHp() - 100);
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
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right")
				{
					if ((v.getAngle() >= -3.14 / 2 && v.getAngle() <= 3.14 / 2))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}

				}
				else if (dir == "Up")
				{
					if ((v.getAngle() >= 0 && v.getAngle() <= 3.14))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Down")
				{
					float c = v.getAngle();
					if ((v.getAngle() >= -3.14 && v.getAngle() <= 0))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Up")
				{
					if ((v.getAngle() >= 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Left-Down")
				{
					if ((v.getAngle() >= 3 * 3.14 / 4 && v.getAngle() <= 3.14) || (v.getAngle() >= -3.14 && v.getAngle() <= -3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Up")
				{
					if ((v.getAngle() >= -3.14 / 4 && v.getAngle() <= 3 * 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
					}
				}
				else if (dir == "Right-Down")
				{
					if ((v.getAngle() >= -3 * 3.14 / 4 && v.getAngle() <= 3.14 / 4))
					{
						(*i)->setCurrentHp((*i)->getCurrentHp() - 100);
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
		if ((!_player->isDie()) && (_enemy->getPosition().x - _player->getPosition().x)*(_enemy->getPosition().x - _player->getPosition().x) + (_enemy->getPosition().y - _player->getPosition().y)*(_enemy->getPosition().y - _player->getPosition().y) <= 500 * 500)
		{
			f->target.push_back(_player);
			if (!GetEnemy)cc = _player;
			GetEnemy = true;

		}
		if (!player_flag.empty())
		{
			for (auto i = player_flag.begin(); i != player_flag.end(); i++)
			{
				if (((*i)->getPosition().x - _enemy->getPosition().x)*((*i)->getPosition().x - _enemy->getPosition().x) + ((*i)->getPosition().y - _enemy->getPosition().y)*((*i)->getPosition().y - _enemy->getPosition().y) <= 300 * 300)
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
			_Scheduleflying.push_back(f);
			f->setVisible(false);
			_tileMap->addChild(f, 1);
		}
	}
}
void GameScene::enemyAttack_1()
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
					f->target_length.push_back(_player->getPosition().y - f->getPosition().y);
				}
				else
				{
					f->target_length.push_back(_player->getPosition().x - f->getPosition().x);

				}
			}
			if (!player_flag.empty())
			{
				for (auto i = player_flag.begin(); i != player_flag.end(); i++)
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
	else if (_enemy->getName() == "YaSe")
	{

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
void GameScene::enemyAttack_2()
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
			_tileMap->addChild(f, 1);
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
				
			}
			if (!player_flag.empty())
			{
				for (auto i = player_flag.begin(); i != player_flag.end(); i++)
				{
					if (((*i)->getPosition().x - f->getPosition().x)*((*i)->getPosition().x - f->getPosition().x) + ((*i)->getPosition().y - f->getPosition().y)*((*i)->getPosition().y - f->getPosition().y) <= f->getContentSize().width * f->getContentSize().width / 4)
					{

					}
				}
			}
			_RangeSkill.push_back(f);
			_enemy->_attackTime2 = GetCurrentTime();
			_tileMap->addChild(f, 10);
		}
	}
}
void GameScene::enemyAttack_3()
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
			if (v1.getDistance(v2) < 500&&!_player->isDie())
			{
				_enemy->_attackTime3 = GetCurrentTime();
				_enemy->setPosition(v2);
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
			if ((*i)->getOwner() == _player) 
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
			else if ((*i)->getOwner() == _enemy)
			{
				if (abs((*i)->getPosition().x - _player->getPosition().x) <= 50 && abs((*i)->getPosition().y - _player->getPosition().y) <= 50)
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

void GameScene::doShield()
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
		if (now_time >(*i)->getNowtime())
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
					(*j)->setCurrentHp((*j)->getCurrentHp() - 100);
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
	LoadingYaSeAnimation();
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


