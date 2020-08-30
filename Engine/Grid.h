#pragma once
#include "pch.h"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <vector>
#include "Entity.h"

class Entity;


using namespace sf;
class Grid
{
public:
	std::vector<RectangleShape> walls{ 15 };

	RectangleShape wall;
	

	std::vector<int> globalbounds;
	
	Grid(int w, std::vector<std::vector<int>> v1);
	Grid(int w);
	~Grid();
	void rendergrid(RenderTarget& target);
	void updateCollision(Entity* entity, const float& dt);
};

