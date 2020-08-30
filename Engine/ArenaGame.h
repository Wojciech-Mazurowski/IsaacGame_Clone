#pragma once
#include "Game.h"

class ArenaGame : public Game
{
private:
	int currentWave = 0;
	float difficulty = 1;
	//std::vector<Monster> monsters;

public:
	ArenaGame();
	~ArenaGame();

	virtual void prepare();
	virtual sf::Vector2u update(float deltaTime);
	virtual void resetState();
	virtual void devInput();



	bool hasTheWaveBeenCleared();
	void nextWave();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

