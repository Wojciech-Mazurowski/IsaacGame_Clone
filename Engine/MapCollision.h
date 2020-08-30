#pragma once
#include "Tile.h"
#include "Player.h"
#include <list>
#include "Astar.h"
#include "FollowingMonster.h"

class Tile;
class Entity;


class MapCollision
{
private:


	sf::RectangleShape collisionBox;

	sf::FloatRect nextPos;
public:
	MapCollision();
	void SetGrid(std::vector<std::vector<int>> v);
	static bool IsPassable(int x, int y, std::vector<std::vector<int>> grid);
	void follow(std::shared_ptr<Entity> player, std::shared_ptr<Entity> monster, const float& dt);
	MapCollision(int w);
	MapCollision(std::vector<std::vector<int>> v1, int w);
	void updateWalls();
	std::vector<std::vector<int>> grid{ 15 };
	virtual ~MapCollision();
	std::vector<std::vector<int>>  Get_Grid();
	void PlayerMonsterCollision(Entity* entity, Entity* enemy);
	void BulletCollision(Entity* player, Entity* enemy);

	void ConvertGrid();
	std::vector<std::vector<Tile> > map{ 30 };


	void update(Entity* entity, const float& dt);
	void render(sf::RenderTarget& target) const;

};



