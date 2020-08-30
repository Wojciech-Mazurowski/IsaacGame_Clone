#include "pch.h"
#include "Animation.h"
#include <iostream>


Animation::Animation(){}

Animation::Animation(const sf::Texture* texture, sf::Vector2u frameCount, float timePerFrame, bool loop): frameCount(frameCount), timePerFrame(timePerFrame), loop(loop)
{
	totalTime = 0.0f;
	currentFrame.x = 0;
	rect.width = texture->getSize().x / (float)frameCount.x;
	rect.height = texture->getSize().y / (float)frameCount.y;
}

Animation::~Animation()
{
}
void Animation::setFrame(int i) {currentFrame.x= i; rect.left = currentFrame.x*rect.width; rect.top = currentFrame.y*rect.height;}
void Animation::setNextFrame() { update(currentFrame.y, timePerFrame + 0.001); }
void Animation::setPreviousFrame() { currentFrame.x-= 2; update(currentFrame.y, timePerFrame + 0.001); }

void Animation::update(int row, float deltaTime)
{
		currentFrame.y = row;
		totalTime += deltaTime;
		if (totalTime >= timePerFrame)
		{
			//std::cout <<"\nFRAME: " <<currentFrame.x <<" state ("<<row<<")";
			totalTime -= timePerFrame;
			if (reversed == false)
			{ 
				if (currentFrame.x == frameCount.x-1)
				{
					if (loop) { currentFrame.x = 0; }
					else { isFinished = true; currentFrame.x--; }
				}
				currentFrame.x++; 
			}
			if (reversed == true)
			{ 
				if (currentFrame.x == 0)
				{
					if (loop) { currentFrame.x = frameCount.x; }
					else { isFinished = true; currentFrame.x++; }
				}
				currentFrame.x--; 
			}
			
		}
		rect.left = currentFrame.x*rect.width;
		rect.top = currentFrame.y*rect.height;
}

void Animation::setReversed(bool r)
{
	if (r == true) { currentFrame.x = frameCount.x-1; }else{ currentFrame.x = 0; }
	this->reversed = r; 
}

bool Animation::getIsFinished(){return isFinished;}
sf::Vector2u Animation::getFrameCount(){ return this->frameCount; }
bool Animation::getReversed(){ return reversed;}

void Animation::setIsFinished(bool b){ this->isFinished = b;}
void Animation::setLoop(bool b){ 
	if (b) { this->isFinished = false;}
	this->loop = b;
}

