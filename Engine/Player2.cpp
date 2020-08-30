#include "pch.h"
#include "Player2.h"


Player2::Player2(float x, float y, sf::Texture* texture): Player(x, y, texture)
{
}


Player2::~Player2()
{
}

void Player2::handleInput(const float& dt)
{

	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->move(-1.f, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->move(1.f, 0.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->move(0.f, -1.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->move(0.f, 1.f, dt);
	}

	//strzelanie
	if (b1.shoot_timer < this->attack_speed)
		b1.shoot_timer++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(0.f, -5.0f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(0.f, 5.0f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(-5.0f, 0.f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && b1.shoot_timer >= this->attack_speed)
	{
		b1.shape.setPosition(this->getCenter());
		b1.currVelocity = Vector2f(5.0f, 0.f);
		b1.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b1));
		b1.shoot_timer = 0;

	}


}
