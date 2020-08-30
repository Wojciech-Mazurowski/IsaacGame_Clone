#include "pch.h"
#include "ItemRoom.h"
#include <iostream>

ItemRoom::ItemRoom():Room()
{
	this->hasBeenCleared = true;
}
ItemRoom::ItemRoom(Room room):Room(room){
	this->hasBeenCleared = true;
}

ItemRoom::ItemRoom(const ItemRoom& room) : Room() {
	this->yetEntered = room.yetEntered;
	this->hasBeenCleared = true;
	this->previousDoors = room.previousDoors;
	this->coordinate = room.coordinate;
	this->isEmpty = room.isEmpty;
	this->doors = modifyDoors(room.doors);
	this->levelNumber = room.levelNumber;
}

std::string ItemRoom::modifyDoors(std:: string doors) {
	std::string temp{ "0000" };
	for (int i = 0; i < temp.size(); i++) {
		if (doors.at(i) != '0') { temp.at(i) = '2'; break; } //as the item room always ony has one door
	}
	return temp;
}

void ItemRoom::generateRandomChests()
{
	int randomChance= Universals::getRandom(0, 100);
	int chestNumber = 1;
	if (randomChance > 80) { chestNumber = 2; }
	if (randomChance > 97) { chestNumber = 3; }

	sf::Vector2f chestPosition{ Universals::WindowManager::getMiddleOfScreenWithOffset() };
	std::string textureKey = "chest";
	textureKey.append(std::to_string(levelNumber));
	floor.movementZone[(roomFloorHeight/2)+1][(roomFloorWidth/2)+1]=0;

	for (int i = 0; i < chestNumber; i++) {
		if (i == 1) { chestPosition = sf::Vector2f{ chestPosition.x-180,chestPosition.y };floor.movementZone[(roomFloorHeight/2)+1][(roomFloorWidth/2)-1]=0; } //if there is to be more chests, then position needs to be changed
		if (i == 2) { chestPosition = sf::Vector2f{ chestPosition.x+180,chestPosition.y }; floor.movementZone[(roomFloorHeight/2)+1][(roomFloorWidth/2)+3]=0;} //if there is to be more chests, then position needs to be changed
	
		chests.push_back(std::make_shared<Chest>(Universals::TextureManager::getTexture(textureKey), chestPosition));
		
	}
}




ItemRoom::ItemRoom(std::string doors): Room(doors)
{
}


ItemRoom::~ItemRoom()
{
}

void ItemRoom::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw the floor
	target.draw(floor);
	target.draw(walls);
	for (unsigned int i = 0; i < door.size(); i++) { target.draw(door[i]); }
	for (unsigned int i = 0; i < chests.size(); i++) { target.draw(*chests[i]); }
}

void ItemRoom::generateInsides()
{
	generateDoors();
	generateFlooring();
	prepareWalls();
	generateRandomChests();
	allowPlayerToMoveThroughDoors();
}

void ItemRoom::update(float deltaTime)
{
	if (!yetEntered) { yetEntered = true; }
	for (unsigned int i = 0; i < door.size(); i++) { door[i].update(deltaTime); }
	for (unsigned int i = 0; i < chests.size(); i++) { chests[i]->update(deltaTime); }
}

int ItemRoom::getRoomType()
{
	return 3;
}
