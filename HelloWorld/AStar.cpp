#include "AStar.h"
int AStar::CalculateDistValue(Tile* currentCell, Tile* end) {
	int dx = abs(currentCell->getX() - end->getX());
	int dy = abs(currentCell->getY() - end->getY());
	if (dx < dy) {
		return 14 * dx + 10 * (dy - dx);
	}

	return 14 * dy + 10 * (dx - dy);
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

void AStar::AStarAlgorithm(Tile end) {
	
	/*for (auto a : openList)
	{
		if (a.second->h == 0 && a.second->g == 0) {
			cTile->h = CalculateDistValue(cTile, end);
			cTile->f = cTile->g + cTile->h;
		}
		
	}*/
	bool isTrue = true;
	Tile* cTile = &currentcell;
	while (isTrue == true)
	{
		cTile = openList.begin()->second;
		for (auto a : openList)
		{
			if (a.second->f < cTile->f || cTile->f == a.second->f && a.second->g < cTile->g) {
				
				cTile = a.second;
				
			}


		}
		openList.erase(cTile->id);
		closedList[cTile->id] = cTile;
		if (cTile->getX() == end.getX() && cTile->getY() == end.getY()) {

			isTrue = false;
			break;
		}
		for (int i = 0; i < cTile->neighbours.size(); i++)
		{

			auto it = closedList.find(cTile->neighbours[i]->id);

			if (cTile->neighbours[i]->type != WALL && it == closedList.end()) {
				double newNeighbourCost = cTile->g + CalculateDistValue(cTile, cTile->neighbours[i]);
				auto its = openList.find(cTile->neighbours[i]->id);
				/*if (newNeighbourCost < 0) {
					newNeighbourCost *= -1;
				}*/

				if (its == openList.end() || cTile->neighbours[i]->g > newNeighbourCost) {


					cTile->neighbours[i]->g = newNeighbourCost;
					cTile->neighbours[i]->h = CalculateDistValue(cTile->neighbours[i], &end);
					cTile->neighbours[i]->f = cTile->neighbours[i]->g + cTile->neighbours[i]->h;
					cTile->neighbours[i]->owner = cTile;

					if (its == openList.end()) {
						openList[cTile->neighbours[i]->id] = cTile->neighbours[i];
					}
				}
			}
			

		}
	}
	
}