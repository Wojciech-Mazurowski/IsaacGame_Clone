#pragma once

#include "Entity.h"





class Player :
	public Entity
{

private:
	//variables
	//initfunctions
	void initVariables();
	void initComponents();

	int maxStaticItems = 5; //desribes the max ammount of static items a player can carry
	int maxUsableItems = 1; //describes the max ammount of usable items a player can carry
	int pickUpRange = 100; //range in which the player can pick up items
	sf::Vector2f previousPosition{ 0,0 };
	sf::Time positionMonitor;
	bool hasMovedSubstaintially=false;

public:
	Player(float x, float y, sf::Texture* texture);
	virtual ~Player();

	Bullet b1;
	int attack_speed;
	float hp;
	int dmg;
	int range;
	int velocity;


	virtual void handleInput(const float& dt);


	//Functions
	virtual int getType() final;
	void update(const float& dt);
	void render(sf::RenderTarget &target);

	//setters
	void setDmg(int dmg);
	void setVelocity(int velocity);
	void setHP(float hp);
	void setAttackSpeed(int attack_speed);

	//getters
	int getmaxStaticItems();
	int getmaxUsableItems();
	int getPickUpRange();
	bool gethasMovedSubstaintially();



	//helper functions for items
	void checkIfHasMovedSubstaintially();
	void increaseDmg(float ammount);
	void decreaseDmg(float ammount);
	void increaseAcceleration(float ammount);
	void decreaseAcceleration(float ammount);
	void increaseHP(float ammount);
	void decreaseHP(float  ammount);
	void increaseAttackSpeed(float ammount);
	void increasePickUpRange(float ammount);
	void decreaseAttackSpeed(float ammount);


};

