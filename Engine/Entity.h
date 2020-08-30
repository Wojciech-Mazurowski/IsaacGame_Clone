#pragma once
#include "pch.h"
#include "MovementComponent.h"
#include "Bullet.h"
#include "Animation.h"

class HitboxComponent;
class MovementComponent;

class Bullet;

class Entity
{
private:
	

protected:

	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	Animation animationComponent;


public:
	void initVariables();
	Entity();
	virtual ~Entity();
	int HP;
	int damage;
	bool collision;
	std::vector<Bullet> bullets;
	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height);
	void createMoevementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture* texture, sf::Vector2u frameCount, float timePerFrame, bool looping);
	

	//Accessors
	virtual int getType()=0;
	sf::Vector2f getVelocity();
	void pushInDirection(sf::Vector2f velocity);
	virtual const sf::Vector2f GridToPos(const int gridSizeI, sf::Vector2i Pos) const;
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	virtual void handleInput(const float& dt)=0;

	sf::Vector2f move_towards(Entity* enemy, Vector2i v1);
	//Modifiers

	virtual void setPosition(const float x, const float y);

	//Functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	bool isStillAlive();
	void updateAnimation(float dt, int state);
};

