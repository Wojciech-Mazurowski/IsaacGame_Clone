#include "pch.h"
#include "Entity.h"




void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;

}

Entity::Entity()
{
	this->initVariables();
	this->collision = 1;
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;

}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite & sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMoevementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture * texture, sf::Vector2u frameCount, float timePerFrame, bool looping)
{
	this->animationComponent = Animation(texture, frameCount, timePerFrame, looping);
}


const sf::Vector2f & Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return
		this->hitboxComponent->getPosition() +
		sf::Vector2f
		(
			this->hitboxComponent->getGlobalBounds().width / 2.f,
			this->hitboxComponent->getGlobalBounds().height / 2.f
		);

	return
		this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}
Vector2f Entity::move_towards(Entity* enemy, Vector2i v1)
{
	Vector2f ans;

	float EnemyPosition_X = enemy->getPosition().x;
	float EnemyPosition_Y = enemy->getPosition().y;
	ans = Entity::GridToPos(128, v1);


	Vector2f enemyVelocity;
	if (EnemyPosition_X > ans.x)
	{

		enemyVelocity.x = -1.f;

	}
	else if (EnemyPosition_X < ans.x)
	{
		enemyVelocity.x = 1.f;

	}
	if (EnemyPosition_Y > ans.y)
	{
		enemyVelocity.y = -1.f;

	}
	else if (EnemyPosition_Y < ans.y)
	{
		enemyVelocity.y = 1.f;

	}

	return enemyVelocity;
}

sf::Vector2f Entity::getVelocity(){ return this->movementComponent->getVelocity();}

void Entity::pushInDirection(sf::Vector2f velocity)
{ this->movementComponent->modifyVelocity(velocity);}

const sf::Vector2f Entity::GridToPos(const int gridSizeI, Vector2i Pos) const
{

	return Vector2f(
		Pos.x*gridSizeI,
		Pos.y*gridSizeI
	);

}
const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();

}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

bool Entity::isStillAlive()
{
	if (this->HP>0) return true;
	return false;
}

void Entity::updateAnimation(float dt, int state) {
	animationComponent.update(state, dt);
	sprite.setTextureRect(animationComponent.rect);
}