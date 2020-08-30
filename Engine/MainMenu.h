#pragma once
#include <iostream>
#include "State.h"
#include "characterView.h"
#include "Menu.h"

class MainMenu : public State
{
private:
	sf::Shader shader;
	Object light;

	int buffer = 0;
	int modeChoice = 0;
	Menu mainMenu;
	
	//MainMenu items
	int setting = 0;
	Menu settingsMenu;
	bool settingsOn = false;
	bool coOpOn = false;

	//characterChoice
	int characterChoice = 0;
	int characterChoicePlayer1 = 0;
	int characterChoicePlayer2 = 9;
	std::vector<Character> characters;
	bool changeCharacter = false;
	characterView front;
	characterView back;
	characterView helper;
	//position of the character display in the front
	sf::Vector2f frontPosition {600,Universals::WindowManager::getScreenHeight()-300};
	sf::Vector2f reversePosition;

public:
	MainMenu();
	~MainMenu();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void prepare();
	virtual sf::Vector2u update(float deltaTime); 
	virtual void handleInput(sf::RenderWindow& window);
	virtual void resetState();



	void setCharacters(std::vector<Character> characters);
	void updateCharacters();
	void showSettings();
	void hideSettings();
	void helperPrep(bool b);
	void incrementCharacter();
	void decreaseCharacter();
	void updateCharacterChoicePlayerOne();
	void updateCharacterChoicePlayerTwo();

};

