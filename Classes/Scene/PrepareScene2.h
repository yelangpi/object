#ifndef __SCENE_PREPARESCENE2_H__
#define __SCENE_PREPARESCENE2_H__
#include "cocos2d.h"
#include"client.h"
#include"Order.h"
class PrepareScene2 : public cocos2d::Layer
{
private:
	cocos2d::MenuItemImage* _playerbutton1, *_playerbutton2, *_playerbutton3;
	cocos2d::MenuItemImage* _computerbutton1, *_computerbutton2, *_computerbutton3;
	cocos2d::MenuItemImage*_startbutton;
	cocos2d::Sprite*_playerselected1, *_playerselected2, *_playerselected3;
	cocos2d::Sprite*_computerselected1, *_computerselected2, *_computerselected3;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void BackCallback(Ref *Psender);
	void playerCallback1(Ref *Psender);
	void playerCallback2(Ref *Psender);
	void playerCallback3(Ref *Psender);
	void computerCallback1(Ref *Psender);
	void computerCallback2(Ref *Psender);
	void computerCallback3(Ref *Psender);
	void StartGameCallback(Ref *Psender);
	int _playernumber = 0;
	int _computernumber = 0;
	bool isConnect = false;
	char FLAG = 'n';
	chat_client * client;
	//创建场景1时要传入已经初始化好的客户端 来给自己的服务器传信息
	//注意 这个场景是选人物的场景 应该完成以下几个功能
	//我方选了人，然后向服务器发我选好人物的信息
	//我要接收到对方发的包 知道对方选了那个人物 在哪个方向
	//然后就可以进入下一个方向
	//同时就确定了自己和对方的阵营 然后在GameScene里解包的时候就可以确定调用哪一个函数
	static PrepareScene2 * create();
	void update(float a);

};
#endif