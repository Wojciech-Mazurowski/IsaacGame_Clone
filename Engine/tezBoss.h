#pragma once
#include "Entity.h"
class tezBoss :
	public Entity
{
public:
	tezBoss(float x, float y, sf::Texture* texture);
	virtual ~tezBoss();


	//functions
	//void Follow(Entity* player, const float& dt);
	virtual int getType();
	void update(const float & dt);
	void render(sf::RenderTarget & target);
	virtual void handleInput(const float& dt);
};

