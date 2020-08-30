#pragma once
#include "Universals.h"

class State: public sf::Drawable
{
protected:
	State();
	sf::Vector2u stateChanges{ 0,0 };
public:

	~State();

	virtual sf::Vector2u update(float deltaTime); //updates components of the state, and returns the stateChagnes vector
	virtual void handleInput(sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void prepare();
	virtual void resetState();

};

