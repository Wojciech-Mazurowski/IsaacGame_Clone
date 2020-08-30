#include "pch.h"
#include "Player1.h"




Player1::Player1(float x, float y, sf::Texture* texture): Player(x,y,texture)
{
}


Player1::~Player1()
{
}

void Player1::handleInput(const float& dt)
{

	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->move(-1.f, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->move(1.f, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->move(0.f, -1.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->move(0.f, 1.f, dt);
	}

	//strzelanie
	if (b1.shoot_timer < this->attack_speed)
		b1.shoot_timer++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(0.f, -5.0f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(0.f, 5.0f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(-5.0f, 0.f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(5.0f, 0.f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	


}
