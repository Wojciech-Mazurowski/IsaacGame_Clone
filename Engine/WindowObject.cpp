#include "pch.h"
#include "WindowObject.h"


WindowObject::WindowObject(sf::Vector2f c1, sf::Vector2f c2)
{
	corners.push_back(c1); corners.push_back(c2);
}

WindowObject::~WindowObject()
{
}

void WindowObject::setCardinalDirection(std::string s)
{
	this->cardinalDirection = s;
}

std::string WindowObject::getCardinalDirection()
{
	return cardinalDirection;
}

std::vector<sf::Vector2f> WindowObject::getCorners(){ return corners; }

bool WindowObject::canBeShoneThroughtFromDirection(std::string lightDirection)
{
	for (int i = 0; i < cardinalDirection.size(); i++) {
		if (cardinalDirection.at(i) == '1' && cardinalDirection.at(i) == lightDirection.at(i)) { return true; }
	}
	return false;
}


