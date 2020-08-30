#pragma once
#include "Animation.h"
#include "MovementComponent.h"


class Object: public sf::Drawable
{
public:
	Object(const sf::Texture* texture, sf::Vector2u frameCount, float timePerFrame, sf::Vector2f position, bool looping);
	Object();
	~Object();

	virtual void update(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//getters
	sf::Sprite& getShape();
	const sf::Texture* getTexture();
	sf::Vector2f getPosition();

	//setters
	void setFrame(int i);
	void setScale(sf::Vector2f v);
	void setAnimate(bool b);
	void setState(unsigned int i);
	void setPosition(sf::Vector2f v);
	void setColor(sf::Color c);
	void setOrgin(sf::Vector2f v);
	void setTexture(std::string path);
	void move(sf::Vector2f v);



	Animation animation;
protected:
	bool animate= false; //declares whether the object should animate or not
	sf::Sprite shape; //holds the object's shape (texture)
	unsigned int state=0; //for animation

};

