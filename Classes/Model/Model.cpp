#include"Model.h"
USING_NS_CC;
Model::Model() {

}

Model::~Model() {

}

bool Model::init() {
	return false;
}

const std::string & Model::getName()
{
	return _name;
}

void Model::setName(const std::string _string)
{
	_name = _string;
}

bool Model::isDie() {
	return this->getCurrentHp() <= 0;
}

void Model::attacked(float delta) 
{
	this->setCurrentHp(this->getCurrentHp() - delta);
}

void Model::setDirction_image()
{
	std::string dir[8] = { "Up","Down","Left","Right","Left-Up","Left-Down","Right-Up","Right-Down" };
	for (int i = 0; i < 8; i++)
	{
		dirction_image[dir[i]] = cocos2d::StringUtils::format("%s/%s/Walk/%s/0000.PNG", this->getName().c_str(), this->getName().c_str(), dir[i].c_str());
	}
}
void Model::doHP()
{
	if (!initHP)
	{
		cocos2d::Sprite*HPbox = cocos2d::Sprite::create("xuetiao/xuetiao2.png");
		cocos2d::Sprite*HPrectangle = cocos2d::Sprite::create("xuetiao/xuetiao1.png");
		_HPbox = HPbox;
		_HPrectangle = HPrectangle;
		initHP = true;
		this->getParent()->addChild(HPbox, 10);
		this->getParent()->addChild(HPrectangle, 10);
		_HPrectangle->setAnchorPoint(Vec2(0, 0));
	}
	Vec2 v1 = this->getPosition();
	Vec2 v2 = this->getContentSize();
	Vec2 v = Vec2(v1.x, v1.y + v2.y / 2 + 20);
	Vec2 v3 = _HPrectangle->getContentSize();
	_HPbox->setPosition(v);
	_HPrectangle->setPosition(v - 0.5*v3);
	_HPrectangle->setScaleX(this->getCurrentHp() / this->getHp());
	if (this->getCurrentHp() < 0)this->setCurrentHp(0);
}