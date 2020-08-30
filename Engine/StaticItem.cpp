#include "pch.h"
#include "StaticItem.h"


StaticItem::StaticItem()
{
}

StaticItem::StaticItem(const sf::Texture * texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects):
	Item(texture, position, name, effects, powerOfEffects)
{
}

StaticItem::StaticItem(const sf::Texture * texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects, bool canBePickedUp) :
	Item(texture, position, name, effects, powerOfEffects)
{
	this->isOnTheMap = canBePickedUp;
}


StaticItem::~StaticItem()
{
}


void StaticItem::update(float deltaTime)
{
	if (isOnTheMap){
		if (measureTime) pickUpTimer -= sf::seconds(deltaTime);
		checkIfBecamePickupable();
		animation.update(state, deltaTime);
		shape.setTextureRect(animation.rect);
		movementComponent->update(deltaTime);
	}

}

bool StaticItem::getType(){return 0;}
