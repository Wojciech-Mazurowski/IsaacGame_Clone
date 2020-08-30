#include "pch.h"
#include "Character.h"




Character::Character(){}
Character::Character(std::string name, int mH, sf::Texture* texture) : name(name), maxHealth(mH){
	body.getShape().setTexture(*texture);
}

Character::~Character(){}

void Character::setScale(sf::Vector2f v){body.setScale(v);}
void Character::setOrgin(sf::Vector2f v){body.setOrgin(v);}
void Character::setPosition(sf::Vector2f v){this->body.setPosition(v);}
void Character::setColor(sf::Color c){body.setColor(c);}



Object Character::getBody(){ return this->body; }
std::string Character::getName(){ return name;}
const sf::Texture* Character::getTexture(){ return body.getTexture();}
int Character::getMaxHealth() { return this->maxHealth; }

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const{ target.draw(body,states);}