#include "pch.h"
#include "WithTimerSplashScreen.h"



WithTimerSplashScreen::WithTimerSplashScreen(std::string mainText, sf::Vector2f position,std::string subtext, unsigned int timeToCountDown, unsigned int underLyingStates) : SplashScreen(mainText, underLyingState)
{
	float xPosition = this->mainText.getPosition().x;
	subText.setFont(*Universals::FontManager::getFont("retro"));
	subText.setString(subtext);
	subText.setCharacterSize(20);
	subText.setFillColor(sf::Color(255, 255, 255, 220));
	this->subText.setOrigin((this->subText.getCharacterSize()*subText.getString().getSize()) / 2, this->subText.getCharacterSize() / 2);
	subText.setPosition(Universals::WindowManager::getMiddleOfScreen().x, this->mainText.getPosition().y + subText.getCharacterSize() * 2);
	timeToCountDownFrom = sf::seconds(timeToCountDown);


	timeRemainingText.setFont(*Universals::FontManager::getFont("retro"));
	timeRemainingText.setString(std::to_string(timeToCountDownFrom.asSeconds()));
	timeRemainingText.setCharacterSize(50);
	timeRemainingText.setFillColor(sf::Color(255, 255, 255, 76));
	this->timeRemainingText.setOrigin((this->subText.getCharacterSize()*subText.getString().getSize()) / 2, this->subText.getCharacterSize() / 2);
	timeRemainingText.setPosition(position);
}


WithTimerSplashScreen::WithTimerSplashScreen()
{
}


WithTimerSplashScreen::~WithTimerSplashScreen()
{
}

void WithTimerSplashScreen::update(float deltaTime)
{
	fullSecondFlag += deltaTime;
	timeToCountDownFrom -= sf::seconds(deltaTime);
	if (fullSecondFlag >= 1.0) { fullSecondFlag = 0; timeRemainingText.setString(std::to_string((int)timeToCountDownFrom.asSeconds())); }
	if (timeToCountDownFrom.asSeconds() == 0.0) { this->timeHasPassed = true; }
}

void WithTimerSplashScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroud);
	target.draw(timeRemainingText);
	target.draw(mainText);
	target.draw(subText);
}

bool WithTimerSplashScreen::getTimeHasPassed(){ return this->timeHasPassed;}
