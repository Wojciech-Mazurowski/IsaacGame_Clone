#include "pch.h"
#include "LightManager.h"
#include <iostream>


LightManager::LightManager(){}


LightManager::LightManager(float y1, float y2, float x1, float x2)
{
	addWalls(y1, y2, x1, x2);
}

LightManager::~LightManager()
{
}

void LightManager::addLightSource(LightSource& l)
{
	calculateCardinalDirection(l);
	calculateDrawRegions(l);
	lightSources.push_back(l);
}

void LightManager::addWindow(WindowObject& w)
{
	WindowObject wi = w;
	calculateCardinalDirection(wi);
	windows.push_back(wi);
}

void LightManager::addWalls(float y1, float y2, float x1, float x2)
{
	walls.push_back(y1);
	walls.push_back(y2);
	walls.push_back(x1);
	walls.push_back(x2);
	calculateWallCorners();
}

void LightManager::calculateWallCorners()
{
	//topLeft corner
	sf::Vector2f topLeftCorner{ (float)walls[2],(float)walls[0] };
	wallCorners.push_back(topLeftCorner);
	sf::Vector2f topRightCorner{ (float)walls[3],(float)walls[0] };
	wallCorners.push_back(topRightCorner);
	sf::Vector2f bottomRightCorner{ (float)walls[3],(float)walls[1]};
	wallCorners.push_back(bottomRightCorner);
	sf::Vector2f bottomLeftCorner{ (float)walls[2],(float)walls[1] };
	wallCorners.push_back(bottomLeftCorner);

}

void LightManager::calculateCardinalDirection(LightSource& l)
{
	std::string temp{"0000"};
	if (l.getPosition().y<walls[0]) { temp.at(0) = '1'; }
	if (l.getPosition().y>walls[1]) { temp.at(1) = '1'; }
	if (l.getPosition().x<walls[2]) { temp.at(2) = '1'; }
	if (l.getPosition().x > walls[3]) { temp.at(3) = '1'; }
	l.setCardinalDireciton(temp);
}

void LightManager::calculateCardinalDirection(WindowObject& w)
{
	std::string temp{"0000" };
	if (w.getCorners()[0].y<=walls[0]) { temp.at(0) = '1'; }
	if (w.getCorners()[0].y>=walls[1]) { temp.at(1) = '1'; }
	if (w.getCorners()[0].x<=walls[2]) { temp.at(2) = '1'; }
	if (w.getCorners()[0].x>=walls[3]) { temp.at(3) = '1'; }
	w.setCardinalDirection(temp);
}

int LightManager::getWhichWalltoSkip(std::string cardinalDirection)
{
	if (cardinalDirection.at(0) == '1') { return 0; }
	if (cardinalDirection.at(1) == '1') { return 1; }
	if (cardinalDirection.at(2) == '1') { return 2; }
	if (cardinalDirection.at(3) == '1') { return 3; }
	return -1;
}



void LightManager::calculateDrawRegions(LightSource& light)
{
	light.clearDrawAreas();
	for (int i = 0; i < windows.size(); i++) {
		WindowObject currentWindow = windows[i];
		//if the light shines through that window, calculate the draw coordinates
		if (currentWindow.canBeShoneThroughtFromDirection(light.getCardinalDirection()))
		{
			std::vector<sf::Vector2f> endPoints;
			sf::Vector2f result;
			int skipWall = getWhichWalltoSkip(currentWindow.getCardinalDirection());
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < walls.size(); j++)
				{
					//to skip the wall that the window is on
					if (j!= skipWall)
					{
						//for vertical walls
						if (j < 2) {
							result = calculatePointOfIntersection(light.getPosition(), currentWindow.getCorners()[i], sf::Vector2f(0, walls[j]), sf::Vector2f(100, walls[j]));
						}
						//for horizontal walls
						if (j >= 2) {
							result = calculatePointOfIntersection(light.getPosition(), currentWindow.getCorners()[i], sf::Vector2f(walls[j], 0), sf::Vector2f(walls[j], 100));
						}
						//std::cout << "\nRESULT:" << result.x << "," << result.y;
						if (result.x!= -1 && isOnTheHouseWalls(result)) { break; }	
					}
				}
				endPoints.push_back(result);
			}
			//first two coordinates are the window corners
			if(areOnDifferentWalls(endPoints))
			{
			
				if (areOnOpposingWalls(endPoints, skipWall)) 
				{
					sf::Vector2f corner1;
					sf::Vector2f corner2;
					if (skipWall == 0) {corner1 = wallCorners[3]; corner2 = wallCorners[2];}
					if (skipWall == 1) { corner1 = wallCorners[0]; corner2 = wallCorners[1]; }
					if (skipWall == 2) { corner1 = wallCorners[2]; corner2 = wallCorners[1]; }
					if (skipWall == 3) { corner1 = wallCorners[0]; corner2 = wallCorners[3]; }
					light.addDrawArea(currentWindow.getCorners()[0], currentWindow.getCorners()[1], endPoints[1], corner2,corner1, endPoints[0]);
				}
				else
				{
					sf::Vector2f corner = getCornerBetween(endPoints);
					light.addDrawArea(currentWindow.getCorners()[0], currentWindow.getCorners()[1], endPoints[1], corner, endPoints[0]);
				}
			
			}
			else{ light.addDrawArea(currentWindow.getCorners()[0], currentWindow.getCorners()[1], endPoints[1], endPoints[0]); }
		}
	}
}

