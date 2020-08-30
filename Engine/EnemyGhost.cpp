#include "pch.h"
#include "EnemyGhost.h"


EnemyGhost::EnemyGhost(float x, float y, sf::Texture* texture): FollowingMonster()
{
	this->initVariables();
	this->createHitboxComponent(this->sprite, 1.f, 0.f, 90.f, 90.f);
	this->createMoevementComponent(100.f, 2000.f, 1000.f);
	this->createAnimationComponent(texture, sf::Vector2u{ 6,6 }, 0.1f, true);
	this->setTexture(*texture);
	this->HP = 20;
	this->setPosition(x, y);
	this->damage = 10;
	this->collision = 0;
}


EnemyGhost::~EnemyGhost()
{
}

int EnemyGhost::getType()
{
	return 2;//2 IS VAMPIRE
}
