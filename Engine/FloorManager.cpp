#include "pch.h"
#include "FloorManager.h"
#include <iostream>






std::vector<std::vector<int>> FloorManager::getMovementZone() { return movementZone;}


void FloorManager::updateMovementZone() {
	//REMEMBER TO ACCOUNT FOR THE PADDING LAYER AROUND THE ZONES
	for (int i = 0; i < holes.size(); i++) {
		sf::Vector2u temp = holes[i].getTopRightPosition();
		temp.x += 1; temp.y += 1; //padding

		std::vector<std::vector<bool>> holeZones = holes[i].getHoleZones();
		int x = 0;
		for (int z = temp.x; z <temp.x+holeZones.size(); z++) {
			int y = 0;
			for (int k = temp.y; k < temp.y +holeZones[x].size(); k++) {
				if (holeZones[x][y]) { movementZone[z][k] = 0; }
				y++;
			}
			x++;
		}
	}
	for (auto o : obsticles) {
		sf::Vector2u gridPosition = o.getGridPostion();
		movementZone[gridPosition.x+1][gridPosition.y+1] = 0;
	}

}

void FloorManager::updatePaths(bool newHolesAdded, bool newObsticlesAdded) {
	if (newHolesAdded) {
		for (int i = 0; i < holes.size(); i++) {
			sf::Vector2u temp = holes[i].getTopRightPosition();
			std::vector<std::vector<bool>> holeZones = holes[i].getHoleZones();
			int x = 0;
			for (int z = temp.x; z < temp.x + holeZones.size(); z++) {
				int y = 0;
				for (int k = temp.y; k < temp.y + holeZones[x].size(); k++) {
					if (holeZones[x][y]) { paths[z][k] = 0; }
					y++;
				}
				x++;
			}
		}
	}
	if (newObsticlesAdded) {
		for (auto o:obsticles) {
			sf::Vector2u gridPosition=o.getGridPostion();
			paths[gridPosition.x][gridPosition.y] = 0;
		}
	}

}

FloorManager::FloorManager()
{
}


FloorManager::~FloorManager()
{
}

