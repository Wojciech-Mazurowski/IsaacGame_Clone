#include "pch.h"
#include "HUD.h"


HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD::prepareHUD(sf::Time maxTime) {
	timeW = TimeWidget(maxTime, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.180));
}


void HUD::prepareHUD(std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes, int width, int height, sf::Vector2i currentRoomCoordinates, sf::Vector2u tileSize,sf::Time maxTime, int hpp1)
{
	//position all the components, load initial ammounts
	miniMap = Map(doorStrings, roomTypes, width, height, currentRoomCoordinates, tileSize, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.325));
	timeW = TimeWidget(maxTime, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.180));
	background.setTexture(*Universals::TextureManager::getTexture("HUDBackground"));
	hpp1Text.setFont(*Universals::FontManager::getFont("retro"));
	hpp1Text.setPosition(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.585);
	std::string hpString = "HP ";
	hpString.append(std::to_string(hpp1));
	hpp1Text.setString(hpString);
	hpp2Text.setString("");
	hpp1Text.setFillColor(sf::Color(168, 0, 0, 200));
}


void HUD::prepareHUD(std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes, int width, int height, sf::Vector2i currentRoomCoordinates, sf::Vector2u tileSize, sf::Time maxTime, int hpp1, int hpp2)
{
	//position all the components, load initial ammounts
	miniMap = Map(doorStrings, roomTypes, width, height, currentRoomCoordinates, tileSize, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.325));
	timeW = TimeWidget(maxTime, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.180));
	background.setTexture(*Universals::TextureManager::getTexture("HUDBackground"));
	hpp1Text.setFont(*Universals::FontManager::getFont("retro"));
	std::string hpString = "HP ";
	hpString.append(std::to_string(hpp1));
	hpp1Text.setString(hpString);
	hpp1Text.setFillColor(sf::Color(168, 0, 0, 200));
	hpp1Text.setPosition(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.585);
	hpp2Text.setFont(*Universals::FontManager::getFont("retro"));
	hpp2Text.setFillColor(sf::Color(168, 0, 0, 200));
	std::string hpString2 = "HP ";
	hpString2.append(std::to_string(hpp2));
	hpp2Text.setString(hpString2);
	hpp2Text.setPosition(Universals::WindowManager::getScreenWidth()*0.905, Universals::WindowManager::getScreenHeight() * 0.670);
}

void HUD::toogleVisible() { visible = !visible; }

void HUD::incrementLevel(sf::Vector2i addNewRoomToMap, std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes) {
	miniMap.nextLevel(addNewRoomToMap,doorStrings,roomTypes);
}

bool HUD::isTimeOver() { return timeW.isTimeOver(); }
void HUD::update(float deltaTime) 
{
	timeW.update(deltaTime);
}

void HUD::updateMap(sf::Vector2i newRoom)
{
	miniMap.update(newRoom);
}

void HUD::updateHealth(int hpp1)
{
	std::string hpString = "HP ";
	hpString.append(std::to_string(hpp1));
	hpp1Text.setString(hpString);
}

void HUD::updateHealth(int hpp1, int hpp2)
{
	std::string hpString = "HP ";
	hpString.append(std::to_string(hpp1));
	hpp1Text.setString(hpString);
	std::string hpString2 = "HP ";
	hpString.append(std::to_string(hpp2));
	hpp2Text.setString(hpString2);
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (visible){
		target.draw(background, states);
		target.draw(miniMap, states);
		target.draw(timeW,states);
		if (hpp2Text.getString() != "") target.draw(hpp2Text);
		target.draw(hpp1Text);
	}
}
