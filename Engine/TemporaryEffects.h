#pragma once
#include "Effect.h"
class TemporaryEffects
{
private:
	std::vector<Effect> timeDialations; 
	std::vector<Effect> darkenings;
public:
	TemporaryEffects();
	~TemporaryEffects();

	void update(float deltaTime);


	void dialateTimeByPercentage(float timeDialation,float duration);
	void darkenTheScreen(float percentOfDarkness,float duration);

	float getTimeDialation();
	float getScreenDarkening();
};

