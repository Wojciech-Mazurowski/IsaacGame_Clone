#pragma once
#include "Room.h"
class BossRoom : public Room
{
private:
public:

	BossRoom();
	BossRoom(std::string doors);
	BossRoom(Room room);
	BossRoom(const BossRoom& room);
	~BossRoom();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void generateInsides();
	virtual void update(float deltaTime);
	virtual int  getRoomType();

	static std::string modifyDoors(std::string doors);


	void setRandomBoss();
};

