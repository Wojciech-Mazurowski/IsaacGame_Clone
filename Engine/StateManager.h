#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <stack>
#include <random>
#include <string>
#include "NormalGame.h"
#include "ArenaGame.h"
#include "MainMenu.h"
#include "Player.h"
#include "Player1.h"
#include "Player2.h"
#include "ResourceLoader.h"

class StateManager
{
private:
	sf::RenderWindow window{ sf::VideoMode(1920,1080), "Gierka ", sf::Style::Fullscreen };
	//sf::RenderWindow window{ sf::VideoMode(1920,1080), "Gierka ", sf::Style::Default };
	std::vector<Character> characters; //holds the characters that can be chosen in the game

	int state=0;
	MainMenu menu;
	NormalGame normalGame;
	ArenaGame arenaGame;
	ResourceLoader resources;
public:
	StateManager();
	~StateManager();


	
	void start();
	//loading
	void prepareWindow();

	void loadCharacters();



	//actualGameloop
	void gameLoop();

	//helper functions
	void intro();
	void setCharacters(Game& g, int i);

};

