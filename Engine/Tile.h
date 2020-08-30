#pragma once
#include "pch.h"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

enum TileTypes { DEFAULT = 0, DAMAGING, DOODAD };

class Tile
{
private:

protected:
	bool collision;
	short type;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();
	sf::RectangleShape shape;
	//Accessors
	const short& getType() const;

	//Functions
	const bool & getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	void update();
	void render(sf::RenderTarget& target, const sf::Vector2f playerPosition = sf::Vector2f());
};


