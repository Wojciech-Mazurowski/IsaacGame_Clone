#include "pch.h"
#include "ItemsManager.h"


std::shared_ptr<Item> ItemsManager::getRandomItem()
{
	int randomChoice = Universals::getRandom(0, 6);
	switch (randomChoice)
	{
	case 0: return 	std::make_shared<StaticItem>(Universals::TextureManager::getTexture("fastGlasses"), sf::Vector2f{ 0,0 }, "fastGlasses", std::vector<std::string>{"increaseAcceleration"}, std::vector<float>{1000.0}, false);
	case 1: return 	std::make_shared<StaticItem>(Universals::TextureManager::getTexture("hoodCap"), sf::Vector2f{ 0,0 }, "czapkaUliczna", std::vector<std::string>{"increaseDmg"}, std::vector<float>{10.0}, false);
	case 2: return 	std::make_shared<StaticItem>(Universals::TextureManager::getTexture("grasper"), sf::Vector2f{ 0,0 }, "grasper", std::vector<std::string>{"increasePickUpRange"}, std::vector<float>{20.0}, false);
	case 3: return 	std::make_shared<StaticItem>(Universals::TextureManager::getTexture("bar"), sf::Vector2f{ 0,0 }, "bar", std::vector<std::string>{"increaseHP"}, std::vector<float>{0.5}, false);
	case 4: return 	std::make_shared<UsableItem>(Universals::TextureManager::getTexture("stopWatch"), sf::Vector2f{ 0,0 }, "stopTheWatchWatch", std::vector<std::string>{"dialateTime"}, std::vector<float>{0.5}, std::vector<float>{5});
	case 5: return 	std::make_shared<UsableItem>(Universals::TextureManager::getTexture("snapper"), sf::Vector2f{ 0,0 }, "snapper", std::vector<std::string>{"clear", "dialateTime"}, std::vector<float>{0.0,0.3}, std::vector<float>{0,1});
	default: return NULL;
	}
	return NULL;
}


void ItemsManager::addCurrentRoom(std::shared_ptr<Room> currentRoom){ this->currentRoom = currentRoom;}



ItemsManager::ItemsManager()
{
	usableItems.resize(2);
	staticItems.resize(2);
}


ItemsManager::~ItemsManager()
{
}

void ItemsManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < itemsOnTheFloor.size();i++) {
		if (itemsOnTheFloor[i]->getIsOnTheMap()) target.draw(*itemsOnTheFloor[i]);
	}
}

void ItemsManager::update(float deltaTime)
{
	for (int i = 0; i < itemsOnTheFloor.size(); i++) {
		if (itemsOnTheFloor[i]->getIsOnTheMap()) {
			itemsOnTheFloor[i]->update(deltaTime);
			if (itemsOnTheFloor[i]->getCanBePickedUp()) {
				moveItemTowardsThePlayerIfHeIsCloseEnough(i, deltaTime);
				checkIfTheItemShouldBePickedUp(i);
			}
		}
	}

	for (int i = 0; i < chests.size(); i++) {
		if(!chests[i]->getIsOpen()){ checkIfAChestShouldBeOpened(i); }
		if (chests[i]->getIsDoneOpening() && !chests[i]->isEmpty()) { addItemsToTheFloor(chests[i]->getItems(),true); chests[i]->clear(); }
	}
}



void ItemsManager::checkIfTheItemShouldBePickedUp(int itemIndex){
		for (int i = 0; i < players.size(); i++) {
			int distanceX = 1000;
			int distanceY = 1000;
			distanceX= abs(itemsOnTheFloor[itemIndex]->getPosition().x - players[i]->getPosition().x); 
			distanceY = abs(itemsOnTheFloor[itemIndex]->getPosition().y - players[i]->getPosition().y); 

			if (distanceX <= 10 && distanceY <= 10) { //if the player is within a small enough radius of the item
			//  std::cout << "dystans:" << distanceX << "," << distanceY;
			  playerPickUpItem(i, itemIndex); 
			  break; //so that if one player already picked it up the other can't
			}
		}
	
}

void ItemsManager::checkIfAChestShouldBeOpened(int chestIndex)
{
	for (auto p : players) {
		int distanceX = abs(chests[chestIndex]->getPosition().x - p->getPosition().x);
		int distanceY = abs(chests[chestIndex]->getPosition().y - p->getPosition().y);
		
		if (distanceX<= p->getPickUpRange()+10 && distanceY <= p->getPickUpRange()+10) { //if the player is within a small enough radious of the chest
			//std::cout << "\nOTWARI" << distanceX << "," << distanceY;
			openChest(chestIndex);
		}
	}

}

