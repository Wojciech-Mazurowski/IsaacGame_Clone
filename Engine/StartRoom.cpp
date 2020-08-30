#include "pch.h"
#include "StartRoom.h"


StartRoom::StartRoom(): Room()
{
	this->hasBeenCleared = true;
}

StartRoom::StartRoom(std::string doors) : Room(doors)
{
}


StartRoom::~StartRoom()
{
}

void StartRoom::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(floor);
	target.draw(walls);
	for (unsigned int i = 0; i < door.size(); i++) { target.draw(door[i]); }
}

void StartRoom::generateInsides()
{
	generateFlooring();
	generateDoors();
	prepareWalls();
	allowPlayerToMoveThroughDoors();
}

void StartRoom::update(float deltaTime)
{
	for (unsigned int i = 0; i < door.size(); i++) { door[i].update(deltaTime); }
}

int StartRoom::getRoomType()
{
	return 1;
}
