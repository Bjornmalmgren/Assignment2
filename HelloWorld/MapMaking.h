#pragma once
#include "Tile.h"
using namespace std;
class MapMaking
{
public:
	Tile startTile;
	Tile endTile;
	
	std::vector<Tile> tiles;
	void MakeMap(std::string);
};

