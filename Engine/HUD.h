#pragma once
#include "Map.h"
#include "Character.h"
#include "TimeWidget.h"


class HUD: public sf::Drawable
{
private:
	bool mapVisible = true;
	Map miniMap;
	TimeWidget timeW;
	sf::Sprite background;
	sf::Text hpp1Text;
	sf::Text hpp2Text;

	bool visible = true;
public:
	
	HUD();
	~HUD();

	void prepareHUD(sf::Time maxTime);


	void prepareHUD(std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes, int width, int height, sf::Vector2i currentRoomCoordinates,sf::Vector2u tileSize,sf::Time maxTimem, int hpp1);
	void prepareHUD(std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes, int width, int height, sf::Vector2i currentRoomCoordinates, sf::Vector2u tileSize, sf::Time maxTimem, int hpp1,int hpp2);
	void toogleVisible();
	void incrementLevel(sf::Vector2i addNewRoomToMap, std::vector<std::vector<std::string>> doorStrings, std::vector<std::vector<int>> roomTypes);
	bool isTimeOver();
	void update(float deltaTime);
	void updateMap(sf::Vector2i newRoom);
	void updateHealth(int hpp1);
	void updateHealth(int hpp1, int hpp2);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

