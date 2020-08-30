#include "pch.h"
#include "FollowingMonster.h"


FollowingMonster::FollowingMonster()
{
}


FollowingMonster::~FollowingMonster()
{
}


int FollowingMonster::getType()
{
	return 2;//2 IS FOLLOWING
}

void FollowingMonster::update(const float & dt) 
{
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	this->updateAnimation(dt, movementComponent->getState());
	this->updateAnimation(dt, movementComponent->getState());
}

void FollowingMonster::render(sf::RenderTarget & target) 
{
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
	target.draw(this->sprite);
}

void FollowingMonster::handleInput(const float & dt) 
{
}

void FollowingMonster::setPathToFollow(std::list<Vector2i> path) { this->hasPathToFollow = true;  this->path = path; }

std::list<Vector2i>FollowingMonster::getPathItFollows() { return path; }
bool FollowingMonster::getHasPathToFollow() { return hasPathToFollow; }

