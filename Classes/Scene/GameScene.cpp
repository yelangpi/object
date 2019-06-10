#include "GameScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"Model/Hero.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * GameScene::createScene(std::string name1,std::string name2)
{

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

//void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)//
//GameScene * GameScene::createWithName(std::string name1,std::string name2)


//void GameScene::update(float delta)

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
//void GameScene::LoadingAnimation(std::string sprite_name)


//void GameScene::playerAttack()

//void GameScene::playerAttack_1()

//void GameScene::playerAttack_2()

//void GameScene::playerAttack_3()


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

