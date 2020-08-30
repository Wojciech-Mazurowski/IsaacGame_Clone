#pragma once
#include "Entity.h"
#include "Astar.h"

class FollowingMonster : public Entity
{
private:
	std::list<Vector2i> path;
	bool hasPathToFollow = false;

public:

	virtual ~FollowingMonster();
	FollowingMonster();

	//functions
	virtual int getType();
	void update(const float & dt) final;
	void render(sf::RenderTarget & target) final;
	virtual void handleInput(const float& dt) final;

	void setPathToFollow(std::list<Vector2i> path);
	std::list<Vector2i> getPathItFollows();
	bool getHasPathToFollow();
};

