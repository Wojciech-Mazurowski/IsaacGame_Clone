#include "pch.h"
#include "EnemyWorm.h"

//Initializer functions
void EnemyWorm::initVariables()
{

}

int EnemyWorm::getType()
{
	return 1; //WORM IS 1
}

//Constructors / Destructors
EnemyWorm::EnemyWorm(float x, float y, sf::Texture* texture)
{
	this->initVariables();
	this->ataki = 0;
	this->createHitboxComponent(this->sprite, 1.f, 0.f, 75.f, 40.f);
	this->createMoevementComponent(250.f, 2000.f, 1000.f);
	this->createAnimationComponent(texture, sf::Vector2u{ 6,4},0.1f, true);
	this->setTexture(*texture);
	this->HP = 20;
	this->setPosition(x, y);
	this->range = 600;
	this->damage = 10;
	this->attackSpeed = 2;
	int random = Universals::getRandom(0, 2);
	if (random > 1) { state = 2; }
}

EnemyWorm::~EnemyWorm()
{

}



void EnemyWorm::handleInput(const float & dt)
{
}
void EnemyWorm::Hide()
{
	if (this->ataki == 2 && zmieniono == 0)
	{
		if(playHideAnimation){
			state = (state + 2) % 4;
			animationComponent.setLoop(false);
			playHideAnimation = false;
		}

		if (HideTimer.getElapsedTime().asSeconds() >Universals::getRandom(4,8))
		{
			state = 0;
			this->setPosition(Universals::getRandom(Universals::WindowManager::getWallPosition(2), Universals::WindowManager::getWallPosition(3) - this->hitboxComponent->getGlobalBounds().width),
				Universals::getRandom(Universals::WindowManager::getWallPosition(0), Universals::WindowManager::getWallPosition(1) - this->hitboxComponent->getGlobalBounds().height));
			AttackTimer.restart();
			this->ataki = 0;
			zmieniono = 1;
			HideTimer.restart();
			playHideAnimation = true;
		}
	}

}
void EnemyWorm::updateAttack(const float & dt)
{
	if (AttackTimer.getElapsedTime().asSeconds() > this->attackSpeed&&this->ataki < 2)
	{
		zmieniono = 0;
		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(2.5f, 0.f);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(Bullet(b3));


		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(-2.5f, 0.f);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(b3);


		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(0.f, 2.5f);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(b3);


		b3.shape.setPosition(this->getCenter());
		b3.shape.setFillColor(sf::Color::Red);
		b3.currVelocity = Vector2f(0.f, -2.5f);
		b3.StartPos = Vector2f(this->getCenter());
		this->bullets.push_back(b3);


		b3.shoot_timer = 0;

		this->ataki++;
		AttackTimer.restart();
		HideTimer.restart();
		HideTimerSprite.restart();
	}


}


void EnemyWorm::update(const float & dt)
{
	this->movementComponent->update(dt);
	if(dt>0){
		this->Hide();
		this->updateAttack(dt);
	}
	this->hitboxComponent->update();
	this->updateAnimation(dt, state);
}

void EnemyWorm::render(sf::RenderTarget & target)
{
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
	if (!(this->ataki == 2 && HideTimerSprite.getElapsedTime().asSeconds() > 1))
		target.draw(this->sprite);
	//	std::cout << this->bullets.size();
	for (size_t i = 0; i < this->bullets.size(); i++)
	{

		this->bullets[i].shape.move(this->bullets[i].currVelocity);

		//Out of bounds
		if (this->bullets[i].shape.getPosition().x < 0 || this->bullets[i].shape.getPosition().x > target.getSize().x
			|| this->bullets[i].shape.getPosition().y < 0 || this->bullets[i].shape.getPosition().y > target.getSize().y)
		{

			this->bullets.erase(this->bullets.begin() + i);

		}//out of range
		else if (!(this->bullets[i].shape.getPosition().x < bullets[i].StartPos.x + this->range) || !(this->bullets[i].shape.getPosition().x > bullets[i].StartPos.x - this->range)
			|| !(this->bullets[i].shape.getPosition().y < bullets[i].StartPos.y + this->range) || !(this->bullets[i].shape.getPosition().y > bullets[i].StartPos.y - this->range))
		{
			this->bullets.erase(this->bullets.begin() + i);

		}
	}
	for (size_t i = 0; i < this->bullets.size(); i++)
	{

		target.draw(this->bullets[i].shape);

	}

}