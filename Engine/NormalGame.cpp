#include "pch.h"
#include "NormalGame.h"


NormalGame::NormalGame(): Game(){}


NormalGame::~NormalGame() {}

void NormalGame::prepare()
{
	
	stateChanges = sf::Vector2u(1, 0);
	Universals::WindowManager::setOffset(0.08);
	Universals::WindowManager::setWallPositions(Universals::WindowManager::getScreenHeight()*0.208, Universals::WindowManager::getScreenHeight()*0.792, Universals::WindowManager::getScreenWidth()*0.115, Universals::WindowManager::getScreenWidth()*0.725);

	//GENERATE ALL THE LEVELS
	for (int i = 0; i < numberOfLevels; i++) {
		Level temp;
		temp.setDifficulty(i + 1);
		temp.setMinRooms(10 + i * 5);
		temp.setMaxRooms(temp.getMinRooms() + 5 * ((1 / 2)*i));
		temp.generateLevel();
		levels.push_back(temp);
	}
	currentLevel = std::make_shared<Level>(levels[currentLevelNumber]);
	currentLevel->generateInsides();
	currentRoom = currentLevel->getCurrent();
	tileMap = MapCollision(currentRoom->getMovementZones(),90);
	//PREPARE THE HUD
	if (players.size() > 1) {
		hud.prepareHUD(currentLevel->getDoorStrings(), currentLevel->getRoomTypes(), 10, 10, currentLevel->getCurrentC(), sf::Vector2u(23, 23), maxTime, players[0]->HP, players[1]->HP);
	}
	else {
		hud.prepareHUD(currentLevel->getDoorStrings(), currentLevel->getRoomTypes(), 10, 10, currentLevel->getCurrentC(), sf::Vector2u(23, 23), maxTime, players[0]->HP);
	}
	//POSITION THE PLAYERS!!

	//add player pointers to items manager
	for (int i = 0; i < players.size(); i++) {  currentRoom->addPlayer(std::static_pointer_cast<Player>(players[i])); items.addPlayer(std::static_pointer_cast<Player>(players[i]));}
	items.addCurrentRoom(currentRoom);

	wasset = 0;
	//add monsters that follow
	followingCreatures = currentRoom->getVampires();

	//PREPARE THE SIDE MENU
	std::vector<std::string> menuItems{ "RESUME","MAINMENU","QUIT" };
	sideMenu = Menu(menuItems, sf::Vector2f(Universals::WindowManager::getScreenWidth()*0.85, Universals::WindowManager::getScreenHeight() * 0.20), Universals::WindowManager::getScreenHeight() * 0.05, 25);
	sideMenu.setToogleOnoff(false);
}

void NormalGame::changeRoom(int direction) { //0 for north 1 for south 2 for west 3 for east
	if (direction > -1) {
		switch (direction) {
		case 0: currentLevel->goNorth(); 
		for (auto p : players){
			p->setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x - 45 - 540 - 90 + (7 * 90), Universals::WindowManager::getMiddleOfScreenWithOffset().y - 45 - 270 - 90 + (7 * 90));
		}
		break;
		case 1: currentLevel->goSouth(); 
		for (auto p : players) {
			p->setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x - 45 - 540 - 90 + (7 * 90), Universals::WindowManager::getMiddleOfScreenWithOffset().y - 45 - 270 - 90 + (1 * 90));
		}
		break;
		case 2: currentLevel->goWest(); 
			for (auto p : players) {
				p->setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x - 45 - 540 - 90 + (13 * 90), Universals::WindowManager::getMiddleOfScreenWithOffset().y - 45 - 270 - 90 + (4 * 90));
			}
			break;
		case 3: currentLevel->goEast(); 
			for (auto p : players) {
				p->setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x - 45 - 540 - 90 + (1 * 90), Universals::WindowManager::getMiddleOfScreenWithOffset().y - 45 - 270 - 90 + (4 * 90));
			}
			break;
		default: break;
		}

		currentRoom = currentLevel->getCurrent();
		wasset = 0;
		items.addChestsToManager(currentRoom->getChests());
		items.updateRoom(currentRoom);

		for (int i = 0; i < players.size(); i++) { std::shared_ptr<Player> p(std::static_pointer_cast<Player>(players[i]));  currentRoom->addPlayer(p); }
		hud.updateMap(currentRoom->getCoordinates());

		tileMap.SetGrid(currentRoom->getMovementZones());
		buffer = 100;
	}

}



