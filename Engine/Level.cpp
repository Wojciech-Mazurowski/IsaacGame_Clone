#include "pch.h"
#include <stack>
#include <iostream>
#include "Level.h"
#include "Room.h"

#define row x
#define column y

//constructors
Level::Level() {}
Level::Level(int h, int w) { this->height = h; this->width = w; }
Level::Level(float diificulty) { this->difficulty = difficulty; }
Level::Level(int max) { this->maxRooms = max; }
Level::Level(int h, int w, float diificulty) { this->height = h; this->width = w; this->difficulty = difficulty; }
Level::Level(int h, int w, float diificulty, int max) { this->height = h; this->width = w; this->difficulty = difficulty; this->maxRooms = max; }

std::shared_ptr<Room> Level::getBossRoom(){ return arragement[boss.x][boss.y]; }

//getters 
Rooms Level::getArragement() { return arragement; }
int Level::getHeight() { return height; }
int Level::getWidth() { return width; }
float Level::getDifficulty() { return difficulty; }
sf::Vector2i Level::getBegining() { return begining; }
sf::Vector2i Level::getBoss() { return boss; }
int Level::calculateNumberOfRooms(){
		this->numberOfRooms = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (!arragement[i][j]->getIsEmpty()) {
					numberOfRooms++;
				}
			}
		}
		return numberOfRooms;
}
int Level::getNumberOfRooms() { calculateNumberOfRooms();  return this->numberOfRooms; }
int Level::getMaxRooms() { return this->maxRooms; }
std::shared_ptr<Room> Level::getCurrent() { return arragement[current.row][current.column]; }
sf::Vector2i Level::getCurrentC() { return this->current; }
int Level::getMinRooms() { return minRooms; }


//setters
void Level::setHeight(int h) { this->height = h; }
void Level::setWidth(int w) { this->width = w; }
void Level::setDifficulty(float d){ this->difficulty = d;}
void Level::setArragement(Rooms r) { this->arragement = r; }
void Level::setBegining(sf::Vector2i  b) { this->begining = b; }
void Level::setMaxRooms(int m) { this->maxRooms = m; }
void Level::setMinRooms(int m) { this->minRooms = m; }

//helper functions
void Level::printStack(std::stack<Room> i) {
		std::cout << "\n\n";
		while (!i.empty()) {
			std::cout << i.top().getDoors() << "\n";
			i.pop();
		}
		std::cout << "STACK";
	}
void Level::printLevel() {
		std::cout << "\n---THIS BE THE BOARD--\n";
		for (int i = 0; i < arragement.size(); i++) {
			for (int j = 0; j < arragement[i].size(); j++)
			{
			std::string doors = arragement[i][j]->getDoors();
				if (begining.row == i && begining.column == j) { std::cout << "s" << doors << " "; }
				else { std::cout << doors << "  "; }
			}
			std::cout << "\n";
		}
}

void Level::clear()
{
	arragement.clear();
	begining = { -1,-1 };
	boss;
	numberOfRooms = 0;
}
std::vector<std::vector<std::string>> Level::getDoorStrings() {
	std::vector<std::vector<std::string>> a;
	a.resize(this->width);
	for (int i = 0; i < arragement.size(); i++) {
		for (int j = 0; j < arragement[i].size(); j++)
		{
			a[i].push_back(arragement[i][j]->getDoors());
		}
	}
	return a;
}

std::vector<std::vector<std::string>> Level::getVisitedRoomsDoorStrings() {
	std::vector<std::vector<std::string>> a;
	a.resize(this->width);
	for (int i = 0; i < arragement.size(); i++) {
		for (int j = 0; j < arragement[i].size(); j++)
		{
			if (arragement[i][j]->getHasBeenEnteredAlready()) {a[i].push_back(arragement[i][j]->getDoors());}
			else { a[i].push_back("0000"); }
		}
	}
	return a;
}

