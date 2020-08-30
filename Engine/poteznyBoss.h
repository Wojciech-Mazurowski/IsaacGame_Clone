#pragma once
#include "Entity.h"
class poteznyBoss :
	public Entity
{
public:
	poteznyBoss(float x, float y, sf::Texture* texture);
	virtual ~poteznyBoss();
	int attackspeed;
	int range;
	int attackcount=0;

	//functions
	//void Follow(Entity* player, const float& dt);
	virtual int getType();
	void update(const float & dt);
	void render(sf::RenderTarget & target);
	virtual void handleInput(const float& dt);
	void updateattack();
	Clock AttackTimer;
};


