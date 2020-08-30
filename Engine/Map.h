#pragma once
#include "TileMap.h"
class Map : public sf::Drawable
{
private:
	TileMap miniMap;
	std::vector<std::vector<std::string>> doorStrings;
	std::vector<std::vector<int>> roomTypes;
	int width; int height;
	sf::Vector2i currentRoomCoordinates;
	sf::Vector2u tileSize;
	std::vector<std::vector<bool>> visitedRooms;

public:
	Map();
	Map(std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes, int width, int height, sf::Vector2i currentRoomCoordinates, sf::Vector2u tileSize,sf::Vector2f position);
	~Map();
	void clearVisitedRoomsArray();
	void nextLevel(sf::Vector2i addNewRoomToMap, std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes);
	

	sf::Vector2f getPostion();
	void update(sf::Vector2i addNewRoomToMap);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

