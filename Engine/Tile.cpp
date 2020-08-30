#include "pch.h"
#include "Tile.h"

Tile::Tile()
{

	//this->shape.setOutlineThickness(-1.f);
	//this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setFillColor(sf::Color::Transparent);
	//this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->collision = false;
	//this->type = type;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF,
	bool collision, short type)
{
	this->shape.setOutlineThickness(-1.f);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{

}

//Accessors
const short & Tile::getType() const
{

	return this->type;
}

const bool & Tile::getCollision() const
{
	return this->collision;
}

const sf::Vector2f & Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

//Functions
const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}



void Tile::update()
{

}

void Tile::render(sf::RenderTarget & target, const sf::Vector2f playerPosition)
{

	target.draw(this->shape);

}