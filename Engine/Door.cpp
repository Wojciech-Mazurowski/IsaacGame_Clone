#include "pch.h"
#include "Door.h"
#include <iostream>


Door::Door()
{
}


Door::Door(const Door& other) :
	Object(other.shape.getTexture(), sf::Vector2u(6, 3), 0.1, sf::Vector2f(0, 0), true)
{
	shape.setTexture(*other.shape.getTexture());
	shape.setOrigin(other.shape.getOrigin());
	shape.setRotation(other.shape.getRotation());
	shape.setPosition(other.shape.getPosition());
	state =other.state;
}

Door::Door(const sf::Texture* texture) :
	Object(texture, sf::Vector2u(6,3), 0.1, sf::Vector2f(0,0), true)
{
	shape.setOrigin((texture->getSize().x/6)/2, (texture->getSize().y / 3));
	state = 1;
}

void Door::setState(int s)
{
	this->state = s;
}

void Door::setNorth(){
	shape.setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x,(float) Universals::WindowManager::getWallPosition(0));
	//makes sure the doors arent rendered on non int pixels (causes bugs)
	shape.setPosition((int)shape.getPosition().x, (int)shape.getPosition().y);
}
void Door::setSouth() {
	shape.setRotation(180);
	shape.setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x, (float)Universals::WindowManager::getWallPosition(1));
	//makes sure the doors arent rendered on non int pixels (causes bugs)
	shape.setPosition((int)shape.getPosition().x, (int)shape.getPosition().y);
}
void Door::setWest() {
	shape.setRotation(270); 
	shape.setPosition((float)Universals::WindowManager::getWallPosition(2), Universals::WindowManager::getMiddleOfScreenWithOffset().y);
	shape.setPosition((int)shape.getPosition().x, (int)shape.getPosition().y);
}
void Door::setEast() { 
	shape.setRotation(90);
	shape.setPosition((float)Universals::WindowManager::getWallPosition(3), Universals::WindowManager::getMiddleOfScreenWithOffset().y);
	shape.setPosition((int)shape.getPosition().x, (int)shape.getPosition().y);
}


Door::~Door()
{
}

void Door::update(float deltaTime) {
	animation.update(state, deltaTime);
	//check if the animation finished
		//the doors just closed
	if (animation.getIsFinished() && animation.getReversed() == true) { state = 0; animation.setLoop(false); }
		//the doors just opened
	if (animation.getIsFinished() && animation.getReversed() == false) { state = 1; animation.setLoop(false); }
	shape.setTextureRect(animation.rect); 
}

void Door::open()
{
	animation.setIsFinished(false);
	this->setState(2);
	animation.setLoop(false);
	
	animation.setReversed(false);
}

void Door::close()
{
	animation.setIsFinished(false);
	this->setState(2);
	animation.setLoop(false);
	animation.setReversed(true);
}
