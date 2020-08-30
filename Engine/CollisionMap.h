#pragma once
#include "pch.h"
#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:

	float gridSizeF;
	int gridSizeI;
	Tile wall;
	std::vector < std::vector<RectangleShape>> walls;


	//Culling

public:
	TileMap(int w, std::vector<std::vector<int>> v1);
	TileMap(int w);
	virtual ~TileMap();

	void update();
	void rendergrid(RenderTarget& target);
	void updateCollision(Entity* entity, const float& dt);
	
};