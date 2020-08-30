#pragma once
#include "Object.h"
class Obsticle : public Object
{
private:
	bool canBeBroken=false;
	float hp=0.0;
	sf::Vector2u gridPosition; //position on the grid
public:
	Obsticle();
	Obsticle(const sf::Texture * texture, bool canBeBroken, sf::Vector2u position);

	~Obsticle();

	void setShapePosition();

	sf::Vector2u getGridPostion();

};

