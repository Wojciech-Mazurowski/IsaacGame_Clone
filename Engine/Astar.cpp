#include "pch.h"
#include "Astar.h"

using namespace std;
using namespace sf;



float Astar::dist_between(mappableVector2I a, mappableVector2I b)
{
	int x = a.x - b.x;
	int y = a.y - b.y;

	return (float)sqrt(x * x + y * y);
}

std::list<Vector2i> Astar::reconstruct_path(std::map<mappableVector2I, mappableVector2I> cameFrom, mappableVector2I current)
{
	std::list<Vector2i> total_path;
	sf::Vector2i Converted_current;
	Converted_current.x = current.x;
	Converted_current.y = current.y;

	total_path.push_back(Converted_current);

	while (cameFrom.find(Converted_current) != cameFrom.end())
	{
		current = cameFrom[Converted_current];
		Converted_current.x = current.x;
		Converted_current.y = current.y;
		total_path.push_back(Converted_current);
	}

	return total_path;
}





bool Astar::IsPassable(mappableVector2I tile)
{
	if (tile.x < 0 || tile.x >= 15 || tile.y < 0 || tile.y >= 7)
		return false;

	// TODO check arena for wall @ tile

	return true;
}

mappableVector2I Astar::GetLowestFscore(set<mappableVector2I> openSet, map<mappableVector2I, float> fScore)
{
	mappableVector2I lowest(-1, -1);
	float lowScore = FLT_MAX;
	//foreach(var v in openSet)
	for (auto &v : openSet)
	{

		if (fScore.find(v) != fScore.end())
		{

			float score = fScore[v]; //TryGetValue(v, out float score) && score < lowScore)
			if (score < lowScore)
			{
				lowest = v;
				lowScore = score;
			}
		}
	}

	return lowest;
}


std::list<Vector2i> Astar::A_Star(Vector2i start, Vector2i goal, vector<vector<int>> grid)
{


	std::set<mappableVector2I> closedSet;

	std::set<mappableVector2I> openSet;
	openSet.insert(start);


	std::map<mappableVector2I, mappableVector2I> cameFrom;


	map<mappableVector2I, float> gScore;

	
	gScore[start] = 0;


	map<mappableVector2I, float> fScore;

	
	fScore[start] = dist_between(start, goal);

	while (openSet.size() > 0)
	{

		mappableVector2I current = GetLowestFscore(openSet, fScore);
		if (current == goal)
			return reconstruct_path(cameFrom, current);

		openSet.erase(current);
		closedSet.insert(current);

		for (int offset_x = -1; offset_x <= 1; offset_x++)
			for (int offset_y = -1; offset_y <= 1; offset_y++)
			{

				mappableVector2I neighbor(current.x + offset_x,
					current.y + offset_y);



				if (neighbor == current)
					continue;   

				if (!(MapCollision::IsPassable(neighbor.x, neighbor.y, grid)))
					continue;  

				if (closedSet.find(neighbor) != closedSet.end())
					continue;   

		
				float tentative_gScore = gScore[current] + dist_between(current, neighbor);
				auto OpenFind = openSet.find(neighbor);
				auto OpenEnd = openSet.end();
				if (!(OpenFind != OpenEnd))    
					openSet.insert(neighbor);
				else if (tentative_gScore >= gScore[neighbor])
					continue;

				
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentative_gScore;
				fScore[neighbor] = gScore[neighbor] + dist_between(neighbor, goal);
			}
	}
	std::list<Vector2i> empty;
	return empty;
}