#pragma once
#include "Object.h"
#include "Universals.h"

//states: 0- closed/ 1-open/2-opening/closing

class Door :public Object
{
public:
	Door();
	Door(const Door & other);
	Door(const sf::Texture* texture);
	
	~Door();
	virtual void update(float deltaTime);

	void setState(int s);
	void setNorth();
	void setSouth();
	void setWest();
	void setEast();
	void open();
	void close();
};

