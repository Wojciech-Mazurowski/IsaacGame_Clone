#pragma once
#include "Player.h"
class Player1 :public Player
{
public:
	Player1(float x, float y, sf::Texture* texture);
	~Player1();

	virtual void handleInput(const float& dt);
};

