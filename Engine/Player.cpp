#include "pch.h"
#include "Player.h"


//init functions
void Player::initVariables()
{
}

void Player::initComponents()
{
}
//Constructors / destructors
Player::Player(float x,float y,sf::Texture* texture)
{
	this->initVariables();
	this->createHitboxComponent(this->sprite, 19.f, 32.f, 87.f, 87.f);
	this->createMoevementComponent(250.f, 2000.f, 1000.f);
	this->setTexture(*texture);
	this->createAnimationComponent(texture, sf::Vector2u{ 6,6 }, 0.2, true);
	this->setPosition(x, y);
	this->attack_speed = 50;
	this->range = 600;
	this->HP = 100;
	this->damage = 5;
	this->setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x, Universals::WindowManager::getMiddleOfScreenWithOffset().y);
	positionMonitor = sf::seconds(0);
}


Player::~Player()
{

}

int Player::getType()
{
	return 0;
}
void Player::handleInput(const float & dt)
{
}

void Player::update(const float & dt)
{
	if(hasMovedSubstaintially) hasMovedSubstaintially = false; //reset the variable at each itteration so it only is on for a single tick
	positionMonitor += sf::seconds(dt);
	if (positionMonitor.asSeconds() >= 1.5) { checkIfHasMovedSubstaintially(); positionMonitor = sf::seconds(0); }

	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	this->handleInput(dt);
	this->updateAnimation(dt, movementComponent->getState());
}


float x;
void Player::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		if (this->bullets[i].StartPos.x < this->bullets[i].shape.getPosition().x - this->range*0.6)
		{
			x = abs(this->bullets[i].StartPos.x - this->bullets[i].shape.getPosition().x);
			this->bullets[i].shape.move(1.5, double((this->bullets[i].currVelocity.y - ((x - pow((x - this->range*0.4), 2)) / 11000) / 8)));
			//	std::cout << double((this->bullets[i].currVelocity.y - ((x - pow((x - this->range*0.2), 2)) / 8000) / 8)) << std::endl;
		}
		if (this->bullets[i].StartPos.x > this->bullets[i].shape.getPosition().x + this->range*0.6)
		{
			x = abs(this->bullets[i].StartPos.x - this->bullets[i].shape.getPosition().x);
			this->bullets[i].shape.move(-1.5, double((this->bullets[i].currVelocity.y - ((x - pow((this->range*0.4), 2)) / 11000) / 8)));
			//std::cout << double(-(this->bullets[i].currVelocity.y - ((pow((x-this->range*0.2), 2)) / 4000) / 2)) << std::endl;
		}

	}
	for (size_t i = 0; i < this->bullets.size(); i++)
	{

		this->bullets[i].shape.move(this->bullets[i].currVelocity);

		//Out of bounds
		if (this->bullets[i].shape.getPosition().x < Universals::WindowManager::getWallPosition(2) || this->bullets[i].shape.getPosition().x > Universals::WindowManager::getWallPosition(3)
			|| this->bullets[i].shape.getPosition().y < Universals::WindowManager::getWallPosition(0) || this->bullets[i].shape.getPosition().y > Universals::WindowManager::getWallPosition(1))
		{

			this->bullets.erase(this->bullets.begin() + i);

		}//out of range
		else if (!(this->bullets[i].shape.getPosition().x < bullets[i].StartPos.x + this->range) || !(this->bullets[i].shape.getPosition().x > bullets[i].StartPos.x - this->range)
			|| !(this->bullets[i].shape.getPosition().y < bullets[i].StartPos.y + this->range) || !(this->bullets[i].shape.getPosition().y > bullets[i].StartPos.y - this->range))
		{
			this->bullets.erase(this->bullets.begin() + i);

		}
		for (size_t i = 0; i < this->bullets.size(); i++)
		{
			this->bullets[i].shape.setFillColor(sf::Color::Red);
			target.draw(this->bullets[i].shape);

		}
	}
}

void Player::setDmg(int dmg){this->dmg = dmg;}
void Player::setVelocity(int velocity){this->velocity = velocity;}
void Player::setHP(float hp){this->hp = hp;}
void Player::setAttackSpeed(int attack_speed){this->attack_speed = attack_speed;}



int Player::getmaxStaticItems(){return this->maxStaticItems;}
int Player::getmaxUsableItems(){return this->maxUsableItems;}

int Player::getPickUpRange(){return this->pickUpRange;}


void Player::checkIfHasMovedSubstaintially()
{
	if (abs(this->previousPosition.x - getPosition().x) > 80 || abs(this->previousPosition.y - getPosition().y) > 80) {
		hasMovedSubstaintially = true;
		previousPosition = getPosition();
	}
}

void Player::increaseDmg(float ammount){this->dmg +=(int) ammount;}
void Player::increaseAcceleration(float ammount) { movementComponent->increaseAcceleration(ammount); }
void Player::increaseHP(float ammount) { this->hp += ammount; }
void Player::increaseAttackSpeed(float ammount) { this->attack_speed += (int)ammount; }
void Player::increasePickUpRange(float ammount) { this->pickUpRange += (int)ammount; }

void Player::decreaseDmg(float ammount){this->dmg -= (int) ammount;}
void Player::decreaseAcceleration(float ammount){this->velocity += (int) ammount;}
void Player::decreaseHP(float ammount){this->hp -= ammount;}
void Player::decreaseAttackSpeed(float ammount){ this->attack_speed -= (int) ammount;}

bool Player::gethasMovedSubstaintially(){ return hasMovedSubstaintially;}



