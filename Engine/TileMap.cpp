#include "pch.h"
#include "TileMap.h"
#include <iostream>

#define row x
#define column y

int TileMap::getTileNumber(std::string d)
{
if (d == "0000") { return 0; }
if (d.at(0) == '0'){
	if (d.at(1) == '0') {
		if (d.at(2) == '0' && d.at(3) != '0') { return 1; }
		if (d.at(2) != '0' && d.at(3) == '0') { return 2; }
		if (d.at(2) != '0' && d.at(3) != '0') { return 3; }
	}
	else {
		if (d.at(2) == '0' && d.at(3) == '0') { return 4; }
		if (d.at(2) == '0' && d.at(3) != '0') { return 5; }
		if (d.at(2) != '0' && d.at(3) == '0') { return 6; }
		if ( d.at(2) != '0' && d.at(3) != '0') { return 7; }
	}
}
else {
	if (d.at(1) == '0') {
		if (d.at(2) == '0' && d.at(3) == '0') { return 8; }
		if (d.at(2) == '0' && d.at(3) != '0') { return 9; }
		if (d.at(2) != '0' && d.at(3) == '0') { return 10; }
		if (d.at(2) != '0' && d.at(3) != '0') { return 11; }
	}
	else {
		if (d.at(2) == '0' && d.at(3) == '0') { return 12; }
		if (d.at(2) == '0' && d.at(3) != '0') { return 13; }
		if (d.at(2) != '0' && d.at(3) == '0') { return 14; }
		if (d.at(2) != '0' && d.at(3) != '0') { return 15; }
	}
	
}

return 0;
}

TileMap TileMap::loadBoards(const std::string& tileset,const std::string& ends, sf::Vector2u tileSize, Boards b, unsigned int width) {
	// resize the vertex array to fit the level size
	TileMap additional;

	if (!m_tileset.loadFromFile(tileset)) 
	m_tileset.setRepeated(true);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * 26 * 4);

	additional.m_tileset.loadFromFile(ends);
	additional.m_tileset.setRepeated(true);
	additional.m_vertices.setPrimitiveType(sf::Quads);
	additional.m_vertices.resize(width * 26 * 4);

	// itterates thorught rows
	for (unsigned int i = 0; i < width; i++){
		int startNumber = Universals::getRandom(0, (m_tileset.getSize().x/tileSize.x)-18);
		int oneboard = 0;
		int whichboard = 0;
		for (unsigned int j = 0; j < 26; j++) {

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
			// define its 4 corners
			quad[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
			quad[1].position = sf::Vector2f((j + 1) * tileSize.x, i* tileSize.y);
			quad[2].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);

			//find its position in the tileset texture
			int tu = (startNumber + oneboard) % (m_tileset.getSize().x / tileSize.x);
			int tv = (startNumber + oneboard) / (m_tileset.getSize().x / tileSize.x);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			////when it gets to the next board
			if (oneboard == b[i][whichboard])
			{
				sf::Vertex* quad2 = &additional.m_vertices[(i + j * width) * 4];

				quad2[0].position = quad[0].position;
				quad2[1].position = quad[1].position;
				quad2[2].position = quad[2].position;
				quad2[3].position = quad[3].position;

				int moreRandom = Universals::getRandom(0, 5);
				int tu = (moreRandom) % (additional.m_tileset.getSize().x / tileSize.x);
				int tv = (moreRandom) / (additional.m_tileset.getSize().x / tileSize.x);

				quad2[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad2[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad2[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad2[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

				//skips a beat
				oneboard = 0; whichboard++; startNumber = Universals::getRandom(0, (m_tileset.getSize().x / tileSize.x) - 18);
			}
				
			
				
			oneboard++;
		}
	}
	return additional;
}
bool TileMap::loadHoles(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height, std::vector<std::vector<bool>> holes)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset)) return false;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = 0; 
			if (holes[j][i]) { //if a hole is to be drawn at that spot change tileFromOpaque to other
				tileNumber = 1;
				int random = Universals::getRandom(2, 6);
				if (i == holes[0].size() - 1 || holes[j][i + 1] == 0) { tileNumber = random ; }
				if (i == 0 || holes[j][i - 1] == 0) { tileNumber = random+5; }
			}
		

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}
bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<std::vector<String>> tiles, std::vector<std::vector<int>> roomTypes, unsigned int width, unsigned int height, sf::Vector2i current, std::vector<std::vector<bool>> visitedRooms)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset)) return false;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber=0;
			if (visitedRooms[j][i]){ tileNumber = getTileNumber(tiles[j][i]);}


			if (j == current.row && i == current.column) { tileNumber += 60; }
			else {
				if (roomTypes[j][i] == -1) { tileNumber = 0; }
				if (roomTypes[j][i]==1) { tileNumber += 15; }
				if (roomTypes[j][i]==2) { tileNumber += 30; }
				if (roomTypes[j][i]==3) { tileNumber += 45; }
			}

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();
		// apply the tileset texture
		states.texture = &m_tileset;
		// draw the vertex array
		target.draw(m_vertices, states);
	}