void ItemsManager::moveItemTowardsThePlayerIfHeIsCloseEnough(int itemIndex, float deltaTime) {
	//find out which player is closer to the item
	int closerIndex = 0;
	int distanceX = abs(itemsOnTheFloor[itemIndex]->getPosition().x - players[0]->getPosition().x);
	int distanceY = abs(itemsOnTheFloor[itemIndex]->getPosition().y - players[0]->getPosition().y);

	if (players.size()!=1) {
		int distanceXp2 = abs(itemsOnTheFloor[itemIndex]->getPosition().x - players[1]->getPosition().x);
		int distanceYp2 = abs(itemsOnTheFloor[itemIndex]->getPosition().y - players[1]->getPosition().y);

		if (distanceXp2+distanceYp2<distanceX+distanceY) { 
			distanceX = distanceXp2;
			distanceY = distanceYp2;
			closerIndex = 1; 
		}
	}

	if (distanceX <= players[closerIndex]->getPickUpRange() && distanceY <= players[closerIndex]->getPickUpRange()) { //if the item is in the playe's pick up range
		if (itemsOnTheFloor[itemIndex]->getPosition().x - players[closerIndex]->getPosition().x < 0) { itemsOnTheFloor[itemIndex]->move(sf::Vector2f{ (float)(distanceX / 6)+5,0 }); } //move to the right
		else { itemsOnTheFloor[itemIndex]->move(sf::Vector2f{ (float)-(distanceX / 6)-5,0 }); } //or move to the left

		if (itemsOnTheFloor[itemIndex]->getPosition().y - players[closerIndex]->getPosition().y < 0) { itemsOnTheFloor[itemIndex]->move(sf::Vector2f{ 0,(float)(distanceY / 6)+5 }); } //movedown
		else { itemsOnTheFloor[itemIndex]->move(sf::Vector2f{ 0,(float)-(distanceY / 6)-5 }); } //or move up
	}
	
			
	
}

void ItemsManager::printItemsInTheRoom() {
	std::cout << "\nITEMKI\n";
	for (auto e : itemsOnTheFloor) {
		std::cout << "\n" << e->getName() << " " << e->getPosition().x << "," << e->getPosition().y <<"is on the map? "<<e->getIsOnTheMap();
	}
	std::cout << "\n";
}

void ItemsManager::printItemsInTheChests()
{
	std::cout << "\nITEMKI W CHESTACH\n";
	for (auto c : chests) {
		for (auto e : c->getItems()) {
			std::cout <<"\n"<< e->getName() << " "<<e->getPosition().x << ","<<e->getPosition().y;
		}
	}

	std::cout << "\n";
}

void ItemsManager::playerPickUpItem(int playerIndex, int itemIndex)
{
	if (itemsOnTheFloor[itemIndex]->getCanBePickedUp()) {
		itemsOnTheFloor[itemIndex]->setIsOnTheMap(false);
		addItem(itemsOnTheFloor[itemIndex],playerIndex);
		itemsOnTheFloor.erase(itemsOnTheFloor.begin() + itemIndex);
	}
}



void ItemsManager::addPlayer(std::shared_ptr<Player> p){ players.push_back(p);}

void ItemsManager::updateRoom(std::shared_ptr<Room> currentRoom){ 
	this->currentRoom->storeItems(itemsOnTheFloor);
	itemsOnTheFloor.clear();
	this->currentRoom = currentRoom;
	addItemsToTheFloor(this->currentRoom->getItems(),false);
}


void ItemsManager::addItem(std::shared_ptr<UsableItem> item, int playerIndex)
{
	
	if (usableItems[playerIndex].size() < players[playerIndex]->getmaxUsableItems()) { usableItems[playerIndex].push_back(item); }
	else {usableItems[playerIndex].push_back(item);  dropUsableItem(0, playerIndex);}
}

void ItemsManager::addItem(std::shared_ptr<StaticItem> item, int playerIndex) {

	if (staticItems[playerIndex].size()<players[playerIndex]->getmaxStaticItems()) { staticItems[playerIndex].push_back(item); this->updateStatistics(playerIndex); }
}

