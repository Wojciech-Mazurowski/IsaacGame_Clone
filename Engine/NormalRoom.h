#pragma once
#include "Room.h"
#include <iostream>
class NormalRoom : public Room
{
private:
	
	sf::Sprite overLay;
	std::vector<std::vector<Object>> obsticles;

public:

	

	NormalRoom();
	NormalRoom(std::string doors);
	NormalRoom(const NormalRoom& normalRoom);
	NormalRoom(Room room);
	~NormalRoom();
	std::shared_ptr<Entity> getRandomMonster();
	void generateMonster(int howmany);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void printPaths(const std::vector<std::vector<bool>>& p);
	void generateObsticles();
	virtual void generateInsides();
	virtual void update(float deltaTime);
	virtual int  getRoomType();

};

