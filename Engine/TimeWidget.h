#pragma once
#include "Universals.h"


class TimeWidget: public sf::Drawable
{
private:
	float fullSecondFlag = 0;
	sf::Time maxTime= sf::seconds(600);
	sf::Time currentTime = sf::seconds(0);
	sf::Text timeDisplayText;

public:
	TimeWidget();
	TimeWidget(sf::Time MaxTime,sf::Vector2f position);
	~TimeWidget();

	std::string convertTimeForDisplay();
	bool isTimeOver();
	void update(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

