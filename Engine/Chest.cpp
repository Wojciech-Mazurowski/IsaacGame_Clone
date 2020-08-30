#include "pch.h"
#include "Chest.h"



Chest::Chest(const sf::Texture* texture, const sf::Vector2f& position):
	Object(texture, sf::Vector2u(6,3), 0.1, position, false)
{
	shape.setOrigin((texture->getSize().x / 6) / 2, (texture->getSize().y / 3)/2);
	shape.setPosition(position);
	state = 0; //closed state
	animate = false;
	animation.setFrame(0);
}

Chest::Chest()
{
}


Chest::~Chest()
{
}

void Chest::update(float deltaTime) {
	if (animate) {
		animation.update(state, deltaTime);
		//check if the animation finished
		if (animation.getIsFinished() && animation.getReversed() == true) { state = 0; animation.setLoop(false); animate = false; } 	//the chest just closed
		if (animation.getIsFinished() && animation.getReversed() == false) { state = 1; animation.setLoop(false); animate = false;  if (!isDoneOpening) { isDoneOpening = !isDoneOpening; } }		//the chest just opened
	}
	shape.setTextureRect(animation.rect);
}

void Chest::setIsDoneOpening(bool b){ this->isDoneOpening = b;}

void Chest::open()
{
	this->animate = true;
	this->isOpen = true;
	animation.setIsFinished(false);
	this->state=2;
	animation.setLoop(false);
	animation.setReversed(false);
}

void Chest::close()
{
	this->animate = true;
	this->isOpen = false;
	animation.setIsFinished(false);
	this->state = 2;
	animation.setLoop(false);
	animation.setReversed(true);
}

void Chest::addItem(std::shared_ptr<Item> item){ 
	item->setPosition(getPosition());
	item->setIsOnTheMap(false);  
	item->setCanBePickedUp(false);
	itemsInTheChest.push_back(item); 
}

std::vector<std::shared_ptr<Item>> Chest::getItems(){ 
	for (auto it : itemsInTheChest) { it->setIsOnTheMap(true);}
	return this->itemsInTheChest;
}

bool Chest::getIsOpen(){ return this->isOpen;}
bool Chest::getIsDoneOpening() { return this->isDoneOpening; }
void Chest::clear() { this->itemsInTheChest.clear(); }
bool Chest::isEmpty(){
	if (itemsInTheChest.size() == 0) { return true; }
	return false;
}