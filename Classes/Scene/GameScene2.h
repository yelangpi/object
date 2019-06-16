#pragma once
#ifndef __SCENE_GAMESCENE2_H__
#define __SCENE_GAMESCENE2_H__
#include "cocos2d.h"
#include"Model/Hero.h"
#include"Model/FlyingBox.h"
#include"Model/Butterfly.h"
#include"Model/RangeSkill.h"
#include"Model/ImpactWave.h"
#include"Model/Shield.h"
#include"Model/Tower.h"
#include"Order.h"
#include"client.h"
#include<vector>
class GameScene2 : public cocos2d::Layer
{
public:
	bool isAp = false;
	chat_client *client;
	//记录敌人上一帧的状态
	Order preOrderEnemy;
	//记录自己上一帧的状态
	Order preOrder;
	//在这一帧中现在的键盘的状态
	Order order;
	cocos2d::PhysicsWorld* m_world;
	void setPhyWorld(cocos2d::PhysicsWorld* world) { m_world = world; };
	static cocos2d::Scene* createScene(std::string name1, std::string name2, chat_client* _client, char FLAG);
	virtual void onEnterTransitionDidFinish();
	std::string _PlayerName;
	std::string _EnemyName;
	Hero* _player;
	Hero* _enemy;
	Tower*_bluecrystal;
	Tower*_redcrystal;
	Tower*_bluetower;
	Tower*_redtower;
	std::vector<Tower*>_tower;
	cocos2d::Label* _skilltime1;
	cocos2d::Label* _skilltime2;
	cocos2d::Label* _skilltime3;
	long long _nowtime = 0;
	long long _soldiertime = 9999999999999999;
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	CREATE_FUNC(GameScene2);
	static GameScene2* createWithName(std::string name1, std::string name2, chat_client * _client, char FLAG);
	bool initWithName(std::string name1, std::string name2, chat_client * _client, char FLAG);
	void update(float delta) override;
	std::map<std::pair<std::string, std::string>, int>Dirction_Animation_Walk_Number;
	std::map<std::pair<std::string, std::string>, int>Dirction_Animation_Attack_Number;
	std::map<std::pair<std::string, std::string>, int>Dirction_Animation_Skill1_Number;
	std::map<std::pair<std::string, std::string>, int>Dirction_Animation_Skill2_Number;
	std::map<std::pair<std::string, std::string>, int>Dirction_Animation_Skill3_Number;
	void LoadingYaSeAnimation();
	void LoadingAnimation(std::string sprite_name);
	std::vector<FlyingBox*>_flying;
	std::vector<FlyingBox*>_Scheduleflying;
	std::vector<Butterfly*>_Butterfly;
	std::vector<Butterfly*>_ScheduleButterfly;
	std::vector<RangeSkill*>_RangeSkill;
	std::vector<ImpactWave*>_ImpactWave;
	std::vector<Shield*>_Shield;
	std::vector<Soldier*>_soldier;
	void playerAttack();
	void playerAttack_1();
	void playerAttack_2();
	void playerAttack_3();
	void enemyAttack();
	void enemyAttack_1();
	void enemyAttack_2();
	void enemyAttack_3();
	void towerAttack();
	void soldierAttack(Soldier* soldier);
	std::vector<Model*>player_flag;
	std::vector<Model*>enemy_flag;
	bool out_of_windows(cocos2d::Vec2 v);
	void MoveMap(float delta);
	float now_x = 0;
	void doRangeSkill();
	void doFlying();
	void doButterfly();
	void doImpactWave();
	void doShield();
	void initMap();
	void initAnimation();
	void initHero(char FLAG);
	void initSkill();
	void initHP();
	void initTower();
	void initSoldier();
	void SkillTime();
	void doHP();
	void soldierAI();
	void enemyAI();
	void enemy_onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, Hero * _player);
	void enemy_onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, Hero * _player);
	void YLP_W(int status);
	void YLP_S(int status);
	void YLP_A(int status);
	void YLP_D(int status);
	void YLP_J(int status);
	void YLP_1(int status);
	void YLP_2(int status);
	void YLP_3(int status);
	void Answering(const Order& tmpOrder);
	void AnsweringEnemy(const Order& tmpOrder);
	void YLP_ENEMY_W(int status);
	void YLP_ENEMY_S(int status);
	void YLP_ENEMY_A(int status);
	void YLP_ENEMY_D(int status);
	void YLP_ENEMY_J(int status);
	void YLP_ENEMY_1(int status);
	void YLP_ENEMY_2(int status);
	void YLP_ENEMY_3(int status);
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;

};
#endif
