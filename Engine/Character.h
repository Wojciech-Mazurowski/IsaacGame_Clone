#pragma once
#include "Object.h"
#include "Universals.h"

class Character: public sf::Drawable
{
private:
	std::string name;
	Object body;
	int maxHealth;
public:
	Character();
	Character(std::string name, int mH,sf::Texture* texture);
	~Character();

	
	Object getBody();
	const sf::Texture* getTexture();
	int getMaxHealth();
	std::string getName();

	void setScale(sf::Vector2f v);
	void setOrgin(sf::Vector2f v);
	void setPosition(sf::Vector2f v);
	void setColor(sf::Color c);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

