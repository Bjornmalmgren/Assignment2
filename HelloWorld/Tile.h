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
	int x;
	int y;
public:
	int id;
	int getX() { return x; }
	int getY() { return y; }
	void setX(int X) { x = X; };
	void setY(int Y) { y = Y; };
	double f, g, h;
	int width;
	tileTypes type;
	int rectangleSize = 10;
	std::vector<int> position;
	std::vector<Tile*> neighbours;
	Tile* owner;
};

