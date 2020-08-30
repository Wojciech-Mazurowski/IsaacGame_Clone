#include "pch.h"
#include "Effect.h"


Effect::Effect()
{
}

Effect::Effect(float value, float timeItLastsInSeconds)
{
	this->value = value;
	this->timeLeft= sf::seconds(timeItLastsInSeconds);
	isOn = true;
}


Effect::~Effect()
{
}

void Effect::update(float deltaTime)
{
	if(isOn) timeLeft -= sf::seconds(deltaTime);
	if (timeLeft.asMilliseconds() <= 0) isOn = false;
}



bool Effect::getIsOn() { return this->isOn;}
float Effect::getValue() { return this->value; }
