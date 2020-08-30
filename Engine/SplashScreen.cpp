#include "pch.h"
#include "SplashScreen.h"
#include <iostream>

SplashScreen::SplashScreen()
{
}

void SplashScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroud);
	target.draw(menu);
	target.draw(mainText);
}

void SplashScreen::handleInput(sf::Window & window)
{
}

void SplashScreen::update(float deltaTime){}

void SplashScreen::changeUnderLyingState(unsigned int state) { this->underLyingState = state;}

unsigned int SplashScreen::getUnderLyingState(){ return underLyingState;}

bool SplashScreen::getTakesOverControl(){ return this->takesOverControl;}

SplashScreen::SplashScreen(std::string textureKey, std::string mainText, unsigned int underLyingState)
{
	this->underLyingState = underLyingState;
	backgroud.setTexture(*Universals::TextureManager::getTexture(textureKey));
	this->mainText.setFont(*Universals::FontManager::getFont("retro"));
	this->mainText.setCharacterSize(50);
	mainText.append("");
	this->mainText.setString(mainText);
	this->mainText.setOrigin((this->mainText.getCharacterSize()*mainText.size()) / 2, this->mainText.getCharacterSize() / 2);
	this->mainText.setPosition(Universals::WindowManager::getMiddleOfScreen().x, Universals::WindowManager::getMiddleOfScreen().y*0.32);
}

SplashScreen::SplashScreen(std::string mainText, unsigned int underlyingState)
{
	this->underLyingState = underLyingState;

	this->mainText.setFont(*Universals::FontManager::getFont("retro"));
	this->mainText.setCharacterSize(50);
	mainText.append("");
	this->mainText.setString(mainText);
	this->mainText.setOrigin((this->mainText.getCharacterSize()*mainText.size()) / 2, this->mainText.getCharacterSize() / 2);
	this->mainText.setPosition(Universals::WindowManager::getMiddleOfScreen().x, Universals::WindowManager::getMiddleOfScreen().y*0.32);
}



SplashScreen::~SplashScreen()
{

}