void FloorManager::generatePaths(std::string doors) {
	std::vector<sf::Vector2u> doNotObscureSpots;
	int rows = 7;
	int columns = 13;
	//fillpaths with ones ()
	paths.resize(rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			paths[i].push_back(1);
		}
	}
	//push back all the doors

	if (doors.at(0) == '1') { //NORTH door
		sf::Vector2u doorPosition{ (unsigned)0,(unsigned)columns / 2 };
		doNotObscureSpots.push_back(doorPosition);
		//add a cone around the door so that no obsticles are generated there
		paths[doorPosition.x][doorPosition.y] = false;
		paths[doorPosition.x][doorPosition.y + 1] = false;
		paths[doorPosition.x][doorPosition.y - 1] = false;
		paths[doorPosition.x + 1][doorPosition.y] = false;
	}

	if (doors.at(1) == '1') { //south door
		sf::Vector2u doorPosition{ (unsigned)rows - 1, (unsigned)columns / 2 };
		doNotObscureSpots.push_back(doorPosition);
		paths[doorPosition.x][doorPosition.y] = false;
		paths[doorPosition.x][doorPosition.y + 1] = false;
		paths[doorPosition.x][doorPosition.y - 1] = false;
		paths[doorPosition.x - 1][doorPosition.y] = false;
	}
	if (doors.at(2) == '1') { //west door
		sf::Vector2u doorPosition{ (unsigned)rows / 2, (unsigned)0 };
		doNotObscureSpots.push_back(doorPosition);
		paths[doorPosition.x][doorPosition.y] = false;
		paths[doorPosition.x + 1][doorPosition.y] = false;
		paths[doorPosition.x - 1][doorPosition.y] = false;
		paths[doorPosition.x][doorPosition.y + 1] = false;
	}
	if (doors.at(3) == '1') {//east door
		sf::Vector2u doorPosition{ (unsigned)rows / 2, (unsigned)columns - 1 };
		doNotObscureSpots.push_back(doorPosition);
		paths[doorPosition.x][doorPosition.y] = false;
		paths[doorPosition.x + 1][doorPosition.y] = false;
		paths[doorPosition.x - 1][doorPosition.y] = false;
		paths[doorPosition.x][doorPosition.y - 1] = false;
	}

	//also add a random point somewhere near the middle of the room
	doNotObscureSpots.push_back(sf::Vector2u(Universals::getRandom(rows / 4, rows / 2), Universals::getRandom(columns / 4, columns / 2)));


	//start from the first door and make paths to all the others from it
	float drunkness = 50; //between 0 and 100 modifies the chance that the algorithm will purpusfully step in random direction
	//drunken greedy algoithm

	sf::Vector2u randomPoint = doNotObscureSpots[0];
	for (int i = 1; i < doNotObscureSpots.size(); i++)
	{
		sf::Vector2u startPoint = randomPoint;
		sf::Vector2u endPoint = doNotObscureSpots[i];
		paths[endPoint.x][endPoint.y] = false;

		while (startPoint.x != endPoint.x || startPoint.y != endPoint.y)
		{
			int chance = Universals::getRandom(1, 100);
			paths[startPoint.x][startPoint.y] = false;

			int rowsDistance = startPoint.x - endPoint.x; //rows distance
			int columnsDistance = startPoint.y - endPoint.y; //distance between columns
			int step = 0; //0 for no step 1 for step north, 2 for step south, 3 for step west, 4 for step east

			if (chance <= drunkness) { step = Universals::getRandom(0, 4); }
			else {
				if (chance % 2 == 0) {
					if (rowsDistance > 0) { step = 1; }
					if (rowsDistance < 0) { step = 2; }
				}
				else {
					if (columnsDistance > 0) { step = 3; }
					if (columnsDistance < 0) { step = 4; }
				}
			}
			switch (step) {
			case 1: if (startPoint.x > 0) { startPoint.x = startPoint.x - 1; } break;
			case 2: if (startPoint.x < rows - 1) { startPoint.x = startPoint.x + 1; }break;
			case 3: if (startPoint.y > 0) { startPoint.y = startPoint.y - 1; } break;
			case 4: if (startPoint.y < columns - 1) { startPoint.y = startPoint.y + 1; } break;
			default:  break; //if no step is to be made
			}
			if (Universals::getRandom(1, 15) == 1) { randomPoint = startPoint; }
		}

	}
}

void FloorManager::prepareMovementZone(const unsigned int& maxHeight, const unsigned int & maxWidth)
{
	movementZone.resize(maxHeight);
	for(int i = 0; i < maxHeight; i++) {
		movementZone[i].resize(maxWidth,1);
	}
}

void FloorManager::setGridTile(sf::Vector2i tileIndex, int state){ movementZone[tileIndex.x][tileIndex.y] = state;}

void FloorManager::generateFlooring(const unsigned int& maxHeight, const unsigned int & maxWidth) {
	prepareMovementZone(maxHeight, maxWidth);

	boards.resize(maxHeight);
	for (int i = 0; i < maxHeight; i++)
	{
		//get3 randomnumbers
		int rand1 = Universals::getRandom(6, 17);
		int upper = 26 - rand1;
		int rand2 = Universals::getRandom(1, 3);
		if (rand2 == 2) {
			//TWO BOARDS PER BOARD
			rand2 = upper;
			boards[i].push_back(rand1);
			boards[i].push_back(rand2);
		}
		else
		{
			int rand2 = Universals::getRandom(5, upper - 4);
			int rand3 = 26 - rand1 - rand2;
			boards[i].push_back(rand1);
			boards[i].push_back(rand2);
			boards[i].push_back(rand3);
		}
	}
	floorDetails = floor.loadBoards(Universals::PathManager::getCurrentLevelPath().append("\\middle.png"), Universals::PathManager::getCurrentLevelPath().append("ends.png"), sf::Vector2u(45, 45), boards, 14);
	floorDetails.setOrigin((45 * 26) / 2, (14 * 45) / 2);
	floorDetails.setPosition((Universals::WindowManager::getScreenWidth() / 2) + Universals::WindowManager::getOffsetValue(), Universals::WindowManager::getScreenHeight() / 2);
	floor.setOrigin((45 * 26) / 2, (14 * 45) / 2);
	floor.setPosition((Universals::WindowManager::getScreenWidth() / 2) + Universals::WindowManager::getOffsetValue(), Universals::WindowManager::getScreenHeight() / 2);
}

