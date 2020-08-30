#pragma once
#include "Item.h"
class UsableItem : public Item
{
private:
	bool hasBeenUsed= false;
 std::vector<float> effectsLast; //in seconds

public:
	UsableItem();
	UsableItem(const sf::Texture * texture, sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects, std::vector<float> timeItLastsInSeconds);

	virtual ~UsableItem();

	virtual void update(float deltaTime);
	virtual bool getType(); //returns the type of the item, 0 for static, 1 for usable

	//getters
	bool getHasBeenUsed();
	float getTimeItLastInSeconds(int index);
};

