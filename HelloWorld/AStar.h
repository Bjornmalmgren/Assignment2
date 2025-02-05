#pragma once
#include "Tile.h"
#include <map>
class AStar
{
public:
	std::map<int, Tile*> openList;
	std::map<int, Tile*> closedList;
	Tile currentcell;
	double CalculateHValue(Tile* currentCell, Tile end);
	double CalculateGValue(Tile* currentCell);
	bool IsDestination(Tile* currentCell, Tile end);
	bool AStarAlgorithm(Tile end);
};

