#pragma once
#include "Universals.h"
class Effect
{
protected:
	bool isOn = false;
	float value=0.0; //for example how much time should be dialated or the screen darkened
	sf::Time timeLeft= sf::seconds(0.0);

public:
	Effect();
	Effect(float value, float timeItLasts);
	~Effect();

	virtual void update(float deltaTime);
	bool getIsOn();
	float getValue();
};

