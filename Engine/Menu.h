#pragma once
#include "Universals.h"
class Menu: public sf::Drawable
{
private:
	bool toogleOn = false;
	int characterSize = 15;
	std::vector<sf::Text> menuItems; //all the possible choices in the menu
	int currentlySelectedItem=0; //the curently selected choice
	sf::Vector2f menuPosition; 
	float distanceBetweenItems;
	sf::Sprite pointer;
	int buffer = 0;
	bool centered = false;

public:
	Menu();
	Menu(std::vector<std::string> menuItemStrings, sf::Vector2f menuPosition, float distanceBetweenItems,int characterSize);
	Menu(std::vector<std::string> menuItemStrings, sf::Vector2f menuPosition, float distanceBetweenItems, int characterSize, bool center);
	~Menu();


	//ITERFACE
	void setToogleOnoff(bool b);
	void toogleVisible();
	bool getToogleOn();
	void addMenuItem(std::string item);
	void changeMenuItem(int menuItemIndex, std::string newString); //if a string in the menu is to change
	void setDistanceBetweenItems(float distance);
	void setBuffer(int buffer);
	int getCurrentlySelectedItem();
	void move(sf::Vector2f moveVector);

	sf::Vector2f getPosition();

	void handleInput();
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

//TO HANDLE THE OUTPUTS FROM MENU EACH CLASS NEEDS A HANDLER for example:

//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && buffer == 0) {
//	int menuChoice = sideMenu.getCurrentlySelectedItem();
//	switch (menuChoice) {
//	case 0: buffer = 10; hud.toogleVisible(); sideMenu.toogleVisible(); setTimeDialation(1); break;
//	case 1: stateChanges.x = 0; break;
//	case 2: window.close(); break;
//	}
//}