//Normal, Start, Boss, Item;
std::vector<std::vector<int>> Level::getRoomTypes() {
	std::vector<std::vector<int>> a;
	a.resize(this->width);
	for (int i = 0; i < arragement.size(); i++) {
		for (int j = 0; j < arragement[i].size(); j++)
		{
			a[i].push_back((int) arragement[i][j]->getRoomType());
		}
	}
	return a;
}


//player changing rooms
void Level::goNorth() 
{
		if (getCurrent()->hasNorthDoor() && !arragement[this->current.row - 1][this->current.column]->getIsEmpty() && arragement[this->current.row ][this->current.column]->getHasBeenCleared()) { current.row = current.row - 1; }
}
void Level::goSouth() 
{
		if (getCurrent()->hasSouthDoor() && !arragement[this->current.row + 1][this->current.column]->getIsEmpty() && arragement[this->current.row][this->current.column]->getHasBeenCleared()) { current.row = current.row + 1; }
}
void Level::goWest() 
{
		if (getCurrent()->hasWestDoor() && !arragement[this->current.row][this->current.column - 1]->getIsEmpty() && arragement[this->current.row][this->current.column]->getHasBeenCleared()) { current.column = current.column - 1; }
}
void Level::goEast()
{
		if (getCurrent()->hasEastDoor() && !arragement[this->current.row][this->current.column + 1]->getIsEmpty() && arragement[this->current.row][this->current.column]->getHasBeenCleared()) { current.column = current.column + 1; }
}

//generating the level

void Level::emptyLevel(Rooms& a){
		a.resize(height);
		for (int i = 0; i < height; i++) {
			for (int j = 0;j < width; j++) {
				a[i].push_back(std::make_shared<Room>());
			}
		}
}

sf::Vector2i Level::findFirstRoom()
{
		//chooses the location of the first room somewhere near the middle of the board (if not declared)
		if (begining.x= -1 && begining.y == -1) {
			int roww = Universals::getRandom(height/2, (height/2)+2);
			int columnm = Universals::getRandom(width/2, (width/2)+2);
			begining = sf::Vector2i{ roww,columnm };
		}
		return begining;
}

//to avoid doors going to rooms that are already there but dont have door available
std::vector<int> Level::cannotBeLinked(Room r) 
{
		std::vector<int> temp;
		if (r.getCoordinates().row + 1 < height) {
			Room tempN = *arragement[r.getCoordinates().row + 1][r.getCoordinates().column];
			if (!tempN.getIsEmpty()) {
				if (tempN.getDoors().at(1) != '1') { temp.push_back(0); }
			}
		}
		else { temp.push_back(0); }
		if (r.getCoordinates().row - 1 >= 0) {
			Room tempS = *arragement[r.getCoordinates().row - 1][r.getCoordinates().column];
			if (!tempS.getIsEmpty()) {
				if (tempS.getDoors().at(0) != '1') { temp.push_back(1); }
			}
		}
		else { temp.push_back(1); }

		if (r.getCoordinates().column - 1 >= 0) {
			Room tempW = *arragement[r.getCoordinates().row][r.getCoordinates().column - 1];
			if (!tempW.getIsEmpty()) {
				if (tempW.getDoors().at(3) != '1') { temp.push_back(2); }
			}
		}
		else { temp.push_back(2); }

		if (r.getCoordinates().column + 1 <width) {
			Room tempE = *arragement[r.getCoordinates().row][r.getCoordinates().column + 1];
			if (!tempE.getIsEmpty()) {
				if (tempE.getDoors().at(2) != '1') { temp.push_back(3); }
			}
		}
		else { temp.push_back(3); }

		return temp;
}


