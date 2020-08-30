#include "pch.h"
#include "Room.h"
#include <iostream>

using String = std::string;
using Boards = std::vector<std::vector<int>>;

#define row x
#define column y

//constructors
Room::Room(){}
Room::Room(std::string d):doors(d){ this->isEmpty = false;}

//static variables
std::string Room::allDoors[14]{ "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1111" }; //all possible door configurations excluding 0000

Room::Room(const Room & room)
{
	this->yetEntered = room.yetEntered;
	this->hasBeenCleared = room.hasBeenCleared;
	this->previousDoors = room.previousDoors;
	this->coordinate = room.coordinate;
	this->isEmpty = room.isEmpty;
	this->doors = room.doors;
	this->levelNumber = room.levelNumber;
}

//getters
std::vector<std::shared_ptr<Chest>> Room::getChests() { return this->chests; }
int Room::getRoomType() { return -1; }
bool Room::getIsEmpty() { return isEmpty; }
std::string Room::getDoors() { return doors; }
sf::Vector2i Room::getCoordinates() { return this->coordinate; }
int Room::getPreviousDoors() { return previousDoors; }
int Room::howManyDoors() { int c = 0; for (auto e : doors) { if (e != '0') { c++; /*HIHI*/ } } return c; }
Doors Room::getDoor(){return this->door;}
bool Room::getHasBeenEnteredAlready() { return yetEntered;}
bool Room::getHasBeenCleared() { return hasBeenCleared; }

//setters
void Room::setIsEmpty(bool s) { isEmpty = s; }
void Room::setDoors(std::string d) { this->doors = d; }
void Room::setCoordinates(sf::Vector2i c) { coordinate = c; }
void Room::setCoordinates(int x, int y) { coordinate = sf::Vector2i(x, y); }
void Room::setPreviousDoors(int c) { this->previousDoors = c; }

//helpers
bool Room::hasNorthDoor() { if (doors.at(0) != '0') { return true; }return false; }
bool Room::hasSouthDoor() { if (doors.at(1) != '0') { return true; }return false; }
bool Room::hasWestDoor() { if (doors.at(2) != '0') { return true; }return false; }
bool Room::hasEastDoor() { if (doors.at(3) != '0') { return true; }return false; }


//generators
void Room::setRandomDoors(){ doors = allDoors[Universals::getRandom(0, 13)]; }
void Room::setRandomDoors(int i)
{
	while (true) {
		std::string temp = allDoors[Universals::getRandom(0, 13)];
		if (temp.at(i) == '1') { doors = temp; break; }
	}
}
void Room::setRandomDoors(int i, std::vector<int> no)
{
	while (true) {
		std::string temp = allDoors[Universals::getRandom(0, 13)];
		if (temp.at(i) == '1')
		{
			for (auto e : no) {
				if (e != i) { temp.at(e) = '0'; }
			}
			this->doors = temp;
			break;
		}
	}
}


void Room::allowPlayerToMoveThroughDoors(){
	if (doors.at(0) != '0') { floor.movementZone[0][(roomFloorWidth/2)+1] = 1; }
	if (doors.at(1) != '0') { floor.movementZone[roomFloorHeight+1][(roomFloorWidth / 2) + 1] = 1; }
	if (doors.at(2) != '0') { floor.movementZone[(roomFloorHeight/2)+1][0] = 1; }
	if (doors.at(3) != '0') { floor.movementZone[(roomFloorHeight / 2) + 1][roomFloorWidth+1] = 1; }
}

void Room::generateFlooring() {
	floor.generateFlooring(roomFloorHeight*2,roomFloorWidth*2);
}

void Room::generateDoors() {
	std::string key;

	if (doors.at(0) != '0'){	
		if (doors.at(0) == '1') { key = "door";  Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setNorth(); door.push_back(temp);}
		if (doors.at(0) == '2') { key = "doorItem"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setNorth(); door.push_back(temp);}
		if (doors.at(0) == '3') { key = "doorBoss"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setNorth(); door.push_back(temp);}
	}

	if (doors.at(1) != '0') {
		if (doors.at(1) == '1') { key = "door";  Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setSouth(); door.push_back(temp);}
		if (doors.at(1) == '2') { key = "doorItem"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setSouth(); door.push_back(temp);}
		if (doors.at(1) == '3') { key = "doorBoss"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setSouth(); door.push_back(temp);}
	}
	if (doors.at(2) != '0'){
		if (doors.at(2) == '1') { key = "door";  Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setWest(); door.push_back(temp);}
		if (doors.at(2) == '2') { key = "doorItem"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setWest(); door.push_back(temp);}
		if (doors.at(2) == '3') { key = "doorBoss"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setWest(); door.push_back(temp);}
	}
	if (doors.at(3) != '0'){
		if (doors.at(3) == '1') { key = "door";  Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setEast();	door.push_back(temp);}
		if (doors.at(3) == '2') { key = "doorItem"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setEast();	door.push_back(temp);}
		if (doors.at(3) == '3') { key = "doorBoss"; Door temp(Universals::TextureManager::getTexture(key.append(std::to_string(levelNumber)))); temp.setEast();	door.push_back(temp);}
	}
}
void Room::generateInsides(){}

