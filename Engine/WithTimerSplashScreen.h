#pragma once
#include "SplashScreen.h"
class WithTimerSplashScreen: public SplashScreen
{
private:
	float fullSecondFlag = 0;
	sf::Text subText;
	sf::Time timeToCountDownFrom;
	sf::Text timeRemainingText;
	bool timeHasPassed = false;
public:
	WithTimerSplashScreen(std::string mainText, sf::Vector2f position, std::string subtext, unsigned int timeToCountDown, unsigned int underLyingStates);
	WithTimerSplashScreen();
	~WithTimerSplashScreen();


	virtual void update(float deltaTime);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	bool getTimeHasPassed();

};

