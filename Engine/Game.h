#pragma once
#include "State.h"
#include <vector>
#include "Level.h"
#include <iostream>
#include "HUD.h"
#include "GameOverSplashScreen.h"
#include "WithTimerSplashScreen.h"
#include "Menu.h"
#include "ItemsManager.h"
#include "TemporaryEffects.h"
#include "MapCollision.h"
class Entity;
using Levels = std::vector<Level>;

class Game : public State //purely virtual class
{
protected:
	int buffer = 0; //helper variable to help with input control
	bool devMode = true;
	HUD hud;
	Menu sideMenu;
	sf::Time maxTime = sf::seconds(600); //Max time to complete the map in seconds
	std::vector<std::shared_ptr<Entity>> players; //players in the game
	ItemsManager items; //manges the items currently on the map and in players's inventories
	TemporaryEffects temporaryEffects;

	int score = 0;

	bool splashScreenMode = false;
	std::shared_ptr<SplashScreen> splashScreen;

	float timeDialation = 1; //takes values between 0 and infinity- 1 for normal time passage, 0.5 for halftime, 0 for pause, 2 for double time

	Game();
	~Game();

public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void prepare();
	virtual sf::Vector2u update(float deltaTime);
	virtual void devInput();
	virtual void calculateScore();
	virtual void handleUseOfUsableItems();


	void resetStateChanges();

	void handleInput(sf::RenderWindow& window);
	void gameOver(int reason);

	void setPlayers(std::shared_ptr<Player> p);
	void setPlayers(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
	void setMaxTime(sf::Time max);
	void setTimeDialation(float timedialation);
};