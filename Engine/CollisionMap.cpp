#include "pch.h"
#include "TileMap.h"
#include "pch.h"



TileMap::TileMap(int w, std::vector<std::vector<int>> v1)
{
	/*this->wall.shape.setFillColor(Color::Red);
	this->wall.shape.setSize(Vector2f(w, w));

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (v1[i][j] == 0)
			{

				this->wall.shape.setPosition(w * i, w * j);
				this->walls.push_back(this->wall.shape);
			}


		}
	}*/
}
TileMap::TileMap(int w)
{
	/*this->wall.setFillColor(Color::Red);
	this->wall.setSize(Vector2f(w, w));

	std::vector<std::vector<int>> v1{ 20 };
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 9; j++)
		{
			if (i != 0 && i != 14 && j != 0 && j != 8)
				v1[i].push_back(1);
			else
				v1[i].push_back(0);
		}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (v1[i][j] == 0)
			{

				this->wall.setPosition(w * i, w * j);
				this->walls.push_back(wall);
			}


		}
	}*/


}

TileMap::~TileMap()
{
	this->walls.clear();
}

void TileMap::update()
{
}

void TileMap::rendergrid(RenderTarget& target)
{
	/*for (int i = 0; i < this->walls.size(); i++)
	{


		this->walls[i].se
		target.draw(this->walls[i]);



	}

	*/




}

void TileMap::updateCollision(Entity * entity, const float & dt)
{
	/*if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > 1920)
	{
		entity->setPosition(1920 - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > 1080)
	{
		entity->setPosition(entity->getPosition().x, 1080 - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	for (int i = 0; i < this->walls.size(); i++)

	{
		sf::FloatRect playerBounds = entity->getGlobalBounds();
		sf::FloatRect wallBounds = this->walls[i].getGlobalBounds();
		sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
		if (wallBounds.intersects(nextPositionBounds))
		{
			//Bottom collision
			if (playerBounds.top < wallBounds.top
				&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left
				)
			{
				std::cout << "kolizja dol" << std::endl;
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
				std::cout << "kolizja gora" << std::endl;
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
				std::cout << "kolizja prawo" << std::endl;
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
				std::cout << "kolizja lewo" << std::endl;
				entity->stopVelocityX();
				entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
			}
		}

	}*/

}

