#include "DepthFirst.h"
void DepthFirst::TraversMap() {
	bool endReached = false;
	Tile* cTile = traversedList.back();
	std::map<int,int> directions;
	


	while (endReached == false)
	{
		if (traversedList.empty() == false) {
			cTile = traversedList.back();
		}
		directions[cTile->id + cTile->width] = 0;
		directions[cTile->id + cTile->width + 1] = 1;
		directions[cTile->id + 1] = 2;
		directions[cTile->id - cTile->width + 1] = 3;
		directions[cTile->id - cTile->width] = 4;
		directions[cTile->id - cTile->width - 1] = 5;
		directions[cTile->id - 1] = 6;
		directions[cTile->id + cTile->width - 1] = 7;
		std::map<int, Tile*> dirId;

		AddNeigboursToTravers(cTile);
		if (cTile->type == END) {
			endReached = true;
		}
		else
		{
			for (auto tile : toTravers)
			{
				for (auto t : directions)
				{
					if (t.first == tile.second->id && IsANeigbour(cTile, tile.second->id) == true) {
						dirId.insert(std::pair(t.second, tile.second));
						break;
					}

				}




			}
			int j = 10;
			Tile* newTraversall = NULL;
			for (auto t : dirId)
			{
				if (t.first < j)
				{
					j = t.first;
					newTraversall = t.second;
				}
			}
			if (newTraversall != NULL) {
				newTraversall->owner = cTile;
				traversedList.push_back(newTraversall);
				toTravers.erase(newTraversall->id);
			}
			if (traversedList.back()->id == cTile->id) {
				deadEnd.insert(std::pair(cTile->id, cTile));
				traversedList.pop_back();
			}

			
		}
		
	}
	
	
}

bool DepthFirst::IsInTraversed(Tile* cTile) {
	for (int i = 0; i < traversedList.size(); i++)
	{
		if (traversedList[i]->id == cTile->id) {
			return true;
		}
	}
	return false;
}

void  DepthFirst::AddNeigboursToTravers(Tile* cTile){
	for (int i = 0; i < cTile->neighbours.size(); i++)
	{
		if (cTile->neighbours[i]->type != WALL && IsInTraversed(cTile->neighbours[i]) == false) {
			if (deadEnd.empty() == true || deadEnd.contains(cTile->neighbours[i]->id) == false) {
				toTravers.insert(std::pair<int, Tile*>(cTile->neighbours[i]->id, cTile->neighbours[i]));
			}
			
		}
	}
}

bool  DepthFirst::IsANeigbour(Tile* cTile, int id) {
	for (int i = 0; i < cTile->neighbours.size(); i++)
	{
		if(id == cTile->neighbours[i]->id) {
			return true;
		}
	}
	return false;
}