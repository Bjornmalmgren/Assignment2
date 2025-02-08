#include "Greedy.h"
int Greedy::GetDistance(Tile* currentCell, Tile* end) {
	int dx = abs(currentCell->getX() - end->getX());
	int dy = abs(currentCell->getY() - end->getY());
	if (dx > dy) {
		
		return 14 * dy + 10 * (dx - dy);
	}

	return 14 * dx + 10 * (dy - dx);
}

void Greedy::TraversMap() {
	Tile* cTile = tilesTraversed.back();
	while (endReached == false)
	{
		cTile = tilesTraversed.back();
		if (cTile->type == END) {
			endReached = true;
		}
		std::map<Tile*, int> neigburs;

		for (int i = 0; i < cTile->neighbours.size(); i++)
		{
			if (cTile->neighbours[i]->type != WALL && deadEnd.contains(cTile->neighbours[i]->id) == false && IsInTraversed(cTile->neighbours[i]) == false) {
				neigburs.insert(std::pair<Tile*, int>(cTile->neighbours[i], GetDistance(cTile->neighbours[i], endTile)));
			}
		}

		int id = -1;
		int weight;
		Tile* tile = cTile;
		for (auto t : neigburs)
		{
			if (t.first->type == END) {
				weight = t.second;
				id = t.first->id;
				tile = t.first;
				break;
			}
			if (id == -1) {
				weight = t.second;
				id = t.first->id;
				tile = t.first;
			}
			else if (weight > t.second) {
				weight = t.second;
				id = t.first->id;
				tile = t.first;
			}
			else if (weight == t.second && tile != cTile) {
				if (t.first->getY() > tile->getY()) {
					weight = t.second;
					id = t.first->id;
					tile = t.first;
				}
				else if (t.first->getX() > tile->getX()) {
					weight = t.second;
					id = t.first->id;
					tile = t.first;
				}
			}
		}

		if (id != -1) {
			tilesTraversed.push_back(tile);
		}
		if (tilesTraversed.back()->id == cTile->id) {
			deadEnd.insert(std::pair(cTile->id, cTile));
			tilesTraversed.pop_back();
		}
		
	}
	
	
}

bool Greedy::IsInTraversed(Tile* cTile) {
	for (int i = 0; i < tilesTraversed.size(); i++)
	{
		if (tilesTraversed[i]->id == cTile->id) {
			return true;
		}
	}
	return false;
}