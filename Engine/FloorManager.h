#pragma once
#include "FloorHole.h"
#include "Obsticle.h"

class FloorManager: public sf::Drawable{
private:
	std::vector<std::vector<bool>> paths;

	std::vector<FloorHole> holes;
	std::vector<Obsticle> obsticles;
	Boards boards; //holds the lenghts on individual boards in each row of the floor
	TileMap floor;
	TileMap floorDetails;
	
public:
	std::vector<std::vector<int>> movementZone;



	void updateMovementZone();


	FloorManager();
	~FloorManager();

	void generatePaths(std::string doors);
	void updatePaths(bool newHolesAdded, bool newObsticlesAdded);


	void prepareMovementZone(const unsigned int & maxHeight, const unsigned int & maxWidt);
	void setGridTile(sf::Vector2i tileIndex, int state);

	void generateFlooring(const unsigned int & maxHeight, const unsigned int & maxWidth);
	void printT(std::vector<std::vector<bool>> v);
	bool noHoleIntersectingWith(sf::Vector2u topRightPoint, const unsigned int & maxHeight, const unsigned int & maxWidth);
	bool isFragmentSuitableForAHole(sf::Vector2u topRightPoint, std::vector<std::vector<bool>> floor, const unsigned int & maxHeight, const unsigned int & maxWidth);
	void generateObsticles(unsigned int numberOfDebris);
	void generateHoles(unsigned int numberOfHoles, const unsigned int& maxHeight, const unsigned int& maxWidth);

	std::vector<FloorHole> getHoles();
	std::vector<std::vector<int>> getMovementZone();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

