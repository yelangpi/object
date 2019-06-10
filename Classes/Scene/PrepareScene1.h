#ifndef __SCENE_PREPARESCENE1_H__
#define __SCENE_PREPARESCENE1_H__
#include "cocos2d.h"
class PrepareScene1 : public cocos2d::Layer
{
private:
	cocos2d::MenuItemImage* _playerbutton1,*_playerbutton2, *_playerbutton3;
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
	CREATE_FUNC(PrepareScene1);
};
#endif
