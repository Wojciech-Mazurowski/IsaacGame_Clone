#include "pch.h"
#include "FloorHole.h"
#include <iostream>


FloorHole::FloorHole()
{
}


FloorHole::~FloorHole()
{
}

FloorHole::FloorHole(std::vector<std::vector<bool>> floorFragment, sf::Vector2u topRightPoint, const unsigned int& maxHeight, const unsigned int& maxWidth)
{
	this->topRightposition=topRightPoint;
	//set position of the tileMap (texture)
	generateHole(floorFragment, maxHeight, maxWidth);
	generateTexture(maxHeight, maxWidth);
}

void FloorHole::generateHole(std::vector<std::vector<bool>> floorFragment, const unsigned int& maxHeight, const unsigned int& maxWidth)
{
	int sum = 0;
	for (int i = 0; i < maxHeight; i++) {
		for (int j = 0; j < maxWidth; j++) {
			if (floorFragment[i][j]) {sum++;}
		}
	}
	int maxAmmount= (maxHeight*maxWidth);
	if(sum>=maxAmmount/15) {
		int toChange = sum - ((maxAmmount-1) /1.5);
		for (int i = 0; i <= toChange; i++) {
			int randomRow = Universals::getRandom(0, maxHeight-1);
			int chooseBeginginOrEnd = Universals::getRandom(0, 1);
			int column=0;

			if (chooseBeginginOrEnd == 0) {
				while (column != maxWidth - 1 && floorFragment[randomRow][column] == 0) { column++; }
			}
			else {
				column = maxWidth - 1;
				while (column != 0 && floorFragment[randomRow][column] == 0) { column--; }
			}

			floorFragment[randomRow][column] = 0;
		}
	}
	this->holeZones = floorFragment;
}

void FloorHole::generateTexture(const unsigned int& maxHeight, const unsigned int& maxWidth)
{
	texture.loadHoles(Universals::PathManager::getCurrentLevelPath().append("floorholes.png"),sf::Vector2u(90,90), maxWidth, maxHeight, holeZones);
	texture.setPosition(sf::Vector2f(Universals::WindowManager::getWallPosition(2) + (this->topRightposition.y * 90), Universals::WindowManager::getWallPosition(0) + (this->topRightposition.x * 90)));
}

sf::Vector2u FloorHole::getTopRightPosition(){ return topRightposition;}

int FloorHole::getMaxWidth(){return holeZones.size();}
int FloorHole::getMaxHeight() { return holeZones[0].size(); }

std::vector<std::vector<bool>> FloorHole::getHoleZones(){return holeZones;}

void FloorHole::update(float deltaTime){}

void FloorHole::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(texture, states);
}
