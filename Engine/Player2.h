#pragma once
#include "Player.h"
class Player2 :
	public Player
{
public:
	Player2(float x, float y, sf::Texture* texture);
	virtual ~Player2();

	virtual void handleInput(const float& dt);
};

