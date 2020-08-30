#pragma once
#include "pch.h"
#include "Tile.h"
using namespace sf;
class Bullet
{
public:
	CircleShape shape;
	Vector2f currVelocity;
	float maxSpeed;
	Vector2f StartPos;
	int shoot_timer;
	Bullet(float radius = 15.f);
	~Bullet();
	
};

