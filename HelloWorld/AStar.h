#pragma once
#include "Tile.h"
#include <map>
class AStar
{
public:
	std::map<int, Tile*> openList;
	std::map<int, Tile*> closedList;
	Tile currentcell;
	int CalculateDistValue(Tile* currentCell, Tile* end);
	bool IsDestination(Tile* currentCell, Tile end);
	void AStarAlgorithm(Tile end);
};

