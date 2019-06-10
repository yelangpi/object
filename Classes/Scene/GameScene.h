#ifndef __SCENE_GAMESCENE_H__
#define __SCENE_GAMESCENE_H__
#include "cocos2d.h"
#include"Model/Hero.h"
#include"Model/FlyingBox.h"
#include<vector>
class GameScene : public cocos2d::Layer
{
public:
	cocos2d::PhysicsWorld* m_world;
	void setPhyWorld(cocos2d::PhysicsWorld* world) { m_world = world; };
	static cocos2d::Scene* createScene(std::string name1, std::string name2);
	virtual void onEnterTransitionDidFinish();
	std::string _PlayerName;
	std::string _EnemyName;
	Hero* _player;
	Hero* _enemy;
	long long _nowtime = 0;
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	CREATE_FUNC(GameScene);
	static GameScene* createWithName(std::string name1, std::string name2);
	bool initWithName(std::string name1,std::string name2);
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
	void playerAttack();
	void playerAttack_1();
	void playerAttack_2();
	void playerAttack_3();
	std::vector<Model*>player_flag;
	std::vector<Model*>enemy_flag;
	void MoveMap(float delta);
	cocos2d::Layer* FixedLayer;
	float now_x = 0;
private:
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _collidable;
	
};
#endif
