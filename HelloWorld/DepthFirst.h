#pragma once
#include <vector>
#include <map>
#include "Tile.h"
enum directions {
	UP = 0,
	UPRIGHT = 1,
	RIGHT = 2,
	DOWNRIGHT = 3,
	DOWN = 4,
	DOWNLEFT = 5,
	LEFT = 6,
	LEFTUP = 7,
};
class DepthFirst
{
public:
	std::vector<Tile*> traversedList;
	std::map<int,Tile*> toTravers;
	std::map<int, Tile*> deadEnd;
	std::vector<directions> dir;
	Tile* endTile;
	Tile* startTile;
	bool foundEnd = false;
	void TraversMap();
	bool IsInTraversed(Tile* cTile);
	void AddNeigboursToTravers(Tile* cTile);
	bool IsANeigbour(Tile* cTile, int id);
};

