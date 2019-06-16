#include "PrepareScene2.h"
#include"GameScene2.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include"client.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * PrepareScene2::createScene()
{
	auto scene = Scene::create();
	auto layer = PrepareScene2::create();
	scene->addChild(layer);
	return scene;
}


bool PrepareScene2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	boost::asio::io_context* io_context = new boost::asio::io_context();
	tcp::resolver* resolver = new tcp::resolver(*io_context);
	std::string ip = "127.0.0.1";
	std::string port = "8964";
	tcp::resolver::results_type* endpoints = new tcp::resolver::results_type();
	*endpoints = resolver->resolve(ip, port);
	auto c = chat_client::Create(*io_context, *endpoints);
	this->client = c;

	boost::thread t(boost::bind(&boost::asio::io_context::run, io_context));
	t.detach();

	auto background = Sprite::create("PrepareScene1/background.png");
	Vec2 v1 = Director::getInstance()->getWinSize();
	Vec2 v4 = background->getContentSize();
	background->setScale(v1.x / v4.x);
	background->setPosition(v1.x / 2, v1.y / 2);
	this->addChild(background, 0);
	//
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadEffect("DaJi/chuchangmusic.mp3");
	audioengine->preloadEffect("HouYi/chuchangmusic.mp3");
	audioengine->preloadEffect("YaSe/chuchangmusic.mp3");
	//
	auto BackItem = MenuItemImage::create(
		"button/button9.png",
		"button/button10.png",
		CC_CALLBACK_1(PrepareScene2::BackCallback, this));
	Vec2 v2 = BackItem->getContentSize();
	BackItem->setPosition(v2.x / 2 * 0.5, v1.y - v2.y / 2 * 0.5);
	BackItem->getSelectedImage()->setScale(0.7);
	BackItem->setScale(0.5);
	//妲己人物选择,
	auto PlayerItem1 = MenuItemImage::create(
		"DaJi/touxiang.png",
		"DaJi/touxiang.png",
		CC_CALLBACK_1(PrepareScene2::playerCallback1, this));
	PlayerItem1->setScale(2.0);
	PlayerItem1->setPosition(v1.x / 3, 3 * v1.y / 4);
	_playerbutton1 = PlayerItem1;
	//后羿人物选择
	auto PlayerItem2 = MenuItemImage::create(
		"HouYi/touxiang.png",
		"HouYi/touxiang.png",
		CC_CALLBACK_1(PrepareScene2::playerCallback2, this));
	PlayerItem2->setPosition(v1.x / 3, 2 * v1.y / 4);
	PlayerItem2->setScale(2.0);
	_playerbutton2 = PlayerItem2;
	//亚瑟选择
	auto PlayerItem3 = MenuItemImage::create(
		"YaSe/touxiang.png",
		"YaSe/touxiang.png",
		CC_CALLBACK_1(PrepareScene2::playerCallback3, this));
	PlayerItem3->setPosition(v1.x / 3, v1.y / 4);
	PlayerItem3->setScale(2.0);
	_playerbutton3 = PlayerItem3;
	//选择之后的图片
	auto PlayerSelected1 = Sprite::create("DaJi/touxiang-xuanzhong.png");
	PlayerSelected1->setScale(2.0);
	PlayerSelected1->setPosition(v1.x / 3, 3 * v1.y / 4);
	PlayerSelected1->setVisible(false);
	this->addChild(PlayerSelected1, 1);
	_playerselected1 = PlayerSelected1;
	//选择之后的图片的变化
	auto PlayerSelected2 = Sprite::create("HouYi/touxiang-xuanzhong.png");
	PlayerSelected2->setScale(2.0);
	PlayerSelected2->setPosition(v1.x / 3, 2 * v1.y / 4);
	PlayerSelected2->setVisible(false);
	this->addChild(PlayerSelected2, 1);
	_playerselected2 = PlayerSelected2;
	//
	auto PlayerSelected3 = Sprite::create("YaSe/touxiang-xuanzhong.png");
	PlayerSelected3->setScale(2.0);
	PlayerSelected3->setPosition(v1.x / 3, v1.y / 4);
	PlayerSelected3->setVisible(false);
	this->addChild(PlayerSelected3, 1);
	_playerselected3 = PlayerSelected3;
	//敌方选择人物 妲己
	auto ComputerItem1 = MenuItemImage::create(
		"DaJi/touxiang.png",
		"DaJi/touxiang.png",
		CC_CALLBACK_1(PrepareScene2::computerCallback1, this));
	ComputerItem1->setPosition(2 * v1.x / 3, 3 * v1.y / 4);
	ComputerItem1->setScale(2.0);
	_computerbutton1 = ComputerItem1;
	//
	auto ComputerItem2 = MenuItemImage::create(
		"HouYi/touxiang.png",
		"HouYi/touxiang.png",
		CC_CALLBACK_1(PrepareScene2::computerCallback2, this));
	ComputerItem2->setPosition(2 * v1.x / 3, 2 * v1.y / 4);
	ComputerItem2->setScale(2.0);
	_computerbutton2 = ComputerItem2;
	//
	auto ComputerItem3 = MenuItemImage::create(
		"YaSe/touxiang.png",
		"YaSe/touxiang.png",
		CC_CALLBACK_1(PrepareScene2::computerCallback3, this));
	ComputerItem3->setPosition(2 * v1.x / 3, v1.y / 4);
	ComputerItem3->setScale(2.0);
	_computerbutton3 = ComputerItem3;
	//变化
	auto ComputerSelected1 = Sprite::create("DaJi/touxiang-xuanzhong.png");
	ComputerSelected1->setScale(2.0);
	ComputerSelected1->setPosition(2 * v1.x / 3, 3 * v1.y / 4);
	ComputerSelected1->setVisible(false);
	this->addChild(ComputerSelected1, 1);
	_computerselected1 = ComputerSelected1;
	//
	auto ComputerSelected2 = Sprite::create("HouYi/touxiang-xuanzhong.png");
	ComputerSelected2->setScale(2.0);
	ComputerSelected2->setPosition(2 * v1.x / 3, 2 * v1.y / 4);
	ComputerSelected2->setVisible(false);
	this->addChild(ComputerSelected2, 1);
	_computerselected2 = ComputerSelected2;
	//
	auto ComputerSelected3 = Sprite::create("YaSe/touxiang-xuanzhong.png");
	ComputerSelected3->setScale(2.0);
	ComputerSelected3->setPosition(2 * v1.x / 3, v1.y / 4);
	ComputerSelected3->setVisible(false);
	this->addChild(ComputerSelected3, 1);
	_computerselected3 = ComputerSelected3;
	//开始游戏的选项
	auto StartItem = MenuItemImage::create(
		"button/button1.png",
		"button/button2.png",
		CC_CALLBACK_1(PrepareScene2::StartGameCallback, this));
	StartItem->setPosition(v1.x / 2, v1.y / 8);
	StartItem->getSelectedImage()->setScale(0.7);
	StartItem->setEnabled(false);
	_startbutton = StartItem;
	//
	auto menu = Menu::create(BackItem, PlayerItem1, PlayerItem2, PlayerItem3, ComputerItem1, ComputerItem2, ComputerItem3, StartItem, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
	scheduleUpdate();
	//
	return true;
}



