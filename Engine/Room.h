#pragma once
#include "pch.h"
#include <String>
#include <vector>
#include "Object.h"
#include "Door.h"
#include "TileMap.h"
#include <memory>
#include "LightManager.h"
#include "FloorManager.h"
#include "Player.h"
#include "Chest.h"
#include "EnemyWorm.h"
#include "EnemyGhost.h"
#include "poteznyBoss.h"



using String = std::string;
using Boards = std::vector<std::vector<int>>;
using Doors = std::vector<Door>;
//using Windows = std::vector<Window>;

class Room : public sf::Drawable{
protected:
	std::vector<std::shared_ptr<Entity>> monsters;
	static std::string allDoors[14];
	unsigned int roomFloorHeight=7;
	unsigned int roomFloorWidth=13;
	std::vector<std::shared_ptr<Player>> players; //hold pointers to all the players currently in the room


	bool yetEntered = false;
	bool hasBeenCleared = false;
	bool isEmpty = true;
	bool hasJustBeenCleared = false;

	int previousDoors = -1;
	sf::Vector2i coordinate; //rooms coordinate in the level matrix
	std::string doors{ "0000" }; //string giving doors or lack thereof in order NSWE (0 for no doors, 1 for normal, 2 for item doors, 3 for boss doors)
	int levelNumber = 1;

	//graphics
	FloorManager floor;
	Doors door;  
	//Windows windows;
	sf::Sprite walls;
	std::vector<std::shared_ptr<Chest>> chests; //all the chests in the room
	std::vector<std::shared_ptr<Item>> itemsInTheRoom;
public:

	Room();
	Room(std::string d); //set with doors
	Room(const Room& room);

	std::vector<std::shared_ptr<Entity>> getRest();
	std::vector < std::shared_ptr<Entity>> getVampires();
	//virtual methods
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void generateInsides();
	virtual void update(float deltaTime);
	virtual int getRoomType();
	virtual void clear();



	//getters
	bool getIsEmpty();
	std::string getDoors();
	int getPreviousDoors();
	int howManyDoors();
	Doors getDoor();
	bool getHasBeenEnteredAlready();
	bool getHasBeenCleared();
	std::vector<std::shared_ptr<Chest>> getChests();
	std::vector<std::shared_ptr<Item>> getItems();
	std::vector<std::vector<int>> getMovementZones();


	//setters
	void setIsEmpty(bool s);
	void setDoors(std::string d);
	void setCoordinates(sf::Vector2i c);
	void setCoordinates(int x, int y);
	void setPreviousDoors(int c);
	sf::Vector2i getCoordinates();
	void prepareMoveZones();
	void addPlayer(std::shared_ptr<Player> p);
	void storeItems(std::vector<std::shared_ptr<Item>> items);

	void modifyDoors(char changeTo, int position);
	//helpers
	void killAllMonsters();

	bool checkIfWasCleaned();

	bool getHasJustBeenCleared();

	void setHasJustBeenCleared(bool b);

	bool hasNorthDoor();
	bool hasSouthDoor();
	bool hasWestDoor();
	bool hasEastDoor();

	void setRandomDoors();
	void setRandomDoors(int i);
	void setRandomDoors(int i, std::vector<int> no);
	void setHasBeenCleared(bool b);

	void allowPlayerToMoveThroughDoors();

	void generateDoors();
	void generateFlooring();
	void prepareWalls();
	void updateFloorMovement(std::vector<std::vector<int>> v);
	void updateFloorMovement();

};
