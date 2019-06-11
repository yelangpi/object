#include"Level.h"
#include<fstream>
#include<sstream>
LevelControl::LevelControl(std::string name) {
	std::ifstream in(name + "_exp.txt");
	std::string line;
	for (int i = 0; i < 15; ++i) {
		std::getline(in, line);
		LevelData info;
		std::istringstream record(line);
		record >> info._hp;
		record >> info._mp;
		record >> info._magicAttack;
		record >> info._physicsAttack;
		record >> info._magicDefence;
		record >> info._physicsDefence;
		record >> info._movingRate;
		record >> info._attackRadius;
		_data.push_back(info);
	}
}

LevelData* LevelControl::getData(unsigned level) {
	return &_data.at(level - 1);
}