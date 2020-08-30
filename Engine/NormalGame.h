#pragma once
#include "Game.h"

class NormalGame: public Game
{
private:
	int numberOfLevels = 8; //total number of levels in the game
	Levels levels; //vector of all level objects 
	int currentLevelNumber = 0;
	std::shared_ptr<Level> currentLevel;
	std::shared_ptr<Room> currentRoom;
	std::vector<std::shared_ptr<Entity>> followingCreatures;
	std::vector<std::shared_ptr<Entity>> RestCreatures;
	sf::VertexArray box;
	bool wasset=false;
	
public:

	NormalGame();
	~NormalGame();
	MapCollision tileMap;
	virtual void prepare();
	virtual sf::Vector2u update(float deltaTime);
	virtual void devInput();
	void teleportToBossRoom();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void resetState();
	virtual void handleUseOfUsableItems();

	int doorsCheck();
	void incrementLevel();
	void changeRoom(int direction);
};

