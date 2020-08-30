#include "pch.h"
#include "Menu.h"
#include <ios>


Menu::Menu()
{
}

Menu::Menu(std::vector<std::string> menuItemStrings, sf::Vector2f menuPosition, float distanceBetweenItems, int characterSize): menuPosition(menuPosition), distanceBetweenItems(distanceBetweenItems), characterSize(characterSize)
{
	toogleOn = true;

	//prepare the pointer
	pointer.setTexture(*Universals::TextureManager::getTexture("pointer"));
	pointer.setScale(sf::Vector2f((float) characterSize / 30, (float) characterSize / 30));

	//prepare all the items
	sf::Text temp;
	temp.setCharacterSize(characterSize);
	temp.setFont(*Universals::FontManager::getFont("retro"));
	for (int i = 0; i < menuItemStrings.size(); i++) {
		temp.setString(menuItemStrings[i]);
		sf::Vector2f itemPosition{ menuPosition.x,menuPosition.y + (distanceBetweenItems*i) };
		temp.setPosition(itemPosition);
		this->menuItems.push_back(temp);
	}
	update();
}

Menu::Menu(std::vector<std::string> menuItemStrings, sf::Vector2f menuPosition, float distanceBetweenItems, int characterSize, bool center) : menuPosition(menuPosition), distanceBetweenItems(distanceBetweenItems), characterSize(characterSize)
{
	toogleOn = true;
	centered = center;

	//prepare the pointer
	pointer.setTexture(*Universals::TextureManager::getTexture("pointer"));
	pointer.setScale(sf::Vector2f((float)characterSize / 30, (float)characterSize / 30));

	//prepare all the items
	sf::Text temp;
	temp.setCharacterSize(characterSize);
	temp.setFont(*Universals::FontManager::getFont("retro"));

	if (center) {

		for (int i = 0; i < menuItemStrings.size(); i++) {
			temp.setString(menuItemStrings[i]);
			temp.setOrigin((menuItemStrings[i].size()*characterSize) / 2, characterSize / 2);
			sf::Vector2f itemPosition{ menuPosition.x,menuPosition.y + (distanceBetweenItems*i) };
			temp.setPosition(itemPosition);
			this->menuItems.push_back(temp);
		}
	}
	else {
		//prepare all the items
		sf::Text temp;
		temp.setCharacterSize(characterSize);
		temp.setFont(*Universals::FontManager::getFont("retro"));
		for (int i = 0; i < menuItemStrings.size(); i++) {
			temp.setString(menuItemStrings[i]);
			sf::Vector2f itemPosition{ menuPosition.x,menuPosition.y + (distanceBetweenItems*i) };
			temp.setPosition(itemPosition);
			this->menuItems.push_back(temp);
		}
	}
	update();
}



Menu::~Menu()
{
}

void Menu::setToogleOnoff(bool b) { this->toogleOn = b; }

void Menu::toogleVisible()
{
	toogleOn = !toogleOn;
}

bool Menu::getToogleOn(){ return this->toogleOn;}

void Menu::addMenuItem(std::string item)
{
	sf::Text temp;
	temp.setCharacterSize(characterSize);
	temp.setFont(*Universals::FontManager::getFont("retro"));
	temp.setString(item);
	menuItems.push_back(temp);
}

void Menu::changeMenuItem(int menuItemIndex, std::string newString) {
	menuItems[menuItemIndex].setString(newString);
}

void Menu::setDistanceBetweenItems(float distance)
{
	this->distanceBetweenItems = distance;
}

void Menu::setBuffer(int buffer)
{
	this->buffer = buffer;
}

int Menu::getCurrentlySelectedItem()
{
	return currentlySelectedItem;
}

void Menu::move(sf::Vector2f moveVector)
{
	for (int i = 0; i < menuItems.size(); i++) {
		menuItems[i].move(moveVector);
	}
	pointer.move(moveVector);
}

sf::Vector2f Menu::getPosition(){ return menuPosition;}

void Menu::handleInput()
{
	if (toogleOn) {
		if(buffer>0) buffer--;
		//moving up in the menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (currentlySelectedItem != 0 && buffer <= 0) {  currentlySelectedItem--; update(); buffer = 5; }
		}
		//moving down in the menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (currentlySelectedItem != menuItems.size() - 1 && buffer <= 0) {  currentlySelectedItem++; update(); buffer = 5; }
		}
	}
	
}

void Menu::update()
{
	float pointerOffsetY = currentlySelectedItem * distanceBetweenItems;
	float pointerOffsetX = 0;
	if (centered) { pointerOffsetX = (menuItems[currentlySelectedItem].getString().getSize()*characterSize) / 2; }
	pointer.setPosition(sf::Vector2f{ menuItems[currentlySelectedItem].getPosition().x - pointer.getTexture()->getSize().x - 7 - pointerOffsetX ,menuPosition.y + (pointer.getTexture()->getSize().y / 2) + pointerOffsetY });

	for (int i = 0; i < menuItems.size(); i++) {
		menuItems[i].setFillColor(sf::Color(255, 255, 255, 150));
		if(currentlySelectedItem==i){ menuItems[i].setFillColor(sf::Color(255, 255, 255, 255)); }
	}
}

void Menu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (toogleOn) {
		for (int i = 0; i < menuItems.size(); i++) { target.draw(menuItems[i], states); }
		target.draw(pointer);
	}
}


