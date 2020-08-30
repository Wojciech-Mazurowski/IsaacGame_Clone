#include "pch.h"
#include "TemporaryEffects.h"
#include <iostream>


TemporaryEffects::TemporaryEffects()
{
}


TemporaryEffects::~TemporaryEffects()
{
}

void TemporaryEffects::update(float deltaTime)
{
	for (auto t = timeDialations.begin(); t < timeDialations.end();t++) {
		if(t->getIsOn()) t->update(deltaTime);
		else { timeDialations.erase(t); break; }
	}

	for (auto d = darkenings.begin(); d < darkenings.end(); d++) {
		if (d->getIsOn()) d->update(deltaTime);
		else { darkenings.erase(d); break; }
	}

}

void TemporaryEffects::dialateTimeByPercentage(float timeDialation, float duration)
{
	timeDialations.push_back(Effect(timeDialation, duration));
}

void TemporaryEffects::darkenTheScreen(float percentOfDarkness, float duration)
{
	darkenings.push_back(Effect(percentOfDarkness, duration));
}

float TemporaryEffects::getTimeDialation()
{
	float result=1.0;
	for (auto t : timeDialations) {
	if(t.getIsOn()) result *= t.getValue();
	}
	return result;
}

float TemporaryEffects::getScreenDarkening()
{
	float result=0.0;
	for (auto d : darkenings) {
		if (d.getIsOn()) result += d.getValue();
	}
	return result;
}
