#pragma once
#include "Play.h"	
#include <vector>
#include <iostream>
#include <fstream>
enum tileTypes
{
	START,
	END,
	WALL,
	PATH
};
class Tile
{
private:
	
public:
	int width;
	std::vector<tileTypes> tiles;
};

