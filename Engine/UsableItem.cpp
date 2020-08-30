#include "pch.h"
#include "UsableItem.h"


UsableItem::UsableItem()
{
}

UsableItem::UsableItem(const sf::Texture * texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects, std::vector<float> timeItLastsInSeconds):
	Item(texture,position,name,effects,powerOfEffects)
{
	this->effectsLast = timeItLastsInSeconds;
}





UsableItem::~UsableItem()
{
}

void UsableItem::update(float deltaTime)
{
	if (isOnTheMap){
		if (measureTime) pickUpTimer -= sf::seconds(deltaTime);
		checkIfBecamePickupable();

		animation.update(state, deltaTime);
		shape.setTextureRect(animation.rect);
		movementComponent->update(deltaTime);
	}

}


bool UsableItem::getType(){ return 1;}
bool UsableItem::getHasBeenUsed(){ return this->hasBeenUsed;}
float UsableItem::getTimeItLastInSeconds(int index){ return effectsLast[index];}
