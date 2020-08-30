#include "pch.h"
#include "tezBoss.h"


tezBoss::tezBoss(float x, float y, sf::Texture* texture)
{
	this->initVariables();
	this->createHitboxComponent(this->sprite, 1.f, 0.f, 265.f, 321.f);
	this->createMoevementComponent(100.f, 2000.f, 1000.f);
	this->setTexture(*texture);
	this->HP = 100;
	this->setPosition(x, y);
	this->damage = 10;
	this->collision = 0;
}


tezBoss::~tezBoss()
{
}




int tezBoss::getType()
{
	return 4;//4 IS boss
}

void tezBoss::update(const float & dt)
{

	this->movementComponent->update(dt);
	this->hitboxComponent->update();

}

void tezBoss::render(sf::RenderTarget & target)
{
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
	target.draw(this->sprite);
}

void tezBoss::handleInput(const float & dt)
{
}
