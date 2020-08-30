#include "pch.h"
#include "Obsticle.h"


Obsticle::Obsticle()
{
}
Obsticle::Obsticle(const sf::Texture* texture, bool canBeBroken,sf::Vector2u position):
	Object(texture, sf::Vector2u(6, 2), 0.1, sf::Vector2f(0, 0), true)
{
	this->canBeBroken = canBeBroken;
	state = 0;
	this->gridPosition = position; //as position on the room grid
	setShapePosition();
	animation.setFrame(0);
	animation.update(state, 100);
	shape.setTextureRect(animation.rect);
}

void Obsticle::setShapePosition() {
	int northWall=Universals::WindowManager::getWallPosition(0);
	int westWall= Universals::WindowManager::getWallPosition(2);
	setPosition(sf::Vector2f{ (float) westWall + (gridPosition.y * 90),(float) northWall + (gridPosition.x * 90)});
}

sf::Vector2u Obsticle::getGridPostion(){ return this->gridPosition;}



Obsticle::~Obsticle()
{
}
