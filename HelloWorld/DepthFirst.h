#pragma once
#include <vector>
#include <map>
#include "Tile.h"
class DepthFirst
{
public:
	std::vector<Tile*> traversedList;
	std::map<int,Tile*> toTravers;
	std::map<int, Tile*> deadEnd;
	Tile* endTile;
	Tile* startTile;
	bool foundEnd = false;
	void TraversMap();
	bool IsInTraversed(Tile* cTile);
	void AddNeigboursToTravers(Tile* cTile);
	bool IsANeigbour(Tile* cTile, int id);
};

