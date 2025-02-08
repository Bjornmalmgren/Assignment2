#pragma once
#include "Tile.h"
class Greedy
{
public:
	Tile* endTile;
	Tile* startTile;
	std::vector<Tile*> tilesTraversed;
	std::map<int, Tile*> deadEnd;
	bool endReached = false;
	int GetDistance(Tile* currentCell, Tile* end);
	void TraversMap();
	bool IsInTraversed(Tile* cTile);
};

