#include "pch.h"
#include "StateManager.h"
#include <array>


StateManager::StateManager(){}
StateManager::~StateManager(){}


void StateManager::start()
{
	prepareWindow();
	resources.loadAll();
	loadCharacters();
	menu.setCharacters(characters);
	menu.prepare();
	gameLoop();
	
}
void StateManager::intro() {}

void StateManager::prepareWindow()
{
	window.setFramerateLimit(60);
	//possibly adjust screensize
}

void StateManager::loadCharacters() {
	characters.push_back(Character("Meryl", 5,Universals::TextureManager::getTexture("character")));
	characters.push_back(Character("Herla", 3,Universals::TextureManager::getTexture("character1")));
}

void StateManager::gameLoop() {
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Event windowEvent;
	sf::Vector2u stateChanges;
	bool toGenerateNormal = true;
	bool toGenerateArena = true;

	while (window.isOpen())
	{
		//checks if it wasnt closed
		while (window.pollEvent(windowEvent)) { if (windowEvent.type == sf::Event::Closed) { window.close(); } }
		deltaTime = clock.restart().asSeconds();

		//main menu
		if (state == 0){
			menu.handleInput(window);
			stateChanges = menu.update(deltaTime);
			state = stateChanges.x;
			window.clear(sf::Color(7, 7, 7, 255));
			window.draw(menu);
		}
		//NormalGame
		if (state == 1)
		{
			if (toGenerateNormal) { normalGame = NormalGame(); normalGame.setMaxTime(sf::seconds(600)); setCharacters(normalGame, stateChanges.y); normalGame.prepare(); toGenerateNormal = false; }
			
			window.clear(sf::Color(7, 7, 7, 255));
			stateChanges = normalGame.update(deltaTime);
			normalGame.handleInput(window);
			state = stateChanges.x;
			window.draw(normalGame);
			if (state == 0) { toGenerateNormal = true; }
		}
		//ArenaGame
		if (state == 2)
		{
			if (toGenerateArena) {arenaGame = ArenaGame(); arenaGame.setMaxTime(sf::seconds(60)); setCharacters(arenaGame, stateChanges.y); arenaGame.prepare(); toGenerateArena = false; }
			arenaGame.handleInput(window);
			window.clear(sf::Color(12, 12, 12, 255));
			stateChanges =arenaGame.update(deltaTime);
			state = stateChanges.x;
			window.draw(arenaGame);
			if (state == 0) { toGenerateArena = true; }
		}

		if (state == 3)
		{
		//std::cout<<
		}
		window.display();
	
	}
}

void StateManager::setCharacters(Game& g, int i) //the character choice is passed to the stateManager in the update vector
{
	int temp = i / 10; //the first digit of the number is the index of the first character in the character array
	int temp2 = i - (temp * 10);	//the seconds digit of the number is the index of the second one 
	if (temp2 != 9) { // (IF EQUALS 9 MEANS ONLY ONE CHARACTER WAS CHOSEN)
		if (temp2 == 0) { g.setPlayers(std::make_shared<Player2>(90, 90, Universals::TextureManager::getTexture("wampir"))); }
		if (temp2 == 1) { g.setPlayers(std::make_shared<Player2>(90, 90, Universals::TextureManager::getTexture("baba"))); }
	}

	if(temp==0){ g.setPlayers(std::make_shared<Player1>(90, 90, Universals::TextureManager::getTexture("wampir"))); }
	if (temp == 1) { g.setPlayers(std::make_shared<Player1>(90, 90, Universals::TextureManager::getTexture("baba"))); }
	
	
}



