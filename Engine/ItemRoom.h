#pragma once
#include "Room.h"


class ItemRoom :public Room
{
public:
	ItemRoom();
	ItemRoom(Room room);
	ItemRoom(const ItemRoom& room);
	ItemRoom(std::string doors);
	~ItemRoom();



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void generateInsides();
	virtual void update(float deltaTime);
	virtual int  getRoomType();

	static std::string modifyDoors(std::string doors);

	void generateRandomChests();

};

