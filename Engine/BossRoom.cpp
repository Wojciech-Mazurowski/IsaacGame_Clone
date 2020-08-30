#include "pch.h"
#include "BossRoom.h"


BossRoom::BossRoom():Room()
{
}

BossRoom::BossRoom(std::string doors):Room(doors)
{
}
BossRoom::BossRoom(const BossRoom& room) : Room() {
	this->yetEntered = room.yetEntered;
	this->hasBeenCleared = room.hasBeenCleared;
	this->previousDoors = room.previousDoors;
	this->coordinate = room.coordinate;
	this->isEmpty = room.isEmpty;
	this->doors = room.doors;
	this->levelNumber = room.levelNumber;
}

BossRoom::BossRoom(Room room):Room(room){}

BossRoom::~BossRoom()
{
}

void BossRoom::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(floor);
	target.draw(walls);
	for (unsigned int i = 0; i < door.size(); i++) { target.draw(door[i]); }
	for (auto m : monsters){m->render(target);}
}

void BossRoom::generateInsides()
{
	hasBeenCleared = false;
	prepareWalls();
	generateDoors();
	generateFlooring();
	setRandomBoss();
}

void BossRoom::update(float deltaTime)
{
	if (yetEntered == false) {
		for (unsigned int i = 0; i < door.size(); i++) { door[i].close(); }
		yetEntered = true;
	}
	//boss.update();
	for (unsigned int i = 0; i < door.size(); i++) { door[i].update(deltaTime); }
	if (checkIfWasCleaned()) { setHasBeenCleared(true); allowPlayerToMoveThroughDoors(); }

	for (int i = 0; i < monsters.size(); i++) {
		monsters[i]->update(deltaTime);
		if (!monsters[i]->isStillAlive()) { monsters.erase(monsters.begin() + i); break; };
	}
}

int BossRoom::getRoomType()
{
	return 2;
}

std::string BossRoom::modifyDoors(std::string doors) {
	std::string temp{ "0000" };
	for (int i = 0; i < temp.size(); i++) {
		if (doors.at(i) != '0') { temp.at(i) = '3'; break; } //as the item room always ony has one door
	}
	return temp;
}


void BossRoom::setRandomBoss()
{
	int random=Universals::getRandom(0, 1);
	if (random>-1) {
		monsters.push_back(std::make_shared<poteznyBoss>(Universals::WindowManager::getMiddleOfScreenWithOffset().x, Universals::WindowManager::getMiddleOfScreenWithOffset().y, Universals::TextureManager::getTexture("grubus")));
	}
}