void PrepareScene2::BackCallback(Ref * Psender)
{
	Director::getInstance()->popScene();
}

//触发按键会设置自己的阵营，然后再向服务器发包和接包
//在所有属性都选好的情况下，进入下一个场景，并且把在这个里面创建的client和在这个程序里你自己的阵营FLAG也传入下一个场景

//进行修改 所有的点击之后 只进行输入处理，然后在update里不断的读取客户端发来的消息，如果读完了，就进入下一个场景
void PrepareScene2::playerCallback1(Ref * Psender)
{
	FLAG = 'B';
	//向服务器发包表示自己的阵营,还有选择的人物
	char line[10] = { "BBBBBBBDJ" };
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//再接受服务器所分发的信息
	/*client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();*/
		/*if (tmpStr[0]== 'r')
			isConnect = true;
		if (tmpStr[8] == 'J') {
			_computernumber = 1;
		}
		else if (tmpStr[8] == 'E') {
			_computernumber = 3;
		}
		else if (tmpStr[8] == 'Y') {
			_computernumber = 2;
		}*/
		/*if (tmpStr == std::string("rrrrrrrDJ")) {
			isConnect = true;
			_computernumber = 1;
		}
		if (tmpStr == std::string("rrrrrrrHY")) {
			isConnect = true;
			_computernumber = 2;
		}
		if (tmpStr == std::string("rrrrrrrYS")) {
			isConnect = true;
			_computernumber = 3;
		}
	}
	client->t_lock.unlock();*/

	_playerbutton1->setVisible(false);
	_playerselected1->setVisible(true);
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("DaJi/chuchangmusic.mp3");
	if (_playernumber == 1)
	{
		_playerbutton1->setVisible(true);
		_playerselected1->setVisible(false);
	}
	else if (_playernumber == 2)
	{
		_playerbutton2->setVisible(true);
		_playerselected2->setVisible(false);
	}
	else if (_playernumber == 3)
	{
		_playerbutton3->setVisible(true);
		_playerselected3->setVisible(false);
	}
	_playernumber = 1;

}
void PrepareScene2::playerCallback2(Ref * Psender)
{
	FLAG = 'B';
	char line[10] = { "BBBBBBBHY" };
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//再接受服务器所分发的信息

	/*client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();
		if (tmpStr == std::string("rrrrrrrDJ")) {
			isConnect = true;
			_computernumber = 1;
		}
		if (tmpStr == std::string("rrrrrrrHY")) {
			isConnect = true;
			_computernumber = 2;
		}
		if (tmpStr == std::string("rrrrrrrYS")) {
			isConnect = true;
			_computernumber = 3;
		}
	}
	client->t_lock.unlock();*/
	_playerbutton2->setVisible(false);
	_playerselected2->setVisible(true);
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("HouYi/chuchangmusic.mp3");
	if (_playernumber == 1)
	{
		_playerbutton1->setVisible(true);
		_playerselected1->setVisible(false);
	}
	else if (_playernumber == 2)
	{
		_playerbutton2->setVisible(true);
		_playerselected2->setVisible(false);
	}
	else if (_playernumber == 3)
	{
		_playerbutton3->setVisible(true);
		_playerselected3->setVisible(false);
	}
	_playernumber = 2;

}
void PrepareScene2::playerCallback3(Ref * Psender)
{
	FLAG = 'B';
	char line[10] = { "BBBBBBBYS" };
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//再接受服务器所分发的信息

	/*client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();
		if (tmpStr == std::string("rrrrrrrDJ")) {
			isConnect = true;
			_computernumber = 1;
		}
		if (tmpStr == std::string("rrrrrrrHY")) {
			isConnect = true;
			_computernumber = 2;
		}
		if (tmpStr == std::string("rrrrrrrYS")) {
			isConnect = true;
			_computernumber = 3;
		}
	}
	client->t_lock.unlock();*/

	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("YaSe/chuchangmusic.mp3");
	_playerbutton3->setVisible(false);
	_playerselected3->setVisible(true);
	if (_playernumber == 1)
	{
		_playerbutton1->setVisible(true);
		_playerselected1->setVisible(false);
	}
	else if (_playernumber == 2)
	{
		_playerbutton2->setVisible(true);
		_playerselected2->setVisible(false);
	}
	else if (_playernumber == 3)
	{
		_playerbutton3->setVisible(true);
		_playerselected3->setVisible(false);
	}
	_playernumber = 3;

}

