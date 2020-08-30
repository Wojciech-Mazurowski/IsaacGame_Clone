#include "pch.h"
#include "State.h"


State::State(){}
State::~State(){}

sf::Vector2u State::update(float deltaTime) { return sf::Vector2u(); }

void State::handleInput(sf::RenderWindow& window){}

void State::draw(sf::RenderTarget & target, sf::RenderStates states) const{}

void State::prepare(){}

void State::resetState()
{
}