void Level::modifyDoorsInRoomLeadingTo(int previousDoors, char roomtype, sf::Vector2u roomCoordinates) {
	if(previousDoors==0) {
		arragement[roomCoordinates.x-1][roomCoordinates.y]->modifyDoors(roomtype,1);
		return;
	}
	if (previousDoors==1) {
		arragement[roomCoordinates.x+1][roomCoordinates.y]->modifyDoors(roomtype, 0);
		return;
	}
	if (previousDoors==2) {
		arragement[roomCoordinates.x][roomCoordinates.y-1]->modifyDoors(roomtype, 3);
		return;
	}
	if (previousDoors==3) {
		arragement[roomCoordinates.x][roomCoordinates.y+1]->modifyDoors(roomtype, 2);
		return;
	}
}

void Level::setSpecialRooms() 
{
		//max distance
		int max = 0;
		Room boss;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Room temp = *arragement[i][j];
				if (!temp.getIsEmpty() && temp.howManyDoors() == 1 && temp.getCoordinates()!=this->begining) {
					int distance = std::abs(temp.getCoordinates().row - begining.row) + std::abs(temp.getCoordinates().column - begining.column);
					//chance of it becoming a tressure room
					if ((float)Universals::getRandom(0, 100)/ 100 > 0.1) {
						std::shared_ptr<ItemRoom> itemRoom= std::make_shared<ItemRoom>(*arragement[i][j]);
						itemRoom->setDoors(ItemRoom::modifyDoors(arragement[i][j]->getDoors()));
						//modify the doors in the room leading to the item room
						modifyDoorsInRoomLeadingTo(itemRoom->getPreviousDoors(), '2', sf::Vector2u{(unsigned)i,(unsigned)j });
						arragement[i][j] = itemRoom;
					}
					if (distance > max) { max = distance; boss = temp; }
				}
			}
		}
		sf::Vector2i k{ boss.getCoordinates().row ,boss.getCoordinates().column };
		this->boss = k;
		std::shared_ptr<BossRoom> bossRoom = std::make_shared<BossRoom>(*arragement[this->boss.row][this->boss.column]);
		bossRoom->setDoors(BossRoom::modifyDoors(arragement[this->boss.row][this->boss.column]->getDoors()));
		arragement[this->boss.row][this->boss.column] = bossRoom;
		modifyDoorsInRoomLeadingTo(bossRoom->getPreviousDoors(), '3', sf::Vector2u{ (unsigned)this->boss.row,(unsigned) this->boss.column});
}


void Level::generateInsides() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (!arragement[i][j]->getIsEmpty()) { arragement[i][j]->prepareMoveZones(); arragement[i][j]->generateInsides(); }
		}
	}
}

