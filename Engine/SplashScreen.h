#pragma once
#include "Menu.h"
class SplashScreen: public sf::Drawable
{
protected:
	sf::Sprite backgroud;
	sf::Text mainText;
	Menu menu;
	unsigned int underLyingState=0;
	bool takesOverControl = false;
public:
	SplashScreen();
	SplashScreen(std::string textureKey, std::string mainText,unsigned int underlyingState );
	SplashScreen(std::string mainText, unsigned int underlyingState);
	~SplashScreen();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void handleInput(sf::Window& window);
	virtual void update(float deltaTime);

	void changeUnderLyingState(unsigned int state);
	unsigned int getUnderLyingState();
	bool getTakesOverControl();
};

