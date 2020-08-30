#include "pch.h"
#include "MapCollision.h"



MapCollision::MapCollision(int w)
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 7; j++)
		{

			if (i == 4 && j == 6)
			{
				Tile xd;
				xd.shape.setSize(sf::Vector2f(w, w));
				xd.shape.setPosition(i*w, j*w);
				map[i].push_back(xd);
				this->grid[i].push_back(1);
			}
			else if (i == 4 && j == 2)
			{
				Tile xd;
				xd.shape.setSize(sf::Vector2f(w, w));
				xd.shape.setPosition(i * w, j * w);
				map[i].push_back(xd);
				this->grid[i].push_back(1);
			}
		
			else this->grid[i].push_back(0);

		}

	for (int j = 0; j < this->grid[0].size(); j++)
	{
		for (int i = 0; i < this->grid.size(); i++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}

}
MapCollision::MapCollision() {};
MapCollision::MapCollision(std::vector<std::vector<int>> v1, int w)
{
	this->grid = v1;
	this->ConvertGrid();
	updateWalls();
}

void MapCollision::updateWalls() {
	this->map.clear();
	map.resize(40);
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 0)
			{
				Tile xd2;
				xd2.shape.setSize(sf::Vector2f(90,90));
				xd2.shape.setPosition(sf::Vector2f{Universals::WindowManager::getMiddleOfScreenWithOffset().x - 45 - 540 - 90 + (i*90), Universals::WindowManager::getMiddleOfScreenWithOffset().y - 45 - 270 - 90 + (j*90)});
				map[i].push_back(xd2);
			}
		}
}

void MapCollision::ConvertGrid()
{
	std::vector<std::vector<int>> vcool;
	vcool.resize(40);
	for (int i = 0; i < 40; i++) {
		vcool[i].resize(40);
	}

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			vcool[j][i]=grid[i][j];
		}
	}
	this->grid = vcool;
}
MapCollision::~MapCollision()
{
	this->map.clear();
}
std::vector<std::vector<int>> MapCollision::Get_Grid()
{
	return this->grid;

}
void MapCollision::SetGrid(std::vector<std::vector<int>> v)
{
	this->grid = v;
	this->ConvertGrid();
	updateWalls();
}
int timer = 0;
void MapCollision::PlayerMonsterCollision(Entity * entity, Entity * enemy)
{

	sf::FloatRect playerBounds = entity->getGlobalBounds();
	sf::FloatRect enemyBounds = enemy->getGlobalBounds();
	if (playerBounds.intersects(enemyBounds) && timer <= 0 && entity->HP > 0)
	{
		entity->HP -= 10;
		timer = 100; 
		entity->pushInDirection(enemy->getVelocity());
	}
	timer--;

}



bool MapCollision::IsPassable(int x, int y, std::vector<std::vector<int>> grid)
{
	if (x < 0 || x >= 15 || y <0 || y >= 8)
		return false;
	if (grid[x][y] == 1)
		return false;
	else return true;
}

void MapCollision::follow(std::shared_ptr<Entity> player, std::shared_ptr<Entity> monster, const float& dt)
{
	std::list<Vector2i> path;
	if (std::static_pointer_cast<Player>(player)->gethasMovedSubstaintially() || !std::static_pointer_cast<FollowingMonster>(monster)->getHasPathToFollow()) { //if player has moved much find new way towards him
		path = Astar::A_Star(monster->getGridPosition(90), player->getGridPosition(90), this->grid);
		std::static_pointer_cast<FollowingMonster>(monster)->setPathToFollow(path);} 
	else { path = std::static_pointer_cast<FollowingMonster>(monster)->getPathItFollows(); } //else use the old way if such one exists

	Vector2f dir;

	if (path.size() > 2)
	{
		path.pop_back();
		dir = monster->move_towards(monster.get(), path.back());
	}
	else
	{
		dir = player->getPosition() - monster->getPosition();
		if (dir.x > 1.f || dir.x < -1.f)
			dir.x = (dir.x / abs(dir.x));
		if (dir.y > 1.f || dir.y < -1.f)
			dir.y = (dir.y / abs(dir.y));
	}
	monster->move(dir.x, dir.y, dt);
}



void MapCollision::BulletCollision(Entity * player, Entity * enemy)
{
	sf::FloatRect enemyBounds;
	sf::FloatRect bulletBounds;
	for (int i = 0; i < player->bullets.size(); i++)
	{
		enemyBounds = enemy->getGlobalBounds();
		bulletBounds = player->bullets[i].shape.getGlobalBounds();
		if (enemyBounds.intersects(bulletBounds) && enemy->HP > 0)
		{
			enemy->HP -= player->damage;
			std::cout << enemy->HP << std::endl;
			player->bullets.erase(player->bullets.begin() + i);
		}
	}

}


void MapCollision::update(Entity * entity, const float& dt)
{

	//WORLD BOUNDS
	if (entity->getPosition().x < Universals::WindowManager::getWallPosition(2) - 90)
	{
		entity->setPosition(Universals::WindowManager::getWallPosition(2) - 90, entity->getPosition().y);
		entity->stopVelocityX();

	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > Universals::WindowManager::getWallPosition(3)+90)
	{
		entity->setPosition(Universals::WindowManager::getWallPosition(3) + 90- entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < Universals::WindowManager::getWallPosition(0)-90)
	{
		entity->setPosition(entity->getPosition().x, Universals::WindowManager::getWallPosition(0)-90);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > Universals::WindowManager::getWallPosition(1)+90)
	{
		entity->setPosition(entity->getPosition().x, Universals::WindowManager::getWallPosition(1) + 90 - entity->getGlobalBounds().height);
		entity->stopVelocityY();

	}



	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[i].size(); j++)
		{
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = map[i][j].shape.getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
			if (this->map[i][j].intersects(nextPositionBounds) && entity->collision == 1)
			{






				//Bottom collision
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{

					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}

				//Top collision
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{

					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}

				//Right collision
				if (playerBounds.left < wallBounds.left
					&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{

					entity->stopVelocityX();
					entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}

				//Left collision
				else if (playerBounds.left > wallBounds.left
					&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{

					entity->stopVelocityX();
					entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}
			}
		}

}
void MapCollision::render(sf::RenderTarget & target) const
{
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[i].size(); j++)
		{

			//map[i][j].shape.setFillColor(sf::Color::Red);

			target.draw(map[i][j].shape);
		}
}