void Level::generateLevel()
{
	restart:
		//generates an empty level
		emptyLevel(arragement);
		//finds position for the first room, and creates it
		sf::Vector2i first = findFirstRoom();
		std::shared_ptr<StartRoom> start=std::make_shared<StartRoom>();
		start->setRandomDoors();
		start->setIsEmpty(false);
		start->setCoordinates(first.row,first.column);
		begining = first;
		current = begining;
		arragement[first.x][first.y] = start;
		// a stack that the generated rooms will be saved on
		///printLevel();
		std::stack<Room> doNext;
		doNext.push(*start);
		while (getNumberOfRooms() <= maxRooms && !doNext.empty())
		{
		    ///this->printStack(doNext);
			//takes the room that's on top of the stack
			Room temp = doNext.top();
			doNext.pop();
			std::string doors = temp.getDoors();

			//DOORS is a 4 bit string, first bit corresponding to  North doors, second to South doors, third to West doors and last to East (ex. 1001-has North and East doors)
			if (doors.at(0) == '1' && temp.getPreviousDoors() != 0)
			{
				if (temp.getCoordinates().row - 1 >= 0 && arragement[temp.getCoordinates().row - 1][temp.getCoordinates().column]->getIsEmpty()) {
					std::shared_ptr<NormalRoom> next=std::make_shared<NormalRoom>();
					next->setIsEmpty(false);
					next->setCoordinates(temp.getCoordinates().row - 1, temp.getCoordinates().column);
					std::vector<int> a = cannotBeLinked(*next);
					next->setRandomDoors(1, a);
					next->setPreviousDoors(1);
					arragement[next->getCoordinates().row][next->getCoordinates().column] = next;
					std::cout << arragement[next->getCoordinates().row][next->getCoordinates().column]->getRoomType();
					doNext.push(*next);
				}
				else { doors.at(0) = '0'; arragement[temp.getCoordinates().row][temp.getCoordinates().column]->setDoors(doors); }

			}
			if (doors.at(1) == '1'&& temp.getPreviousDoors() != 1)
			{
				if (temp.getCoordinates().row + 1 < height && arragement[temp.getCoordinates().row + 1][temp.getCoordinates().column]->getIsEmpty()) {
					std::shared_ptr<NormalRoom> next = std::make_shared<NormalRoom>();
					next->setIsEmpty(false);
					next->setCoordinates(temp.getCoordinates().row + 1, temp.getCoordinates().column);
					std::vector<int> a = cannotBeLinked(*next);
					next->setRandomDoors(0, a);
					next->setPreviousDoors(0);
					arragement[next->getCoordinates().row][next->getCoordinates().column] = next;
					doNext.push(*next);
				}
				else { doors.at(1) = '0'; arragement[temp.getCoordinates().row][temp.getCoordinates().column]->setDoors(doors); }

			}
			if (doors.at(2) == '1'&& temp.getPreviousDoors() != 2)
			{
				if (temp.getCoordinates().column - 1 >= 0 && arragement[temp.getCoordinates().row][temp.getCoordinates().column - 1]->getIsEmpty()) {
					std::shared_ptr<NormalRoom> next = std::make_shared<NormalRoom>();
					next->setIsEmpty(false);
					next->setCoordinates(temp.getCoordinates().row, temp.getCoordinates().column - 1);
					std::vector<int> a = cannotBeLinked(*next);
					next->setRandomDoors(3, a);
					next->setPreviousDoors(3);
					arragement[next->getCoordinates().row][next->getCoordinates().column] =next;
					doNext.push(*next);
				}
				else { doors.at(2) = '0'; arragement[temp.getCoordinates().row][temp.getCoordinates().column]->setDoors(doors); }
			}
			if (doors.at(3) == '1' && temp.getPreviousDoors() != 3)
			{
				if (temp.getCoordinates().column + 1 < width && arragement[temp.getCoordinates().row][temp.getCoordinates().column + 1]->getIsEmpty())
				{
					std::shared_ptr<NormalRoom> next = std::make_shared<NormalRoom>();
					next->setIsEmpty(false);
					next->setCoordinates(temp.getCoordinates().row, temp.getCoordinates().column + 1);
					std::vector<int> a = cannotBeLinked(*next);
					next->setRandomDoors(2, a);
					next->setPreviousDoors(2);
					arragement[next->getCoordinates().row][next->getCoordinates().column] = next;
					doNext.push(*next);
				}
				else { doors.at(3) = '0'; arragement[temp.getCoordinates().row][temp.getCoordinates().column]->setDoors(doors); }
			}

		///	std::cout << "\nWywolane dla " << temp.getDoors();
		///	printLevel();
		///	std::cout << "\nILOSC POKOI: " << getNumberOfRooms();
		}

		if (getNumberOfRooms() < minRooms) { this->clear(); goto restart; }
		//fixes all the unconnected rooms at the end (the ones left on the stack)
		while (!doNext.empty()) {
			std::shared_ptr<NormalRoom> temp = std::make_shared<NormalRoom>(doNext.top());
			doNext.pop();
			std::string buffer{ "0000" };
			buffer.at(temp->getPreviousDoors()) = '1';
			temp->setDoors(buffer);
			arragement[temp->getCoordinates().row][temp->getCoordinates().column] = temp; 
		}
		///printLevel();
		//set a room with 1 door to be a boss room (such room must exist)
			//same goes for tressure rooms
		setSpecialRooms();
}


