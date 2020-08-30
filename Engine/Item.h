#pragma once
#include "Object.h"

class Item : //abstract class
	public Object
{
protected:
	bool canBePickedUp = false;
	bool isOnTheMap = false;


	sf::Time pickUpTimer = sf::seconds(100); //takes care of the time the item cannot be picked up for
	bool measureTime = false;

	std::string name;
	std::vector<std::string> effects; //for example "increaseSpeed" for items that increase speed 
	std::vector<float> powerOfEffects; //the power of each efect in the appropriate index
	std::shared_ptr<MovementComponent> movementComponent;

	Item();
	Item(const sf::Texture* texture,sf::Vector2f position, std::string name, std::vector<std::string> effects, std::vector<float> powerOfEffects);

public:

	~Item();
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//getters
	virtual bool getType(); //returns the type of the item, 0 for static, 1 for usable
	std::vector <std::string> getEffects();
	std::vector<float> getPowerOfEffects();
	bool getIsOnTheMap() const;
	bool getCanBePickedUp();
	std::string getName();

	//setters
	void setCanBePickedUp(bool b);
	void setIsOnTheMap(bool b);
	void lungeForward();
	

	void canBePickedUpIn(float seconds);
	void checkIfBecamePickupable();

};