void FloorManager::printT(std::vector<std::vector<bool>> v) {
	std::cout << "\n";
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) {
			std::cout << v[i][j];
		}
		std::cout <<"\n";
	}
}
bool FloorManager::noHoleIntersectingWith(sf::Vector2u topRightPoint, const unsigned int & maxHeight, const unsigned int & maxWidth) {
	for (int i = 0; i < holes.size(); i++) {
		int distanceRows = abs(holes[i].getPosition().x - topRightPoint.x);
		int distanceColumns= abs(holes[i].getPosition().y - topRightPoint.y);
		if (distanceRows<maxHeight|| distanceColumns-1< maxWidth) { return false; }
	}
	return true;
}

bool FloorManager::isFragmentSuitableForAHole(sf::Vector2u topRightPoint, std::vector<std::vector<bool>> floor, const unsigned int & maxHeight, const unsigned int & maxWidth) {
	int sum = 0;
	for (int i = topRightPoint.x; i < topRightPoint.x+maxHeight; i++) {
		for (int j = topRightPoint.y; j < topRightPoint.y+maxWidth; j++) {
			if (floor[i][j]) {
				sum++; 
				if (sum > 2) { return true; }
			}
		}
	}
	return false;
}

void FloorManager::generateObsticles(unsigned int  numberOfDebris) {
	unsigned int floorWidth = paths[0].size();
	for (unsigned int i = 0; i < numberOfDebris; i++) {
		unsigned int randomRow = Universals::getRandom(1, paths.size()-2);
		unsigned int randomColumn= Universals::getRandom(1, floorWidth - 2);
		for (unsigned int i = randomColumn; i < floorWidth; i++) {
			if (paths[randomRow][i] == 1) { paths[randomRow][i] == 0;  obsticles.push_back(Obsticle(Universals::TextureManager::getTexture("obsticle1"), false, sf::Vector2u{ randomRow,i })); break; }
		}
	}
}

void FloorManager::generateHoles(unsigned int  numberOfHoles, const unsigned int & maxHeight, const unsigned int & maxWidth)
{

	for (int i = 0; i < numberOfHoles; i++) {
		//select a random floor fragment

		std::vector<std::vector<bool>> floorFragment;
		floorFragment.resize(maxHeight);

		sf::Vector2u topRightPoint{ (unsigned)Universals::getRandom(1,paths.size() - maxHeight - 1),(unsigned)Universals::getRandom(1,paths[0].size() - maxWidth - 1) };
		int fullcircleCheck = topRightPoint.y - 1;
		if (fullcircleCheck == 0) { fullcircleCheck++; }
		while (topRightPoint.y != fullcircleCheck) {
			if (noHoleIntersectingWith(topRightPoint, maxHeight, maxWidth) && isFragmentSuitableForAHole(topRightPoint, paths, maxHeight, maxWidth)) {
				//push back the fragment into the fragmentVector
				int tempX = topRightPoint.x;
				for (int z = 0; z < maxHeight; z++) {
					int tempY = topRightPoint.y;
					for (int k = 0; k < maxWidth; k++) {
						floorFragment[z].push_back(paths[tempX][tempY]);
						tempY += 1;
					}
					tempX += 1;
				}
				FloorHole newHole(floorFragment, topRightPoint, maxHeight, maxWidth);
				this->holes.push_back(newHole);
				updatePaths(true, false);
				break; //breaks the while loop
			}
			else {
				topRightPoint.y = (topRightPoint.y + 1);
				if (topRightPoint.y > paths[0].size() - maxWidth - 1) { topRightPoint.y = 1; }
			}
		}
	}
}

std::vector<FloorHole> FloorManager::getHoles() { return this->holes; }

void FloorManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(floor);
	target.draw(floorDetails);
	for (int i = 0; i < holes.size(); i++) { target.draw(holes[i]); }
	for (int i = 0; i < obsticles.size(); i++) { target.draw(obsticles[i]); }
}
