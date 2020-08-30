#pragma once
#include "Character.h"

class characterView : public sf::Drawable {
public:
	static sf::Vector2f distance; //the distance between two views
	static bool reverse; //is the animation going in reverse
	int frames = 10; //how many frames does the animation take

	//the properties of the view
	sf::Text characterName;
	Object health;
	Character c;
	float opacity;
	float scale;
	sf::Sprite base;
	sf::Vector2f position;


	characterView();
	void update(bool isFront);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void apply();

	static void setDistance(sf::Vector2f  d);
	static void setReverse(bool r);
	static bool getReverse();
};

