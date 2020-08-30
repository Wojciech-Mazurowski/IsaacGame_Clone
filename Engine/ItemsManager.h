#pragma once
#include "Player1.h"
#include "Player2.h"
#include "Room.h"
#include "Chest.h"

class ItemsManager: public sf::Drawable
{
protected:

	std::vector<std::shared_ptr<Item>> itemsOnTheFloor;
	std::vector<std::shared_ptr<Player>> players; //hold pointers to all the players currently in game
	std::vector<std::vector<std::shared_ptr<UsableItem>>> usableItems; //holds all the usable items for all the players
	std::vector<std::vector<std::shared_ptr<StaticItem>>> staticItems; //holds all the static items for all the players
	std::vector<std::shared_ptr<Chest>> chests; //holds reference to all the chests in the room
	std::shared_ptr<Room> currentRoom;

public:
	ItemsManager();
	~ItemsManager();

	void addCurrentRoom(std::shared_ptr<Room> currentRoom);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
	void moveItemTowardsThePlayerIfHeIsCloseEnough(int itemIndex, float deltaTime);
	void checkIfTheItemShouldBePickedUp(int itemIndex);
	void checkIfAChestShouldBeOpened(int chestIndex);
	void printItemsInTheRoom();
	void printItemsInTheChests();
	void playerPickUpItem(int playerIndex, int itemIndex);
	std::shared_ptr<Item> getRandomItem();


	void addPlayer(std::shared_ptr<Player> p);
	void updateRoom(std::shared_ptr<Room> currentRoom);


	void addItem(std::shared_ptr<UsableItem> item, int playerIndex);
	void addItem(std::shared_ptr<StaticItem> item, int playerIndex);
	void addItem(std::shared_ptr<Item> item, int playerIndex);

	void dropUsableItem(int index, int playerIndex);
	void updateStatistics(int playerIndex);
	std::shared_ptr<UsableItem> useItem(int itemIndex, int playerIndex);


	void addChestsToManager(std::vector<std::shared_ptr<Chest>> chestsToAdd);
	void addAChestToManager(std::shared_ptr<Chest> chestsToAdd);
	void addItemsToTheFloor(std::vector<std::shared_ptr<Item>> itemsToAdd, bool launchThemForward);
	void fillAllChestsWithRandomItems();
	void fillAChestWithRandomItems(int chestIndex);
	void launchForward(std::shared_ptr<Item> item);
	void openChest(int chestIndex);

	void dropRandomItem(sf::Vector2f position);
};