void PrepareScene2::computerCallback1(Ref * Psender)
{
	FLAG = 'R';
	char line[10] = { "rrrrrrrDJ" };
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//再接受服务器所分发的信息

	/*client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();
		if (tmpStr == std::string("bbbbbbbDJ")) {
			isConnect = true;
			_playernumber = 1;
		}
		else if (tmpStr == std::string("bbbbbbbHY")) {
			isConnect = true;
			_playernumber = 2;
		}
		else if (tmpStr == std::string("bbbbbbbYS")){
			isConnect = true;
			_playernumber = 3;
		}
	}
	client->t_lock.unlock();*/
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("DaJi/chuchangmusic.mp3");
	_computerbutton1->setVisible(false);
	_computerselected1->setVisible(true);
	if (_computernumber == 1)
	{
		_computerbutton1->setVisible(true);
		_computerselected1->setVisible(false);
	}
	else if (_computernumber == 2)
	{
		_computerbutton2->setVisible(true);
		_computerselected2->setVisible(false);
	}
	else if (_computernumber == 3)
	{
		_computerbutton3->setVisible(true);
		_computerselected3->setVisible(false);
	}
	_computernumber = 1;

}
void PrepareScene2::computerCallback2(Ref * Psender)
{
	FLAG = 'R';
	char line[10] = { "rrrrrrrHY" };
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//再接受服务器所分发的信息

	/*client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();
		if (tmpStr == std::string("bbbbbbbDJ")) {
			isConnect = true;
			_playernumber = 1;
		}
		else if (tmpStr == std::string("bbbbbbbHY")) {
			isConnect = true;
			_playernumber = 2;
		}
		else if (tmpStr == std::string("bbbbbbbYS")) {
			isConnect = true;
			_playernumber = 3;
		}
	}
	client->t_lock.unlock();*/
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("HouYi/chuchangmusic.mp3");
	_computerbutton2->setVisible(false);
	_computerselected2->setVisible(true);
	if (_computernumber == 1)
	{
		_computerbutton1->setVisible(true);
		_computerselected1->setVisible(false);
	}
	else if (_computernumber == 2)
	{
		_computerbutton2->setVisible(true);
		_computerselected2->setVisible(false);
	}
	else if (_computernumber == 3)
	{
		_computerbutton3->setVisible(true);
		_computerselected3->setVisible(false);
	}
	_computernumber = 2;

}
void PrepareScene2::computerCallback3(Ref * Psender)
{
	FLAG = 'R';
	char line[10] = { "rrrrrrrYS" };
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//再接受服务器所分发的信息

	/*client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		client->read_msg_list_.pop_front();
		if (tmpStr == std::string("bbbbbbbDJ")) {
			isConnect = true;
			_playernumber = 1;
		}
		else if (tmpStr == std::string("bbbbbbbHY")) {
			isConnect = true;
			_playernumber = 2;
		}
		else if (tmpStr == std::string("bbbbbbbYS")) {
			isConnect = true;
			_playernumber = 3;
		}
	}
	client->t_lock.unlock();*/
	auto audioengine = SimpleAudioEngine::getInstance();
	audioengine->playEffect("YaSe/chuchangmusic.mp3");
	_computerbutton3->setVisible(false);
	_computerselected3->setVisible(true);
	if (_computernumber == 1)
	{
		_computerbutton1->setVisible(true);
		_computerselected1->setVisible(false);
	}
	else if (_computernumber == 2)
	{
		_computerbutton2->setVisible(true);
		_computerselected2->setVisible(false);
	}
	else if (_computernumber == 3)
	{
		_computerbutton3->setVisible(true);
		_computerselected3->setVisible(false);
	}
	_computernumber = 3;

}
void PrepareScene2::StartGameCallback(Ref * Psender)
{
	std::string name[3] = { "DaJi","HouYi","YaSe" };
	Director::getInstance()->replaceScene(TransitionFade::create(3, GameScene2::createScene(name[_playernumber - 1], name[_computernumber - 1], this->client, this->FLAG)));
}

