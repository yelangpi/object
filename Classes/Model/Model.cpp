#include"Model.h"

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

void Model::attacked(float delta) {
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
