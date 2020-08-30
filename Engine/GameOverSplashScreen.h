#pragma once
#include "SplashScreen.h"
class GameOverSplashScreen :public SplashScreen
{
private:
	unsigned int score;
	sf::Text scoreText;
	static std::vector<std::string> reasonSubtexts;
	sf::Text subText;
public:
	GameOverSplashScreen();
	GameOverSplashScreen(std::string textureKey, unsigned int score, unsigned int underLyingState,int reason);
	~GameOverSplashScreen();
	
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void handleInput(sf::Window & window);
};

