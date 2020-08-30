#include "pch.h"
#include "NormalRoom.h"


NormalRoom::NormalRoom():Room()
{
}

NormalRoom::NormalRoom(std::string doors):Room(doors)
{
}

NormalRoom::NormalRoom(const NormalRoom& room):Room()
{
	this->yetEntered = room.yetEntered;
	this->hasBeenCleared = room.hasBeenCleared;
	this->previousDoors = room.previousDoors;
	this->coordinate = room.coordinate;
	this->isEmpty = room.isEmpty;
	this->doors = room.doors;
	this->levelNumber = room.levelNumber;
}

NormalRoom::NormalRoom(Room room) : Room(room)
{
}


NormalRoom::~NormalRoom()
{
}

std::shared_ptr<Entity> NormalRoom::getRandomMonster()
{
	
	int x = Universals::getRandom(0, 3);
		if (x>0)
		{
			return std::make_shared<EnemyWorm>(Universals::getRandom(Universals::WindowManager::getWallPosition(2), Universals::WindowManager::getWallPosition(3)),
				Universals::getRandom(Universals::WindowManager::getWallPosition(0), Universals::WindowManager::getWallPosition(1)),Universals::TextureManager::getTexture("worm"));
		}
		else 
			return std::make_shared<EnemyGhost>(Universals::getRandom(Universals::WindowManager::getWallPosition(2), Universals::WindowManager::getWallPosition(3)),
				Universals::getRandom(Universals::WindowManager::getWallPosition(0), Universals::WindowManager::getWallPosition(1)), Universals::TextureManager::getTexture("ghost"));

	
}

void NormalRoom::generateMonster(int howmany)
{
	for(int i=0;i<howmany;i++)
	this->monsters.push_back(getRandomMonster());

}

void NormalRoom::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw the floor
	target.draw(floor);
	target.draw(walls);
	for (unsigned int i = 0; i < door.size(); i++) { target.draw(door[i]); }
	
	for (auto potowry : monsters)
	{
		potowry->render(target);

	}


}
void NormalRoom::printPaths(const std::vector<std::vector<bool>>& p){
	std::cout << "\n---paths----\n";
	for (int i = 0; i < p.size(); i++) {
		for (int j = 0; j < p[i].size(); j++) {
			std::cout << p[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void NormalRoom::generateObsticles() {

	floor.generatePaths(this->getDoors()); //generates random path inside room so that despite the obsticles it can be traverlsed

	//generate holes
	int fragmentHeight = 1;
	int fragmentLenght = 6;
	int holeNumber = 3;

	floor.generateHoles(holeNumber, fragmentHeight, fragmentLenght);

	//generateDebris
	unsigned int numberOfDebris=5;
	floor.generateObsticles(numberOfDebris);

	floor.updateMovementZone();
}


void NormalRoom::generateInsides()
{
	overLay.setTexture(*Universals::TextureManager::getTexture("overlay"));
	overLay.setOrigin(overLay.getTexture()->getSize().x / 2, overLay.getTexture()->getSize().y / 2);
	overLay.setPosition(Universals::WindowManager::getMiddleOfScreenWithOffset());
	generateDoors();
	generateFlooring();
	prepareWalls();
	generateObsticles();
	generateMonster(3);
}


void NormalRoom::update(float deltaTime)
{
	if (yetEntered == false) {
		for (unsigned int i = 0; i < door.size(); i++) { door[i].close(); }
		yetEntered = true;
	}
	for (unsigned int i = 0; i < door.size(); i++) { door[i].update(deltaTime); }

	for (int i = 0; i < monsters.size();i++) {
		monsters[i]->update(deltaTime);
		if (!monsters[i]->isStillAlive()) { monsters.erase(monsters.begin() + i); break; };
	}

	
}

int NormalRoom::getRoomType()
{
	return 0;
}
