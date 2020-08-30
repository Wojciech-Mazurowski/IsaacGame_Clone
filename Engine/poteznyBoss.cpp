#include "pch.h"
#include "PoteznyBoss.h"


poteznyBoss::poteznyBoss(float x, float y, sf::Texture* texture)
{
	this->initVariables();
	this->createHitboxComponent(this->sprite, 80.f, 0.f, 300.f, 400.f);
	//this->sprite.setOrigin((texture->getSize().x / 6) / 2, (texture->getSize().y /2));
	this->createMoevementComponent(100.f, 2000.f, 1000.f);
	this->createAnimationComponent(texture, sf::Vector2u{ 6,1 }, 0.2, true);
	this->setTexture(*texture);
	this->HP = 100;
	this->setPosition(x-150, y-250);
	this->damage = 10;
	this->collision = 0;
}


poteznyBoss::~poteznyBoss()
{
}




int poteznyBoss::getType()
{
	return 4;//4 IS boss
}

void poteznyBoss::update(const float & dt)
{
	this->attackspeed = 1;
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	this->handleInput(dt);
	this->updateAnimation(dt, movementComponent->getState());
	this->updateattack();
	this->range = 800;

}
Bullet b3;
int x;
void poteznyBoss::updateattack()
{
	if (AttackTimer.getElapsedTime().asSeconds() > this->attackspeed)
	{
		if (attackcount % 2==0)
		{
			x = 0;
		}
		else 
		{
			x = 2;
		}
		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(2.5f, x);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b3));


		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(-2.5f, -x);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(b3);


		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(x, 2.5f);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(b3);


		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(-x, -2.5f);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(b3);


		b3.shoot_timer = 0;
		this->attackcount++;
		AttackTimer.restart();

	}
}
void poteznyBoss::render(sf::RenderTarget & target)
{
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
	target.draw(this->sprite);
	for (size_t i = 0; i < this->bullets.size(); i++)
	{

		this->bullets[i].shape.move(this->bullets[i].currVelocity);

		//Out of bounds
		if (this->bullets[i].shape.getPosition().x < 0 || this->bullets[i].shape.getPosition().x > target.getSize().x
			|| this->bullets[i].shape.getPosition().y < 0 || this->bullets[i].shape.getPosition().y > target.getSize().y)
		{

			this->bullets.erase(this->bullets.begin() + i);

		}//out of range
		else if (!(this->bullets[i].shape.getPosition().x < bullets[i].StartPos.x + this->range) || !(this->bullets[i].shape.getPosition().x > bullets[i].StartPos.x - this->range)
			|| !(this->bullets[i].shape.getPosition().y < bullets[i].StartPos.y + this->range) || !(this->bullets[i].shape.getPosition().y > bullets[i].StartPos.y - this->range))
		{
			this->bullets.erase(this->bullets.begin() + i);

		}
	}
	for (size_t i = 0; i < this->bullets.size(); i++)
	{

		target.draw(this->bullets[i].shape);

	}
}

void poteznyBoss::handleInput(const float & dt)
{
}
