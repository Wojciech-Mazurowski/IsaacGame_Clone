#include "pch.h"
#include "Item.h"


Item::Item()
{
}

Item::Item(const sf::Texture * texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects):
	Object(texture, sf::Vector2u(6,1),0.2,position,true)
{
	this->shape.setOrigin((texture->getSize().x / 6) / 2, (texture->getSize().y / 1) / 2);
	this->setPosition(position);
	this->name = name;
	this->effects = effects;
	this->powerOfEffects = powerOfEffects;
	this->movementComponent = std::make_shared<MovementComponent>(this->shape, 250.f, 2000.f, 500.f);
}


Item::~Item()
{
}

void Item::update(float deltaTime){}

void Item::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (isOnTheMap) {
		target.draw(this->shape, states);
	}
}

bool Item::getType() { return 1; };
std::vector<std::string> Item::getEffects(){ return effects;}
std::vector<float> Item::getPowerOfEffects(){ return powerOfEffects;}
bool Item::getIsOnTheMap() const {return this->isOnTheMap;}
bool Item::getCanBePickedUp() {return this->canBePickedUp; }
std::string Item::getName(){ return this->name;}

void Item::setCanBePickedUp(bool b){ this->canBePickedUp = b;}
void Item::setIsOnTheMap(bool b){ this->isOnTheMap = b;}

void Item::lungeForward(){ 
	float randomHorizontalVelocity = (float)Universals::getRandom(-350, 350);
	float randomVerticalVelocity= (float)Universals::getRandom(200, 500);
	this->movementComponent->setVelocity(sf::Vector2f{ randomHorizontalVelocity,randomVerticalVelocity});

}

void Item::canBePickedUpIn(float seconds)
{
	pickUpTimer = sf::seconds(seconds);
	measureTime = true;
}

void Item::checkIfBecamePickupable()
{
	if (this->pickUpTimer.asMilliseconds() <= 0) { canBePickedUp = true;}
}

