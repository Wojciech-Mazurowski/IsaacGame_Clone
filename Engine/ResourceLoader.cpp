#include "pch.h"
#include "ResourceLoader.h"
#include "Universals.h"


ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}

void ResourceLoader::loadAll()
{
	findDefaultPath();
	loadFonts();
	loadTextures();
}

void ResourceLoader::findDefaultPath() {
	Universals::PathManager::setDefaultPath("Files");
	Universals::PathManager::setCurrentLevelPath(1);
}
void ResourceLoader::loadFonts() {

	sf::Font retro;
	retro.loadFromFile(Universals::PathManager::getDefaultPath().append("\\retro.ttf"));
	Universals::FontManager::addFont("retro", retro);
}
void ResourceLoader::loadTextures()
{
	sf::Texture temp;
	std::string graphicsPath = Universals::PathManager::getDefaultPath().append("\\graphics\\");

	temp.loadFromFile(Universals::PathManager::getDefaultPath().append("\\overlay.png"));
	Universals::TextureManager::addTexture("overlay", temp);

	temp.loadFromFile(Universals::PathManager::getDefaultPath().append("\\testStripes.png"));
	Universals::TextureManager::addTexture("testStripes", temp);


	//loading menu items
	std::string menuPath = graphicsPath;
	menuPath.append("\\MainMenu\\");
	std::string help = menuPath;

	temp.loadFromFile(help.append("pointer.png"));
	help = menuPath;
	Universals::TextureManager::addTexture("pointer", temp);


	temp.loadFromFile(help.append("character.png"));
	Universals::TextureManager::addTexture("character", temp);
	help = menuPath;

	temp.loadFromFile(help.append("character1.png"));
	Universals::TextureManager::addTexture("character1", temp);
	help = menuPath;

	temp.loadFromFile(help.append("character2.png"));
	Universals::TextureManager::addTexture("character2", temp);
	help = menuPath;


	temp.loadFromFile(help.append("base.png"));
	Universals::TextureManager::addTexture("base", temp);
	help = menuPath;

	temp.loadFromFile(help.append("basePOne.png"));
	Universals::TextureManager::addTexture("basePOne", temp);
	help = menuPath;

	temp.loadFromFile(help.append("basePTwo.png"));
	Universals::TextureManager::addTexture("basePTwo", temp);
	help = menuPath;

	temp.loadFromFile(help.append("reflector.png"));
	Universals::TextureManager::addTexture("reflector", temp);
	help = menuPath;

	temp.loadFromFile(help.append("health.png"));
	Universals::TextureManager::addTexture("health", temp);
	help = menuPath;


	//load HUD items
	std::string hudPath = graphicsPath;
	hudPath.append("\\HUD\\");
	help = hudPath;

	temp.loadFromFile(help.append("HUDBackground.png"));
	Universals::TextureManager::addTexture("HUDBackground", temp);
	help = hudPath;

	//load ITEMS items
	std::string itemsPath = graphicsPath;
	itemsPath.append("\\Items\\");
	help = itemsPath;

	temp.loadFromFile(help.append("fastGlasses.png"));
	Universals::TextureManager::addTexture("fastGlasses", temp);
	help = itemsPath;

	temp.loadFromFile(help.append("grasper.png"));
	Universals::TextureManager::addTexture("grasper", temp);
	help = itemsPath;


	temp.loadFromFile(help.append("bar.png"));
	Universals::TextureManager::addTexture("bar", temp);
	help = itemsPath;

	temp.loadFromFile(help.append("hoodCap.png"));
	Universals::TextureManager::addTexture("hoodCap", temp);
	help = itemsPath;

	temp.loadFromFile(help.append("stopTheWatchWatch.png"));
	Universals::TextureManager::addTexture("stopWatch", temp);
	help = itemsPath;


	temp.loadFromFile(help.append("snapper.png"));
	Universals::TextureManager::addTexture("snapper", temp);
	help = itemsPath;



	//Loading Levels items
	std::string levelNumber{};
	std::string levelPath{};
	std::string helper{};
	for (int i = 1; i < 2; i++)
	{
		levelNumber = std::to_string(i);
		levelPath = graphicsPath;
		levelPath.append("\\Level").append(levelNumber).append("\\");
		help = levelPath;

		temp.loadFromFile(help.append("walls.png"));
		helper = "walls";
		Universals::TextureManager::addTexture(helper.append(levelNumber), temp);
		help = levelPath;

		temp.loadFromFile(help.append("doors.png"));
		helper = "door";
		Universals::TextureManager::addTexture(helper.append(levelNumber), temp);
		help = levelPath;

		temp.loadFromFile(help.append("doorsBoss.png"));
		helper = "doorBoss";
		Universals::TextureManager::addTexture(helper.append(levelNumber), temp);
		help = levelPath;

		temp.loadFromFile(help.append("doorsItem.png"));
		helper = "doorItem";
		Universals::TextureManager::addTexture(helper.append(levelNumber), temp);
		help = levelPath;

		temp.loadFromFile(help.append("chest.png"));
		helper = "chest";
		Universals::TextureManager::addTexture(helper.append(levelNumber), temp);
		help = levelPath;

		temp.loadFromFile(help.append("obsticle1.png"));
		helper = "obsticle";
		Universals::TextureManager::addTexture(helper.append(levelNumber), temp);
		help = levelPath;
	}

	temp.loadFromFile(Universals::PathManager::getDefaultPath().append("\\gameOver.png"));
	Universals::TextureManager::addTexture("gameOver", temp);

	//load characters
	help = graphicsPath;
	help.append("\\characters\\");
	temp.loadFromFile(help.append("character1.png"));
	Universals::TextureManager::addTexture("postac", temp);

	help = graphicsPath;
	help.append("\\characters\\");
	temp.loadFromFile(help.append("baba.png"));
	Universals::TextureManager::addTexture("baba", temp);

	help = graphicsPath;
	help.append("\\characters\\");
	temp.loadFromFile(help.append("wampir.png"));
	Universals::TextureManager::addTexture("wampir", temp);


	//load monsters
	help = graphicsPath;
	help.append("\\monsters\\");
	temp.loadFromFile(help.append("worm.png"));
	Universals::TextureManager::addTexture("worm", temp);

	help = graphicsPath;
	help.append("\\monsters\\");
	temp.loadFromFile(help.append("ghost.png"));
	Universals::TextureManager::addTexture("ghost", temp);

	help = graphicsPath;
	help.append("\\monsters\\");
	temp.loadFromFile(help.append("grubus.png"));
	Universals::TextureManager::addTexture("grubus", temp);

}
