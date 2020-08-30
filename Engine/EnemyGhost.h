#pragma once
#include "FollowingMonster.h"


class EnemyGhost:public FollowingMonster
{
private:
public:
	EnemyGhost(float x, float y, sf::Texture* texture);
	virtual ~EnemyGhost();


	//functions
	//void Follow(Entity* player, const float& dt);
	virtual int getType();

};

