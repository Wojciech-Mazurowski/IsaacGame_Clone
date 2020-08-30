#pragma once
#include "pch.h"
#include <vector>
#include <iostream>
#include <stack>
#include <map>
#include<math.h>
#include<vector>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
#include<map>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include "Universals.h"


class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
	sf::FloatRect nextPosition;
public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x,float offset_y,
		float width,float height);
	virtual ~HitboxComponent();

	//functions
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	bool checkIntersect(const sf::FloatRect& frect);
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	void update();
	void render(sf::RenderTarget& target);
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

};

