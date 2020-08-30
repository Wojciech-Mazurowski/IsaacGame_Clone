#pragma once
#include <random>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <map>

namespace Universals 
{

	class TextureManager {
	private:
		static std::map<std::string, sf::Texture> textures;
		TextureManager();
	public:
		static sf::Texture* getTexture(std::string key);
		static void addTexture(std::string key, sf::Texture t);

	};

	class SoundManager {
	private:
		static std::map<std::string, sf::SoundBuffer> sounds;
		SoundManager();
	public:
		static void playSound(std::string key, int volume);
		static void addSound(std::string key, sf::SoundBuffer t);
	};

	class FontManager {
	private:
		static std::map<std::string, sf::Font> fonts;
		FontManager();
	public:
		static sf::Font* getFont(std::string key);
		static void addFont(std::string key, sf::Font f);
	};

	class PathManager {
	private:
		static std::string defaultPath;
		static std::string currentLevelPath;
		PathManager();
		
	public:
		static void setCurrentLevelPath(int i);
		static std::string getCurrentLevelPath();
		static void setDefaultPath(std::string path);
		static std::string getDefaultPath();
	};

	class WindowManager {
		private:
			static int screenWidth;
			static int screenHeight;
			static float offset; //offsets the gameview so that Hud can be visible
			static std::vector<int> wallPositions; //[0] NORTH, [1] SOUTH,[2] WEST ,[3] EAST
			WindowManager();
		public:
			static int getScreenWidth();
			static int getScreenHeight();
			static int getOffsetValue();
			static int getWallPosition(int wallIndex); //[0] NORTH, [1] SOUTH,[2] WEST ,[3] EAST

			static sf::Vector2f getMiddleOfScreen();
			static sf::Vector2f getMiddleOfScreenWithOffset();
			
			static void setOffset(float off);
			static void setScreenHeight(int h);
			static void setScreenWidth(int w);
			static void setWallPositions(int north, int south, int west, int east);
	};

	int getRandom(int b, int e);
}


