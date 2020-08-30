#pragma once
#include "Object.h"
#include "TileMap.h"

class FloorHole: public Object
{
private:
	sf::Vector2u topRightposition;
	TileMap texture;
	std::vector<std::vector<bool>> holeZones;
public:
	FloorHole();
	~FloorHole();
	FloorHole(std::vector<std::vector<bool>> floorFragment, sf::Vector2u topRightPoint, const unsigned int & maxHeight, const unsigned int & maxWidth);

	void generateHole(std::vector<std::vector<bool>> floorFragment, const unsigned int & maxHeight, const unsigned int & maxWidth);
	void generateTexture(const unsigned int & maxHeight, const unsigned int & maxWidth);


	sf::Vector2u getTopRightPosition();
	int getMaxWidth();
	int getMaxHeight();
	std::vector<std::vector<bool>> getHoleZones();

	virtual void update(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

