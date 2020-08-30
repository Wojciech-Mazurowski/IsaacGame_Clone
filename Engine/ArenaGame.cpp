#include "pch.h"
#include "ArenaGame.h"


ArenaGame::ArenaGame(): Game(){}
ArenaGame::~ArenaGame(){}

void ArenaGame::prepare()
{
	stateChanges = sf::Vector2u(2, 0);
	Universals::WindowManager::setOffset(0.08f);
	//PREPARE THE HUD
 	hud.prepareHUD(maxTime);
	//POSITION THE PLAYERS!!

	//PREPARE THE SIDE MENU
	std::vector<std::string> menuItems{ "RESUME","MAINMENU","QUIT" };
	sideMenu = Menu(menuItems, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.85, Universals::WindowManager::getScreenHeight() * 0.20), Universals::WindowManager::getScreenHeight() * 0.05, 25);
	sideMenu.setToogleOnoff(false);
}


sf::Vector2u ArenaGame::update(float deltaTime)
{
	deltaTime *= timeDialation;
	deltaTime *= temporaryEffects.getTimeDialation(); //to account for time dialation

	for (auto it = players.begin(); it != players.end(); it++)
	{
		//update the characters
	}
	hud.update(deltaTime);
	if (hud.isTimeOver()) {
		if (!hasTheWaveBeenCleared()) gameOver(0);
		else nextWave();
	}
	if (splashScreen != NULL) splashScreen->update(deltaTime);
	if (stateChanges.x == 2) { return stateChanges; }
	else { sf::Vector2u temp = stateChanges; resetState(); return temp; }
}





void ArenaGame::resetState() {
	buffer = 10;
	stateChanges = sf::Vector2u(2, 0);
	hud.toogleVisible(); sideMenu.toogleVisible();
}

void ArenaGame::devInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && buffer == 0) { nextWave(); }
}

bool ArenaGame::hasTheWaveBeenCleared()
{
	//if(monsters.isEmpty()){ return true; }
	return false;
}

void ArenaGame::nextWave() {
	splashScreen = std::make_shared<WithTimerSplashScreen>("NEXT WAVE INCOMING", Universals::WindowManager::getMiddleOfScreen(),"prepare yourself",5,2);
	//WithTimerSplashScreen::WithTimerSplashScreen(std::string mainText, sf::Vector2f position, std::string subtext, unsigned int timeToCountDown, unsigned int underLyingStates) : SplashScreen(mainText, underLyingState)
	//generate monstersscaling with the wavenumber (difficulty and number)
}

void ArenaGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(hud);
	//draw players
	for (auto it = players.begin(); it != players.end(); it++) {
		//target.draw(*it);
	}
	target.draw(sideMenu, states);
	if (splashScreen != NULL) target.draw(*splashScreen);
}
