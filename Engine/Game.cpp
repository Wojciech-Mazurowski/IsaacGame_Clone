#include "pch.h"
#include "Game.h"
#include <iostream>


Game::Game(){}
Game::~Game(){}


void Game::setPlayers(std::shared_ptr<Player> p){ players.push_back(p);}
void Game::setPlayers(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2){ players.push_back(p1); players.push_back(p2);}

void Game::setMaxTime(sf::Time max){this->maxTime =max;}


void Game::prepare(){}

void Game::resetStateChanges() {}

void Game::setTimeDialation(float timedialation) { this->timeDialation =timedialation; }

void Game::handleInput(sf::RenderWindow & window)
{
	if (buffer > 0) buffer--;
	if (splashScreen == NULL || !splashScreen->getTakesOverControl()){
		if (!sideMenu.getToogleOn()) {

			//input for development's sake
			if (devMode == true) { devInput(); }
			//normal input

			//handlespecial input-> players using special items
			handleUseOfUsableItems();
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && buffer == 0) { buffer = 10; hud.toogleVisible(); sideMenu.toogleVisible(); setTimeDialation(0); }
		}
		else {
			sideMenu.handleInput();
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && buffer == 0) { buffer = 10; hud.toogleVisible(); sideMenu.toogleVisible(); setTimeDialation(1);}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && buffer == 0) {
				int menuChoice = sideMenu.getCurrentlySelectedItem();
				switch (menuChoice) {
				case 0: buffer = 10; hud.toogleVisible(); sideMenu.toogleVisible(); setTimeDialation(1); break;
				case 1: stateChanges.x = 0; break;
				case 2: window.close(); break;
				}
			}
		}
	}
	else { 
		if(splashScreen!=NULL){
			splashScreen->handleInput(window);
			stateChanges.x = splashScreen->getUnderLyingState();
		}
	}
	
}

void Game::handleUseOfUsableItems() {};

void Game::devInput() {}

void Game::calculateScore(){}



void Game::gameOver(int reason) {
		calculateScore();

	/*	sf::RenderTexture all;
		all.create(Universals::WindowManager::getScreenWidth(), Universals::WindowManager::getScreenHeight());
		sf::Shader blur;
		blur.loadFromFile(Universals::PathManager::getDefaultPath().append("gausBlur.frag"), sf::Shader::Fragment);
		blur.setUniform("rt_w",(float) Universals::WindowManager::getScreenWidth());
		blur.setUniform("rt_h", (float)Universals::WindowManager::getScreenHeight());
		draw(all, &blur);
		all.display();
		draw(all, &blur);
		all.display();*/
		/*Universals::TextureManager::addTexture("gameOver", all.getTexture());*/

		splashScreen = std::make_shared<GameOverSplashScreen>("gameOver", score, (unsigned)stateChanges.x, reason);
		splashScreenMode = true;
	
}

sf::Vector2u Game::update(float deltaTime) { return sf::Vector2u(0, 0); }
void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const{}
