#pragma once
#include <math.h>
#include "MapCollision.h"
#include <list>
#include <map>
class Entity;
using namespace std;
using namespace sf;
struct mappableVector2I
{

	int x, y;
	mappableVector2I() {};

	mappableVector2I(sf::Vector2i a)
	{
		this->x = a.x;
		this->y = a.y;
	};
	mappableVector2I(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator ==(mappableVector2I a)
	{
		return a.x == this->x && a.y == this->y;
	}
	bool operator !=(mappableVector2I a)
	{
		return	this->operator==(a);

	}
	bool operator<(const mappableVector2I &a)  const {
		if (x == a.x)
			return y < a.y;

		return x < a.x;
	}


};
class Astar :
	public Entity
{



public:

	static bool IsPassable(mappableVector2I tile);
	static mappableVector2I GetLowestFscore(set<mappableVector2I> openSet, map<mappableVector2I, float> fScore);
	static std::list<Vector2i> A_Star(Vector2i start, Vector2i goal, vector<vector<int>> grid);
	static float dist_between(mappableVector2I a, mappableVector2I b);
	static std::list<Vector2i> reconstruct_path(std::map<mappableVector2I, mappableVector2I> cameFrom, mappableVector2I current);

};

