#pragma once
#include "Object.h"
#include "StaticItem.h"
#include "UsableItem.h"

class Chest : public Object
{
	std::vector<std::shared_ptr<Item>> itemsInTheChest; //all the items stored in the chest
	bool isOpen = false; //determines if the chest is open
	bool isDoneOpening = false; //determines if th eanimation of opening has already ended
public:
	Chest(const sf::Texture* texture, const  sf::Vector2f& position);
	Chest();
	~Chest();

	virtual void update(float deltaTime);
	void setIsDoneOpening(bool b);

	void open();
	void close();

	void addItem(std::shared_ptr<Item> item);
	std::vector<std::shared_ptr<Item>> getItems();
	bool getIsOpen();
	bool getIsDoneOpening();
	void clear();
	bool isEmpty();
};

