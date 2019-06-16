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
	//��������1ʱҪ�����Ѿ���ʼ���õĿͻ��� �����Լ��ķ���������Ϣ
	//ע�� ���������ѡ����ĳ��� Ӧ��������¼�������
	//�ҷ�ѡ���ˣ�Ȼ�������������ѡ���������Ϣ
	//��Ҫ���յ��Է����İ� ֪���Է�ѡ���Ǹ����� ���ĸ�����
	//Ȼ��Ϳ��Խ�����һ������
	//ͬʱ��ȷ�����Լ��ͶԷ�����Ӫ Ȼ����GameScene������ʱ��Ϳ���ȷ��������һ������
	static PrepareScene2 * create();
	void update(float a);

};
#endif