#include "pch.h"
#include "characterView.h"


sf::Vector2f characterView::distance;
bool characterView::reverse = false;

characterView::characterView(){}
//characterView::characterView(Character character, float opacity, float scale, sf::Vector2f position, std::string baseTextureKey, ) {}

//front.c = characters[characterChoice];
//front.opacity = 1;
//front.scale = 1;
//front.position = frontPosition;
//front.base.setTexture(*Universals::TextureManager::getTexture("basePOne"));
//front.base.setOrigin(Universals::TextureManager::getTexture("base")->getSize().x / 2, Universals::TextureManager::getTexture("base")->getSize().y / 2);
//front.c.setOrgin(sf::Vector2f(Universals::TextureManager::getTexture("character")->getSize().x / 2, Universals::TextureManager::getTexture("character")->getSize().y / 2));
//front.health = Object(Universals::TextureManager::getTexture("health"), sf::Vector2u(10, 1), 1, sf::Vector2f(0, 0), false);
//front.health.setFrame((front.c.getMaxHealth() * 2) - 1);
//front.health.setOrgin(sf::Vector2f((Universals::TextureManager::getTexture("health")->getSize().x / 10) / 2, Universals::TextureManager::getTexture("health")->getSize().y));
//front.health.setPosition(sf::Vector2f(front.position.x, front.position.y - Universals::TextureManager::getTexture("character")->getSize().y - 10));
//front.health.setAnimate(false);
//front.characterName.setFont(*Universals::FontManager::getFont("retro"));
//front.characterName.setString(characters[characterChoice].getName());
//front.characterName.setOrigin(sf::Vector2f((front.characterName.getCharacterSize()*front.characterName.getString().getSize() / 2), front.characterName.getCharacterSize() / 2));
//front.characterName.setPosition(sf::Vector2f(front.position.x, 0));
//front.apply();


void characterView::apply(){
	//scale
	base.setScale(sf::Vector2f(scale, scale));
	c.setScale(sf::Vector2f(scale, scale));
	characterName.setScale(sf::Vector2f(scale, scale));

	//position
	base.setPosition(sf::Vector2f(position.x, position.y));
	//so that the character moves according to the scale
	int charY = position.y - (Universals::TextureManager::getTexture("character")->getSize().y / 2 * scale);
	c.setPosition(sf::Vector2f(position.x, charY));
	characterName.setPosition(sf::Vector2f(position.x, position.y - (Universals::TextureManager::getTexture("character")->getSize().y)*scale - 50 * scale));

	//oppacity
	if (opacity <= 0) { base.setColor(sf::Color(255, 255, 255, 0)); c.setColor(sf::Color(255, 255, 255, 0)); characterName.setFillColor(sf::Color(255, 255, 255, 0)); }
	else { base.setColor(sf::Color(255, 255, 255, opacity * 255)); c.setColor(sf::Color(255, 255, 255, opacity * 255)); characterName.setFillColor(sf::Color(255, 255, 255, opacity * 255)); }

}

///setters & getters
void characterView::setDistance(sf::Vector2f d) { distance = d;}
void characterView::setReverse(bool r){ reverse = r;}
bool characterView::getReverse() {return reverse;}

void characterView::update(bool isFront){
	int translationX = distance.x / frames;
	int translationY = distance.y / frames;
	if (!reverse) {
		this->position = sf::Vector2f(position.x - translationX, position.y + translationY);
		this->scale = scale + 0.5 / frames;
		if (isFront) { this->opacity -= 0.95 / (frames); }
		else { this->opacity += +0.95 / frames; }
	}
	else {
		this->position = sf::Vector2f(position.x + translationX, position.y - translationY);
		this->scale = scale - 0.5 / frames;
		if (!isFront) { this->opacity -= 0.95 / frames; }
		else { this->opacity += 0.95 / frames; }
	}

	apply();
}
void characterView::draw(sf::RenderTarget & target, sf::RenderStates states) const{
	target.draw(base, states);
	target.draw(c, states);
	target.draw(characterName, states);
	//target.draw(health);
}
