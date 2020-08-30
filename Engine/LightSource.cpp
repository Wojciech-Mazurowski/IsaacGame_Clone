#include "pch.h"
#include "LightSource.h"



LightSource::LightSource(sf::Vector2f position, float intensity, float r, float g, float b):
	position(position), intensity(intensity), color(r,g,b,255)
{

}

LightSource::LightSource(sf::Vector2f position, float intensity, sf::Color color):
	position(position), intensity(intensity), color(color)
{

}

LightSource::LightSource() {}
LightSource::~LightSource() {}


void LightSource::setPosition(sf::Vector2f p) {this->position = p;}
void LightSource::setIntensity(float i) {this->intensity = i;}
void LightSource::setColor(sf::Color c) { this->color = c; }

void LightSource::setCardinalDireciton(std::string direction)
{
	this->cardinalDirection = direction;
}

sf::Vector2f LightSource::getPosition(){ return this->position;}
float LightSource::getIntenisty(){ return this->intensity;}
sf::Color LightSource::getColor(){ return this->color;}

std::string LightSource::getCardinalDirection()
{
	return this->cardinalDirection;
}

void LightSource::addDrawArea(sf::Vector2f x, sf::Vector2f  y, sf::Vector2f z, sf::Vector2f k)
{
	sf::ConvexShape temp{ 4 };
	temp.setPoint(0, x);
	temp.setPoint(1, y);
	temp.setPoint(2, z);
	temp.setPoint(3, k);
	temp.setFillColor(sf::Color::Transparent);
	drawAreas.push_back(temp);
}
void LightSource::addDrawArea(sf::Vector2f x, sf::Vector2f  y, sf::Vector2f z, sf::Vector2f k, sf::Vector2f g)
{
	sf::ConvexShape temp{ 5 };
	temp.setPoint(0, x);
	temp.setPoint(1, y);
	temp.setPoint(2, z);
	temp.setPoint(3, k);
	temp.setPoint(4, g);
	temp.setFillColor(sf::Color::Transparent);
	drawAreas.push_back(temp);
}
void LightSource::addDrawArea(sf::Vector2f x, sf::Vector2f  y, sf::Vector2f z, sf::Vector2f k, sf::Vector2f g, sf::Vector2f h)
{
	sf::ConvexShape temp{ 6 };
	temp.setPoint(0, x);
	temp.setPoint(1, y);
	temp.setPoint(2, z);
	temp.setPoint(3, k);
	temp.setPoint(4, g);
	temp.setPoint(5, h);
	temp.setFillColor(sf::Color::Transparent);
	drawAreas.push_back(temp);
}

void LightSource::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	sf::Shader gausianBlur;
	gausianBlur.loadFromFile(Universals::PathManager::getDefaultPath().append("gaussianBlur.frag"), sf::Shader::Fragment);
	//gausianBlur.setUniform("blur_radius", sf::Glsl::Vec2(1, 1));

	sf::Shader radialGradient;
	radialGradient.loadFromFile(Universals::PathManager::getDefaultPath().append("radialGradient.frag"), sf::Shader::Fragment);
	
	radialGradient.setUniform("center", position);
	radialGradient.setUniform("radius", 15 * intensity);
	radialGradient.setUniform("color", sf::Glsl::Vec4(color));
	radialGradient.setUniform("windowHeight", (float)Universals::WindowManager::getScreenHeight());
	radialGradient.setUniform("expand", 0.1f);

	//draw all the draw area
		//modify to apply the shaders (blur and radial gradient)
	sf::RenderTexture image;
	image.create(Universals::WindowManager::getScreenWidth(), Universals::WindowManager::getScreenHeight());
	for (int i = 0; i < drawAreas.size(); i++)
	{
		sf::ConvexShape temp = drawAreas[i];
		image.clear(sf::Color::Transparent);
		image.draw(temp,&radialGradient);
		image.display();
		image.draw(sf::Sprite(image.getTexture()), &gausianBlur);
		image.display();
		target.draw(sf::Sprite(image.getTexture()),sf::BlendAdd);
		//target.draw(temp,&radialGradient);
	}
}

void LightSource::clearDrawAreas() {
	drawAreas.clear();
}



