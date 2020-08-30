#pragma once
#include "Universals.h"
class LightSource: public sf::Drawable
{
private:
	sf::Vector2f position;
	float intensity;
	sf::Color color;
	std::vector<sf::ConvexShape> drawAreas;
	std::string cardinalDirection {0000}; //NSWE ex. 1000 for north, 1010 for north-west

public:
	LightSource();
	LightSource(sf::Vector2f position, float intensity,float r,float g,float b);
	LightSource(sf::Vector2f position, float intensity, sf::Color color);
	~LightSource();

	void setPosition(sf::Vector2f p);
	void setIntensity(float i);
	void setColor(sf::Color c);
	void setCardinalDireciton(std::string direction);

	sf::Vector2f getPosition();
	float getIntenisty();
	sf::Color getColor();
	std::string getCardinalDirection();
	
	void addDrawArea(sf::Vector2f x, sf::Vector2f  y, sf::Vector2f z, sf::Vector2f k);
	void addDrawArea(sf::Vector2f x, sf::Vector2f y, sf::Vector2f z, sf::Vector2f k, sf::Vector2f g);
	void addDrawArea(sf::Vector2f x, sf::Vector2f y, sf::Vector2f z, sf::Vector2f k, sf::Vector2f g, sf::Vector2f h);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void clearDrawAreas();

};

