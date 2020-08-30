#pragma once
#include <string>
#include <random>
#include <vector>
#include "Universals.h"


using String = std::string;
using Boards = std::vector<std::vector<int>>;


class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
public:

	int getTileNumber(std::string d);
	TileMap loadBoards(const std::string& tileset, const std::string& ends, sf::Vector2u tileSize, Boards b, unsigned int width);
	bool loadHoles(const std::string & tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height, std::vector<std::vector<bool>> holes);
	bool load(const std::string & tileset, sf::Vector2u tileSize, std::vector<std::vector<std::string>> tiles, std::vector<std::vector<int>> roomTypes, unsigned int width, unsigned int height, sf::Vector2i current, std::vector<std::vector<bool>> visitedRooms);
	
};


