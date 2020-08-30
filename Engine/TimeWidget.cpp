#include "pch.h"
#include "TimeWidget.h"
#include <iostream>


TimeWidget::TimeWidget()
{
	
}


TimeWidget::TimeWidget(sf::Time MaxTime,sf::Vector2f position)
{
	maxTime = MaxTime;
	fullSecondFlag = 0;
	currentTime = sf::seconds(0);

	timeDisplayText.setFont(*Universals::FontManager::getFont("retro"));
	timeDisplayText.setFillColor(sf::Color(255, 255, 255, 120));
	timeDisplayText.setOrigin((timeDisplayText.getCharacterSize() * 8) / 2, timeDisplayText.getCharacterSize() / 2);
	timeDisplayText.setPosition(position);
	timeDisplayText.setString(convertTimeForDisplay());
}

TimeWidget::~TimeWidget()
{
}

std::string TimeWidget::convertTimeForDisplay()
{
	int timeToDisplay = (int) maxTime.asSeconds() - (int) currentTime.asSeconds();
	if (timeToDisplay<21) { timeDisplayText.setFillColor(sf::Color(255, 100+7.75*timeToDisplay, 100+7.75*timeToDisplay, 120)); }

	if (timeToDisplay > 0) {
		int hours = timeToDisplay / 3600;
		int minutes = (timeToDisplay % 3600) / 60;
		int seconds = timeToDisplay % 60;
		std::string hoursString = std::to_string(hours); if (hours < 10) { hoursString.insert(0, "0"); }
		std::string minutesString = std::to_string(minutes); if (minutes < 10) { minutesString.insert(0, "0"); }
		std::string secondsString = std::to_string(seconds); if (seconds < 10) { secondsString.insert(0, "0"); }
		std::string result = hoursString;
		result.append(":").append(minutesString).append(":").append(secondsString);
		return result;
	}
	return "00:00:00";
}

bool TimeWidget::isTimeOver()
{
	if(currentTime >= maxTime){ return true; }
	return false;
}

void TimeWidget::update(float deltaTime)
{
	fullSecondFlag += deltaTime;
	currentTime += sf::seconds(deltaTime);
	if (fullSecondFlag >= 1.0) { fullSecondFlag = 0; timeDisplayText.setString(convertTimeForDisplay());}

}


void TimeWidget::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(timeDisplayText, states);
}