void LightManager::move(int indexInArray, sf::Vector2f moveVector)
{
	if (indexInArray < lightSources.size()) {
		lightSources[indexInArray].setPosition(sf::Vector2f(lightSources[indexInArray].getPosition().x + moveVector.x, lightSources[indexInArray].getPosition().y + moveVector.y));
		calculateCardinalDirection(lightSources[indexInArray]);
		calculateDrawRegions(lightSources[indexInArray]);
	}
}

sf::Vector2f LightManager::getCornerBetween(std::vector<sf::Vector2f> points)
{
	for (int i = 0; i < wallCorners.size(); i++)
	{
		sf::Vector2f currentCorner = wallCorners[i];
		if (currentCorner.x == points[0].x &&currentCorner.y == points[1].y) { return currentCorner; }
		if (currentCorner.x == points[1].x &&currentCorner.y == points[0].y) { return currentCorner; }
	}
	//if all fails 
	return points[0];
}

bool LightManager::isOnTheHouseWalls(const sf::Vector2f& point)
{
	if (point.y >= walls[0] && point.y<=walls[1] && point.x>=walls[2] && point.x <= walls[3]) return true;
	return false;
}

bool LightManager::areOnDifferentWalls(const std::vector<sf::Vector2f>& points)
{
	if (points[0].x != points[1].x && points[0].y != points[1].y) return true;
	return false;
}
bool LightManager::areOnOpposingWalls(const std::vector<sf::Vector2f>& points, int skipWall)
{
	int wallPair = 0;
	//if skipWall ewuals 0 or 1 that means the pair is eastWest
	if (skipWall == 0 || skipWall == 1) { wallPair = 2; }
	//there are only two possible oposing wall pairs NS and WE
	if (isOnWall(points[0], wallPair) && isOnWall(points[1], wallPair + 1) || isOnWall(points[1], wallPair) && isOnWall(points[0], wallPair + 1)){ return true; }
	return false;
}

bool LightManager::isOnWall(sf::Vector2f point, int wallIndex) {
	if (wallIndex < 2) 
	{
		if (point.y == walls[wallIndex]) { return true; }
	}
	else
	{
		if (point.x == walls[wallIndex]) { return true; }
	}
	return false;
}

//ADAPTED FROM https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
sf::Vector2f LightManager::calculatePointOfIntersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D)
{
		// Line AB represented as a1x + b1y = c1 
		double a1 = B.y - A.y;
		double b1 = A.x - B.x;
		double c1 = a1 * (A.x) + b1 * (A.y);

		// Line CD represented as a2x + b2y = c2 
		double a2 = D.y - C.y;
		double b2 = C.x - D.x;
		double c2 = a2 * (C.x) + b2 * (C.y);

		double determinant = a1 * b2 - a2 * b1;

		// The lines are parallel. 
		if (determinant == 0)
		{
			return sf::Vector2f(-1, -1);
		}
		else
		{
			double x = (b2*c1 - b1 * c2) / determinant;
			double y = (a1*c2 - a2 * c1) / determinant;
			return sf::Vector2f(x, y);
		}
	}
void LightManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{


	for (int i = 0; i < lightSources.size(); i++) {
		target.draw(lightSources[i]);
	}
}