PrepareScene2 * PrepareScene2::create()
{
	PrepareScene2 *pRet = new(std::nothrow) PrepareScene2();
	if (pRet && pRet->init())
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

void PrepareScene2::update(float a)
{
	//同时不停广播自己所携带的信息
	//即自己的FLAG类型 还有人物信息
	char line[10] = { "rrrrrrrrr" };
	if (FLAG == 'R') {
		if (_computernumber == 1) {
			line[7] = 'D';
			line[8] = 'J';
		}
		else if (_computernumber == 2) {
			line[7] = 'H';
			line[8] = 'Y';
		}
		else if (_computernumber == 3) {
			line[7] = 'Y';
			line[8] = 'S';
		}
	}
	else if (FLAG == 'B') {
		line[0] = 'B';
		line[1] = 'B';
		line[2] = 'B';
		line[3] = 'B';
		line[4] = 'B';
		line[5] = 'B';
		line[6] = 'B';
		if (_playernumber == 1) {
			line[7] = 'D';
			line[8] = 'J';
		}
		else if (_playernumber == 2) {
			line[7] = 'H';
			line[8] = 'Y';
		}
		else if (_playernumber == 3) {
			line[7] = 'Y';
			line[8] = 'S';
		}
	}
	chat_message msg;
	msg.body_length(std::strlen(line));
	memcpy(msg.body(), line, msg.body_length());
	msg.encode_header();
	client->write(msg);
	//
	client->t_lock.lock();
	while (client->read_msg_list_.size()) {
		std::string tmpStr = client->read_msg_list_.front()->body();
		tmpStr.resize(client->read_msg_list_.front()->body_length());
		CCLOG(tmpStr.c_str());
		client->read_msg_list_.pop_front();
		if (FLAG == 'R') {
			if (tmpStr == std::string("BBBBBBBDJ")) {
				isConnect = true;
				_playernumber = 1;
			}
			else if (tmpStr == std::string("BBBBBBBHY")) {
				isConnect = true;
				_playernumber = 2;
			}
			else if (tmpStr == std::string("BBBBBBBYS")) {
				isConnect = true;
				_playernumber = 3;
			}
		}
		if (FLAG == 'B') {
			if (tmpStr == std::string("rrrrrrrDJ")) {
				isConnect = true;
				_computernumber = 1;
			}
			else if (tmpStr == std::string("rrrrrrrHY")) {
				isConnect = true;
				_computernumber = 2;
			}
			else if (tmpStr == std::string("rrrrrrrYS")) {
				isConnect = true;
				_computernumber = 3;
			}
		}
		if ((_playernumber&&_computernumber) && isConnect) {
			_startbutton->setEnabled(true);
		}
	}
	client->t_lock.unlock();


}
