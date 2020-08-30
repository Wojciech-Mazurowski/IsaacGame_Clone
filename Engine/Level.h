#pragma once
#include "pch.h"
#include <vector>
#include <stack>
#include "Universals.h"
#include "StartRoom.h"
#include "BossRoom.h"
#include "ItemRoom.h"
#include "NormalRoom.h"
#include <string>



class Room;
using Rooms = std::vector<std::vector<std::shared_ptr<Room>>>;

class Level {
private:
	int height = 10; //number of rows
	int width = 10; //numer of columns
	float difficulty = 0;
	Rooms arragement;
	sf::Vector2i current;
	sf::Vector2i begining { -1,-1 };
	sf::Vector2i boss;
	int numberOfRooms = 0;
	int maxRooms = 96;
	int minRooms = 10;

public:

	//constructors
	Level();
	Level(int h, int w);
	Level(float diificulty);
	Level(int max);
	Level(int h, int w, float diificulty);
	Level(int h, int w, float diificulty, int max);

	//getters 
	std::shared_ptr<Room> getBossRoom();
	Rooms getArragement();
	int getHeight();
	int getWidth();
	float getDifficulty();
	sf::Vector2i getBegining();
	sf::Vector2i getBoss();
	int calculateNumberOfRooms();
	int getNumberOfRooms();
	int getMaxRooms();
	int getMinRooms();
	std::shared_ptr<Room> getCurrent();
	sf::Vector2i getCurrentC();
	std::vector<std::vector<std::string>> getDoorStrings();
	std::vector<std::vector<std::string>> getVisitedRoomsDoorStrings();
	std::vector<std::vector<int>> getRoomTypes();


	//setters
	void setHeight(int h);
	void setWidth(int w);
	void setDifficulty(float d);
	void setArragement(Rooms r);
	void setBegining(sf::Vector2i  b);
	void setMaxRooms(int m);
	void setMinRooms(int m);

	//helper methods
	void printStack(std::stack<Room> i);
	void printLevel();
	void clear();

	//player changing rooms
	void goNorth();
	void goSouth();
	void goWest();
	void goEast();


	//generating the level
	void emptyLevel(Rooms& a);
	void generateInsides();
	sf::Vector2i findFirstRoom();
	std::vector<int> cannotBeLinked(Room r);
	void modifyDoorsInRoomLeadingTo(int previousDoors, char roomtype, sf::Vector2u roomCoordinates);
	//to avoid doors going to rooms that are already there but dont have door available
	void setSpecialRooms();
	void generateLevel();
};
