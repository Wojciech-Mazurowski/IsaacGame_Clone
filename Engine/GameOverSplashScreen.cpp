#include "pch.h"
#include "GameOverSplashScreen.h"
#include <iostream>

std::vector<std::string> GameOverSplashScreen::reasonSubtexts {"that's all the time we've got","you dead boi" }; //[0] NORTH, [1] SOUTH,[2] WEST ,[3] EAST

GameOverSplashScreen::GameOverSplashScreen()
{
}


GameOverSplashScreen::GameOverSplashScreen(std::string textureKey, unsigned int score, unsigned int underLyingState, int reason): SplashScreen(textureKey,"GAMEOVER", underLyingState)
{
	float xPosition = mainText.getPosition().x;
	subText.setFont(*Universals::FontManager::getFont("retro"));
	subText.setString(reasonSubtexts[reason]);
	subText.setCharacterSize(20);
	subText.setFillColor(sf::Color(255,255,255,220));
	this->subText.setOrigin((this->subText.getCharacterSize()*subText.getString().getSize()) / 2, this->subText.getCharacterSize() / 2);
	subText.setPosition(Universals::WindowManager::getMiddleOfScreen().x, mainText.getPosition().y + subText.getCharacterSize() * 2);

	scoreText.setFont(*Universals::FontManager::getFont("retro"));
	scoreText.setCharacterSize(80);
	std::string scoreString = std::to_string(score).append("--");
	scoreString.insert(0, "--");
	scoreText.setString(scoreString);
	this->scoreText.setOrigin((this->scoreText.getCharacterSize()*scoreText.getString().getSize()) / 2, this->scoreText.getCharacterSize() / 2);
	scoreText.setPosition(Universals::WindowManager::getMiddleOfScreen().x, subText.getPosition().y+scoreText.getCharacterSize());

	std::vector<std::string> menuOptions{"MainMenu","Quit"};
	menu = Menu(menuOptions, sf::Vector2f( xPosition, scoreText.getPosition().y + Universals::WindowManager::getScreenHeight()*0.1), Universals::WindowManager::getScreenHeight() * 0.05, 25,true);
	this->takesOverControl = true;
}


GameOverSplashScreen::~GameOverSplashScreen()
{
}

void GameOverSplashScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroud);
	target.draw(mainText);
	target.draw(subText);
	target.draw(scoreText);
	target.draw(menu);
}

void GameOverSplashScreen::handleInput(sf::Window& window) {
	menu.handleInput();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
		int menuChoice = menu.getCurrentlySelectedItem();
		switch (menuChoice) {
		case 0:  changeUnderLyingState(0);  break;
		case 1: window.close();  break;
		}
	}
}
