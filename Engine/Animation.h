#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation();
	Animation(const sf::Texture* texture,sf::Vector2u frameCount,float timePerFrame, bool loop);
	~Animation();

	void setFrame(int i);
	void setNextFrame();
	void setPreviousFrame();
	void update(int row, float deltaTime);
	void setReversed(bool r);
	void setIsJustFinished(bool b);

	bool getIsFinished();
	sf::Vector2u getFrameCount();
	bool getReversed();
	void setIsFinished(bool b);
	void setLoop(bool b);

private:
	bool isFinished = false;
	bool loop = false;
	sf::Vector2u frameCount;
	sf::Vector2u currentFrame;
	bool reversed=false;
	float totalTime;
	float timePerFrame;
public:
	sf::IntRect rect;
};

