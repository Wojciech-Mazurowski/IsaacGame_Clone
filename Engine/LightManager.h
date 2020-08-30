#pragma once
#include "LightSource.h"
#include "WindowObject.h"
#include <cmath>

class LightManager: sf::Drawable
{
private:
	std::vector<int> walls; //y1 (the north wall),y2 (the south wall),x1 (the west wall),x2 (the east wall)
	std::vector<sf::Vector2f> wallCorners; //[0]-TopLeft [1]-TopRight [2]-BottomRight [3]-BottomLeft (going clockwise from topLeft)
	std::vector<LightSource> lightSources; //holds all the sources of light 
	std::vector<WindowObject> windows; //holds all the windows

public:
	LightManager();
	LightManager(float y1, float y2, float x1, float x2);
	~LightManager();


	void addLightSource(LightSource& l);
	void addWindow(WindowObject& w);
	void addWalls(float y1, float y2, float x1, float x2);
	void calculateWallCorners();
	
	void calculateCardinalDirection(LightSource& l);
	void calculateCardinalDirection(WindowObject& w);
	
	int getWhichWalltoSkip(std::string cardinalDirection);
	void calculateDrawRegions(LightSource& light);
	void move(int indexInArray,sf::Vector2f moveVector);
	sf::Vector2f getCornerBetween(std::vector<sf::Vector2f> points);

	//helper functions 
	bool isOnTheHouseWalls(const sf::Vector2f& point);
	bool areOnDifferentWalls(const std::vector<sf::Vector2f>& points);
	bool areOnOpposingWalls(const std::vector<sf::Vector2f>& points, int skipWall);
	bool isOnWall(sf::Vector2f point, int wallIndex);
	sf::Vector2f calculatePointOfIntersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