void ItemsManager::addItem(std::shared_ptr<Item> item, int playerIndex) {
	
	if (!item->getType()) { addItem(std::static_pointer_cast<StaticItem>(item),playerIndex); }
	else { addItem(std::static_pointer_cast<UsableItem>(item),playerIndex); }
}

void ItemsManager::dropUsableItem(int index, int playerIndex) {
	if (usableItems[playerIndex].size() > index) {
		usableItems[playerIndex][index]->setPosition(players[playerIndex]->getPosition());
		usableItems[playerIndex][index]->setIsOnTheMap(true);
		usableItems[playerIndex][index]->lungeForward();
		usableItems[playerIndex][index]->setCanBePickedUp(false);
		usableItems[playerIndex][index]->canBePickedUpIn(3);
		itemsOnTheFloor.push_back(usableItems[playerIndex][index]);
		usableItems[playerIndex].erase(usableItems[playerIndex].begin() + index);
	}
}



void ItemsManager::updateStatistics(int playerIndex) {//udpates the players's statistics by the bufs of the last item in his inventory
	if (staticItems[playerIndex].size() > 0) {
		for (int i = 0; i < staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getEffects().size(); i++) {
			std::string tempEffect = staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getEffects()[i];
			if (tempEffect == "increaseDmg") { players[playerIndex]->increaseDmg(staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getPowerOfEffects()[i]); continue; }
			if (tempEffect == "increaseAcceleration") { players[playerIndex]->increaseAcceleration(staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getPowerOfEffects()[i]); continue; }
			if (tempEffect == "increaseHP") { players[playerIndex]->increaseHP(staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getPowerOfEffects()[i]); continue; }
			if (tempEffect == "increaseAttackSpeed") { players[playerIndex]->increaseAttackSpeed(staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getPowerOfEffects()[i]); continue; }
			if (tempEffect == "increasePickUpRange") { players[playerIndex]->increasePickUpRange(staticItems[playerIndex][staticItems[playerIndex].size() - 1]->getPowerOfEffects()[i]); continue; }
		}
	}
}


std::shared_ptr<UsableItem> ItemsManager::useItem(int itemIndex, int playerIndex) {
	if (itemIndex < usableItems[playerIndex].size()) {
		if (!usableItems[playerIndex][itemIndex]->getHasBeenUsed()) {
			std::shared_ptr<UsableItem> tempUsable = usableItems[playerIndex][itemIndex];
			usableItems[playerIndex].erase(usableItems[playerIndex].begin() + itemIndex);
			return tempUsable;
		}
	}
	return NULL; //if the item cannot be used
}

void ItemsManager::addChestsToManager(std::vector<std::shared_ptr<Chest>> chestsToAdd){
	chests.clear(); //clears currently held chests in the manager
	for (int i = 0; i < chestsToAdd.size();i++) { 
		chests.push_back(chestsToAdd[i]);
	}
	fillAllChestsWithRandomItems(); 
}

void ItemsManager::addAChestToManager(std::shared_ptr<Chest> chestsToAdd) { this->chests.push_back(chestsToAdd); }

void ItemsManager::addItemsToTheFloor(std::vector<std::shared_ptr<Item>> itemsToAdd, bool launchThemForward)
{
	for (int i = 0; i < itemsToAdd.size();i++) {
		if(launchThemForward) launchForward(itemsToAdd[i]);
		this->itemsOnTheFloor.push_back(itemsToAdd[i]);
	}
}

void ItemsManager::fillAllChestsWithRandomItems()
{
	for (int i = 0; i < chests.size();i++) {
		if (!chests[i]->getIsOpen() && chests[i]->isEmpty()) { fillAChestWithRandomItems(i); }
	}
}

void ItemsManager::fillAChestWithRandomItems(int chestIndex)
{
	int howManyItems = Universals::getRandom(1,3); //fil with up to three items
	for (int i = 0; i < howManyItems; i++) {
		chests[chestIndex]->addItem(getRandomItem());
	}
	
}


void ItemsManager::launchForward(std::shared_ptr<Item> item) {
	item->lungeForward();
	item->canBePickedUpIn(1);
}

void ItemsManager::openChest(int chestIndex)
{
	chests[chestIndex]->open();	
}

void ItemsManager::dropRandomItem(sf::Vector2f position)
{
	std::shared_ptr<Item> itemtemp= getRandomItem();
	itemtemp->setPosition(position);
	itemtemp->setIsOnTheMap(true);
	itemtemp->canBePickedUpIn(1);
	itemsOnTheFloor.push_back(itemtemp);
}
