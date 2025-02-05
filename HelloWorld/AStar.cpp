#include "AStar.h"
double AStar::CalculateHValue(Tile* currentCell, Tile end) {
	double dx = abs(currentCell->getX() - end.getX());
	double dy = abs(currentCell->getY() - end.getY());
	int t = (1 * (dx + dy) + (sqrt(2) - 2 * 1) * std::min(dx, dy));
	if (t < 0) {
		t = 0;
	}
	return t;
}

double AStar::CalculateGValue(Tile* currentCell) {
	bool isTrue = true;
	int g = 0;
	Tile* cTile = currentCell;
	while (isTrue) {
		Tile* TEMP = currentCell;
		if (currentCell->owner != nullptr) {
			cTile = currentCell->owner;
			if (TEMP->id + 1 == cTile->id || TEMP->id - 1 == cTile->id || TEMP->id + TEMP->width == cTile->id || TEMP->id - TEMP->width == cTile->id) {
				g += 10;
			}
			else {
				g += 14;
			}
		}
		else
		{
			//reached start
			isTrue = false;
		}
		
		
	}
	return g;
}

bool AStar::IsDestination(Tile* currentCell, Tile end) {
	if (currentCell->getX() == end.getX() && currentCell->getY() == end.getY()) {
		return true;
	}
	else
	{
		return false;
	}
}

bool AStar::AStarAlgorithm(Tile end) {
	Tile* cTile = &currentcell;
	for (auto a : openList)
	{
		if (a.second->h == 0 && a.second->g == 0) {
			a.second->h = CalculateHValue(a.second, end);
			a.second->g = CalculateGValue(a.second);
			a.second->f = a.second->h + a.second->g;
		}
		
	}
	for (auto a : openList)
	{
		if (cTile->f == 0) {
			cTile = a.second;
		}
		else if (cTile->f > a.second->f) {
			cTile = a.second;
		}
	}
	openList.erase(cTile->id);
	closedList[cTile->id] = cTile;
	if (cTile->getX() == end.getX() || cTile->getY() == end.getY()) {
		return true;
	}
	for (int i = 0; i < cTile->neighbours.size(); i++)
	{
		auto it = closedList.find(cTile->neighbours[i]->id);
		
		if (cTile->neighbours[i]->type == WALL || it != closedList.end()) {
			
		}
		else
		{
			double g;

			if (cTile->neighbours[i]->owner != nullptr) {
				Tile* temp = cTile->neighbours[i]->owner;
				cTile->neighbours[i]->owner = cTile;
				g = CalculateGValue(cTile->neighbours[i]);
				cTile->neighbours[i]->owner = temp;
			}
			auto its = openList.find(cTile->neighbours[i]->id);
			if (its != openList.end() || cTile->neighbours[i]->f <= 0 || cTile->neighbours[i]->g > g) {
				cTile->neighbours[i]->owner = cTile;
				openList[i]->h = CalculateHValue(openList[i], end);
				openList[i]->g = CalculateGValue(openList[i]);
				openList[i]->f = openList[i]->h + openList[i]->g;
				if (it->first != cTile->neighbours[i]->id) {
					openList[cTile->neighbours[i]->id] = cTile->neighbours[i];
				}
			}
		}
		
	}
	
}