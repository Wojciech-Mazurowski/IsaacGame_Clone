#pragma once
#include "pch.h"
#include "Entity.h"
#include <cstdlib>
#include <cstdio>
#include <ctime>

class Entity;


class EnemyWorm :
	public Entity
{
private:
	//Variables

	//Initializer functions
	void initVariables();


public:

	//variables


	int state=0;
	Clock AttackTimer;
	Clock HideTimer;
	Clock HideTimerSprite;
	int zmieniono;
	bool playHideAnimation=false;
	bool playShowAnimation=false;

	//funcitons 2
	virtual int getType();
	EnemyWorm(float x, float y, sf::Texture* texture);
	virtual ~EnemyWorm();
	Bullet b3;
	int range;
	int attackSpeed;
	int ataki;
	virtual void handleInput(const float& dt);
	//Functions
	void Hide();
	void updateAttack(const float & dt);
	void update(const float & dt);
	void render(sf::RenderTarget & target);
};