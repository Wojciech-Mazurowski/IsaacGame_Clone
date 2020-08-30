#include "pch.h"
#include "Map.h"


Map::Map(){}

Map::Map(std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes, int width, int height, sf::Vector2i currentRoomCoordinates, sf::Vector2u tileSize, sf::Vector2f position):
	doorStrings(doorStrings), roomTypes(roomTypes),width(width),height(height),currentRoomCoordinates(currentRoomCoordinates),tileSize(tileSize)
{
	visitedRooms.resize(width);
	for (int i = 0; i < width; i++) { visitedRooms[i].resize(height); }
	visitedRooms[currentRoomCoordinates.x][currentRoomCoordinates.y] = true;
	miniMap.load(Universals::PathManager::getDefaultPath().append("Graphics\\HUD\\miniMapTiles.png"), tileSize, doorStrings, roomTypes, width, height, currentRoomCoordinates,visitedRooms);
	miniMap.setOrigin((tileSize.x*width) / 2, (tileSize.y*height) / 2);
	miniMap.setPosition(position);
}

void Map::clearVisitedRoomsArray() {
	for (int i = 0; i < visitedRooms.size(); i++) {
		for (int j = 0; j < visitedRooms[i].size(); j++) {
			visitedRooms[i][j] = false;
		}
	}
}

void Map::nextLevel(sf::Vector2i addNewRoomToMap, std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes) {
	clearVisitedRoomsArray();
	currentRoomCoordinates = addNewRoomToMap;
	visitedRooms[addNewRoomToMap.x][addNewRoomToMap.y] = true;
	this->doorStrings = doorStrings;
	this->roomTypes = roomTypes;
	miniMap.load(Universals::PathManager::getDefaultPath().append("Graphics\\HUD\\miniMapTiles.png"), tileSize, doorStrings, roomTypes, width, height, currentRoomCoordinates, visitedRooms);
}

void Map::update(sf::Vector2i addNewRoomToMap) {
	currentRoomCoordinates = addNewRoomToMap;
	visitedRooms[addNewRoomToMap.x][addNewRoomToMap.y] = true;
	miniMap.load(Universals::PathManager::getDefaultPath().append("Graphics\\HUD\\miniMapTiles.png"), tileSize, doorStrings, roomTypes, width, height, currentRoomCoordinates,visitedRooms);
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(miniMap, states);
}

Map::~Map()
{
}

sf::Vector2f Map::getPostion()
{
	return miniMap.getPosition();
}
