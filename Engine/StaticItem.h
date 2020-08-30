#pragma once
#include "Item.h"
class StaticItem :public Item
{
public:
	StaticItem();
	StaticItem(const sf::Texture* texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects);
	StaticItem(const sf::Texture* texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects, bool canBePickedUp);

	~StaticItem();


	virtual void update(float deltaTime);
	virtual bool getType(); //returns the type of the item, 0 for static, 1 for usable
};

