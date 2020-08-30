#include "pch.h"
#include "Object.h"


Object::Object(const sf::Texture* texture, sf::Vector2u frameCount, float timePerFrame, sf::Vector2f position, bool looping):
	animation(texture,frameCount,timePerFrame,looping)
{

	this->shape.setPosition(position);
	shape.setTexture(*texture);
}

Object::Object()
{
}

Object::~Object()
{
}



void Object::update(float deltaTime)
{
	if(animate==true) animation.update(state, deltaTime);
	shape.setTextureRect(animation.rect);
}

void Object::move(sf::Vector2f v) { shape.move(v); }
void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const{ target.draw(this->shape, states);}

sf::Sprite& Object::getShape(){ return shape;}
const sf::Texture * Object::getTexture(){ return shape.getTexture();}
sf::Vector2f Object::getPosition(){return shape.getPosition();}

void Object::setAnimate(bool b){ this->animate = b;}
void Object::setState(unsigned int i){ this->state = state;}
void Object::setPosition(sf::Vector2f v){ shape.setPosition(v);}
void Object::setOrgin(sf::Vector2f v) { shape.setOrigin(v); }
void Object::setScale(sf::Vector2f v) { shape.setScale(v);}
void Object::setColor(sf::Color c) { shape.setColor(c);}
void Object::setTexture(std::string path) { sf::Texture tex; tex.loadFromFile(path); this->shape.setTexture(tex); }
void::Object::setFrame(int i) { animation.setFrame(i); shape.setTextureRect(animation.rect); }