sf::Vector2u NormalGame::update(float deltaTime)
{
	
	deltaTime *= timeDialation; //to account for time dialation
	temporaryEffects.update(deltaTime); //so that the timeDialationDoesntHaveToBeConpensatedFor
	deltaTime *= temporaryEffects.getTimeDialation(); //to account for a effect of time dialation

	if (!currentRoom->getHasBeenCleared()) {
		followingCreatures = currentRoom->getVampires();
		RestCreatures = currentRoom->getRest();
	}

	
	for (auto vampire : followingCreatures) //path FINDING
	{
		tileMap.follow(players[0], vampire, deltaTime); 
		tileMap.BulletCollision(players[0].get(), vampire.get());
		tileMap.PlayerMonsterCollision(players[0].get(), vampire.get());
		if (players.size() > 1) {
			tileMap.follow(players[1], vampire, deltaTime);
			tileMap.BulletCollision(players[1].get(), vampire.get());
			tileMap.PlayerMonsterCollision(players[1].get(), vampire.get());
		}
	}

	for (auto creature : RestCreatures)
	{
		tileMap.BulletCollision(players[0].get(), creature.get());
		tileMap.PlayerMonsterCollision(players[0].get(), creature.get());
		tileMap.BulletCollision(creature.get(), players[0].get());
		if (players.size() > 1) {
			tileMap.BulletCollision(players[1].get(), creature.get());
			tileMap.PlayerMonsterCollision(players[1].get(), creature.get());
			tileMap.BulletCollision(creature.get(), players[1].get());
		}
	}

	currentRoom->update( deltaTime);
	if (currentLevel->getCurrentC() == currentLevel->getBoss() && currentRoom->getHasBeenCleared()) { incrementLevel(); }

		
		if (!splashScreenMode && !sideMenu.getToogleOn() && buffer==0) { players[0]->handleInput(deltaTime); }
			tileMap.update(players[0].get(), deltaTime);
			players[0]->update(deltaTime);
			hud.updateHealth(players[0]->HP);
	//		std::cout << "\nHP"<<players[0]->HP;
			if (!players[0]->isStillAlive()) { gameOver(1); }
		if (players.size() > 1)
		{
			hud.updateHealth(players[0]->HP, players[1]->HP);
			if (!splashScreenMode && !sideMenu.getToogleOn() && buffer == 0) { players[1]->handleInput(deltaTime); }
			tileMap.update(players[1].get(), deltaTime);
			players[1]->update(deltaTime);
			if (!players[1]->isStillAlive()) { gameOver(1); }
		}
	
	hud.update(deltaTime);

	if (hud.isTimeOver() && !splashScreenMode) { gameOver(0); }

	items.update(deltaTime);
	
	
	if (currentRoom->checkIfWasCleaned()) {
		if (currentLevel->getCurrentC() == currentLevel->getBoss() && buffer == 0) {
			buffer = 10;
			incrementLevel();
		}
		else {
			currentRoom->setHasBeenCleared(true);
			currentRoom->allowPlayerToMoveThroughDoors();
		}
	}

	if (currentRoom->getHasJustBeenCleared()) { 
		if (currentLevel->getCurrentC() == currentLevel->getBoss() && buffer == 0) {
			buffer = 10;
			incrementLevel();
		}
		tileMap.SetGrid(currentRoom->getMovementZones());
		currentRoom->setHasJustBeenCleared(false);
	}

	

	changeRoom(doorsCheck());

	if (stateChanges.x == 1) { return stateChanges; }
	else { sf::Vector2u temp = stateChanges; resetState(); return temp; }
	
}


