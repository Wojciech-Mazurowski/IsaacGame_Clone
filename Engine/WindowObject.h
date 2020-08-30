#pragma once
#include "Universals.h"
class WindowObject
{
private:
	std::vector<sf::Vector2f> corners;
	std::string cardinalDirection{"0000"}; //NSWE ex. 1000 for north, 1010 for north-west
public:
	WindowObject(sf::Vector2f c1, sf::Vector2f c2);
	~WindowObject();

	void setCardinalDirection(std::string s);

	std::string getCardinalDirection();
	std::vector<sf::Vector2f> getCorners();
	bool canBeShoneThroughtFromDirection(std::string lightDirection);
};

