#include "pch.h"
#include "Bullet.h"



Bullet::Bullet(float radius)
	: currVelocity(0.f, 0.f), maxSpeed(15.f)
{
		this->shape.setRadius(radius);	
		this->shape.setFillColor(Color::Red);
		this->shoot_timer = 150;
		
	
}



Bullet::~Bullet()
{
}