void NormalGame::devInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && buffer == 0) {
		buffer = 10;
		currentRoom->clear();
		tileMap.SetGrid(currentRoom->getMovementZones());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8) && buffer == 0) {
		buffer = 10;
		changeRoom(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2) && buffer == 0) {
		buffer = 10;
		changeRoom(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4) && buffer == 0) {
		buffer = 10;
		changeRoom(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6) && buffer == 0) {
		buffer = 10;
		changeRoom(3);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F5)) {
		buffer = 10;
		teleportToBossRoom();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F7) && buffer == 0) {
		buffer = 10;
		items.dropRandomItem(Universals::WindowManager::getMiddleOfScreenWithOffset());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F6) && buffer == 0) {
		buffer = 10;
		items.printItemsInTheChests();
		items.printItemsInTheRoom();
	}

	//if you step into the boss room it just transports you to the other level

}

void NormalGame::teleportToBossRoom() {
	currentRoom = currentLevel->getBossRoom();
	wasset = 0;
	items.addChestsToManager(currentRoom->getChests());
	items.updateRoom(currentRoom);

	for (int i = 0; i < players.size(); i++) { std::shared_ptr<Player> p(std::static_pointer_cast<Player>(players[i]));  currentRoom->addPlayer(p); }
	hud.updateMap(currentRoom->getCoordinates());

	tileMap.SetGrid(currentRoom->getMovementZones());
	buffer = 100;
}

void NormalGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (splashScreenMode) {
		if(splashScreen!=NULL) target.draw(*splashScreen);
	}
	else {
		
		target.draw(hud,states);
		target.draw(*currentRoom, states);
		target.draw(items);
		//draw players
		for (int i = 0; i < players.size(); i++)
		{
			players[0]->render(target);
			if (players.size() > 1)	players[1]->render(target);
			
		}
		target.draw(sideMenu, states);
		tileMap.render(target);
		
	}
	
}

void NormalGame::resetState() {
	timeDialation = 1;
	hud.toogleVisible(); sideMenu.toogleVisible();
	buffer = 10;
	stateChanges = sf::Vector2u(1,0);
	splashScreenMode = false;
}



int NormalGame::doorsCheck()
{
	for (auto p : players) {
		if (p->getGridPosition(90).x == 8 && p->getGridPosition(90).y == 1) return 0;
		if(p->getGridPosition(90).x == 8 && p->getGridPosition(90).y == 9) return 1;
		if(p->getGridPosition(90).x == 1  && p->getGridPosition(90).y == 5) return 2;
		if(p->getGridPosition(90).x == 15 && p->getGridPosition(90).y ==5 ) return 3;
	}
	return -1; //if  no player goes through doors
}

void NormalGame::incrementLevel() {
	if (currentLevelNumber < numberOfLevels - 1) {
		currentLevelNumber++; currentLevel = std::make_shared<Level>(levels[currentLevelNumber]);
		currentLevel->generateInsides();
		currentRoom = currentLevel->getCurrent();
		hud.incrementLevel(currentRoom->getCoordinates(),currentLevel->getDoorStrings(), currentLevel->getRoomTypes());
		items.addChestsToManager(currentRoom->getChests());
		items.updateRoom(currentRoom);

		currentRoom->setHasBeenCleared(true);
		tileMap.SetGrid(currentRoom->getMovementZones());
		buffer = 100;
		followingCreatures = currentRoom->getVampires();
		RestCreatures = currentRoom->getRest();
	

		for (auto p : players) { p->setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset().x, Universals::WindowManager::getMiddleOfScreenWithOffset().y); }

	}
}

void NormalGame::handleUseOfUsableItems()
{
	std::shared_ptr<UsableItem> usableItem = NULL;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && buffer == 0) {
		buffer = 20;  usableItem = items.useItem(0, 0);
		if (usableItem != NULL && buffer == 20) {
			for (int i = 0; i < usableItem->getEffects().size(); i++) {
				std::string effectTemp = usableItem->getEffects()[i];
				if (effectTemp == "dialateTime") { temporaryEffects.dialateTimeByPercentage(usableItem->getPowerOfEffects()[i], usableItem->getTimeItLastInSeconds(i)); continue;}
				if (effectTemp == "clear") { currentRoom->clear(); continue; }
			}
		}
	}
	if (players.size() > 1)
	{
		//same for player 2
	}

	//efect the game if an item was used
}