#include "pch.h"
#include "Universals.h"


int Universals::getRandom(int b, int e) {
	std::uniform_real_distribution<double> distribution(b, e);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);
}

//TEXTURE MANAGER
Universals::TextureManager::TextureManager() {}
std::map<std::string, sf::Texture> Universals::TextureManager::textures;

sf::Texture* Universals::TextureManager::getTexture(std::string key){ return &textures.find(key)->second; }
void Universals::TextureManager::addTexture(std::string key, sf::Texture t) { textures.insert_or_assign(key,t); }

//WINDOW MANAGER
Universals::WindowManager::WindowManager() {}
int Universals::WindowManager::screenWidth = 1920;
int Universals::WindowManager::screenHeight = 1080;
float Universals::WindowManager::offset= 0.08;
std::vector<int> Universals::WindowManager::wallPositions { 0,0,0,0 }; //[0] NORTH, [1] SOUTH,[2] WEST ,[3] EAST

int Universals::WindowManager::getScreenWidth(){ return screenWidth;}
int Universals::WindowManager::getScreenHeight(){ return screenHeight;}
int Universals::WindowManager::getOffsetValue(){ return (-1)*(offset*screenWidth);}

int Universals::WindowManager::getWallPosition(int wallIndex){ return wallPositions[wallIndex];}

sf::Vector2f Universals::WindowManager::getMiddleOfScreen(){ return sf::Vector2f(screenWidth/2,screenHeight/2); }

sf::Vector2f Universals::WindowManager::getMiddleOfScreenWithOffset(){ return sf::Vector2f((screenWidth / 2)+getOffsetValue(), screenHeight / 2);}

void Universals::WindowManager::setScreenHeight(int h){ screenHeight = h;}
void Universals::WindowManager::setScreenWidth(int w){ screenWidth = w;}
void Universals::WindowManager::setOffset(float off) { offset = off; }
void Universals::WindowManager::setWallPositions(int north, int south, int west, int east)
{
	wallPositions.resize(4);
	wallPositions[0] = north;
	wallPositions[1] = south;
	wallPositions[2] = west;
	wallPositions[3] = east;
}



//SOUND MANAGER
Universals::SoundManager::SoundManager() {}
std::map<std::string, sf::SoundBuffer> Universals::SoundManager::sounds;

void Universals::SoundManager::playSound(std::string key, int volume) { sf::Sound s; s.setBuffer(sounds.find(key)->second); s.play(); }
void Universals::SoundManager::addSound(std::string key, sf::SoundBuffer t){ sounds.insert_or_assign(key, t); }

//PATH MANAGER
std::string Universals::PathManager::defaultPath;
std::string Universals::PathManager::currentLevelPath;
Universals::PathManager::PathManager(){}

std::string Universals::PathManager::getCurrentLevelPath() { return currentLevelPath; }
void Universals::PathManager::setCurrentLevelPath(int i) { currentLevelPath = defaultPath; currentLevelPath.append("\\Graphics\\Level").append(std::to_string(i)).append("\\"); }
void Universals::PathManager::setDefaultPath(std::string path) { defaultPath = path; }
std::string Universals::PathManager::getDefaultPath() { return defaultPath; }


//FONT MANAGER
Universals::FontManager::FontManager() {}
std::map<std::string, sf::Font> Universals::FontManager::fonts;

sf::Font* Universals::FontManager::getFont(std::string key) { return &fonts.find(key)->second; }
void Universals::FontManager::addFont(std::string key, sf::Font t) { fonts.insert_or_assign(key, t); }

