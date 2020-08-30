#pragma once
#include "Room.h"
class StartRoom: public Room
{
public:
	StartRoom();
	StartRoom(std::string doors);
	~StartRoom();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void generateInsides();
	virtual void update(float deltaTime);
	virtual int  getRoomType();
};