void Room::prepareWalls() {
	std::string temp = "walls";
	walls.setTexture(*Universals::TextureManager::getTexture(temp.append(std::to_string(levelNumber))));
	walls.move(Universals::WindowManager::getOffsetValue(), 0);
}

void Room::updateFloorMovement(std::vector<std::vector<int>> v)
{
	for (int i = 1; i < floor.movementZone.size() - 1; i++) {
		for(int j = 1; j < floor.movementZone[i].size() - 1; j++) {
			floor.movementZone[i][j] = v[i - 1][j - 1];
		}
	}
}

void Room::updateFloorMovement(){ floor.updateMovementZone();}

void Room::clear()
{
	setHasBeenCleared(true);
	hasJustBeenCleared = true;
	killAllMonsters();
}

void Room::killAllMonsters() {
	this->monsters.clear();
}

bool Room::checkIfWasCleaned() {
	if (monsters.size() == 0) { return true;}
	return false;
}

bool Room::getHasJustBeenCleared() {
	bool temp = hasJustBeenCleared;
	if (temp) { this->hasJustBeenCleared = false; }
	return temp;
}

void Room::setHasJustBeenCleared(bool b) {
	this->hasJustBeenCleared = b;
}

void Room::setHasBeenCleared(bool b) {
	if (!hasBeenCleared && b) {
		for (unsigned int i = 0; i < door.size(); i++) { door[i].open(); }
		hasJustBeenCleared = true;
		allowPlayerToMoveThroughDoors();
	}
	hasBeenCleared = b;
}

void Room::prepareMoveZones()
{
	//the movezones are padded with one extra layer (in comparison to the room floor) so that movemnt through doors can be allowed
	floor.movementZone.resize(roomFloorHeight + 2);
	//the entire zone is filled with 1's
	for (int i = 0; i < floor.movementZone.size(); i++) {
		floor.movementZone[i].resize(roomFloorWidth + 2, 0);
	}
	for (int i = 1; i < floor.movementZone.size() - 1; i++) {
		for (int j = 1; j < floor.movementZone[i].size() - 1; j++) {
			floor.movementZone[i][j] = 1;
		}
	}
}

void Room::addPlayer(std::shared_ptr<Player> p) { players.push_back(p);}

void Room::modifyDoors(char changeTo , int position) {
	this->doors.at(position) = changeTo;
}


void Room::update(float deltaTime){}


std::vector<std::shared_ptr<Entity>> Room::getVampires()
{
	std::vector<std::shared_ptr<Entity>> v;
	for (auto monsta : monsters)
	{
		if (monsta->getType() == 2)
			v.push_back(monsta);
	}
	return v;
}
std::vector<std::shared_ptr<Entity>> Room::getRest()
{
	std::vector<std::shared_ptr<Entity>> v;
	for (auto monstar : this->monsters)
	{
	
		if (monstar->getType() == 1|| monstar->getType() == 0|| monstar->getType() == 3|| monstar->getType() == 4)
		{
			
			v.push_back(monstar);
		}
	}
	return v;
}
//draw
void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//draw the floor
	target.draw(floor,states);
	target.draw(walls,states);
	for (unsigned int i = 0; i < door.size(); i++) {target.draw(door[i],states);}
}

void Room::storeItems(std::vector<std::shared_ptr<Item>> items) {
	for (auto it : items) {
		itemsInTheRoom.push_back(it);
	}
}

std::vector<std::shared_ptr<Item>> Room::getItems() {
	std::vector<std::shared_ptr<Item>> itemsTemp=this->itemsInTheRoom;
	this->itemsInTheRoom.clear();
	return itemsTemp;
}

std::vector<std::vector<int>> Room::getMovementZones(){ return floor.getMovementZone();}

