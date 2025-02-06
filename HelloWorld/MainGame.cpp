#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MapMaking.h"
#include "AStar.h"
#include "Timer.h"
#include <sstream>
int DISPLAY_WIDTH = 1240;
int DISPLAY_HEIGHT = 640;
int DISPLAY_SCALE = 2;
Play::Vector2D startRect = Play::Vector2D(20,20);
Play::Vector2D startPosition = Play::Vector2D(20, 20);
bool firstTime = true;
int row = 0;
bool endFound1 = false;
bool endFound2 = false;
bool endFound3 = false;
MapMaking map1;
MapMaking map2;
MapMaking map3;
AStar a1;
AStar a2;
AStar a3;
Timer t1;
Timer t2;
Timer t3;

void DrawMap(MapMaking* map, Play::Vector2D original) {
	startRect = Play::Vector2D(startRect.x+ map->tiles[0].width * map->tiles[0].rectangleSize, startPosition.y);
	for (size_t i = map->tiles.size()-1; i > 0; i--)
	{ 
		if (map->tiles[i].id == 54 || map->tiles[i].id == 79) {
			int t1 = 2;
		}
		int t = i + 1;
		if (t % (map->tiles[i].width) == 0) {
			startRect.y += map->tiles[i].rectangleSize;
			startRect.x = original.x + map->tiles[i].width * map->tiles[0].rectangleSize;
		}
		switch (map->tiles[i].type)
		{

		case WALL:
			Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cRed, true);
			startRect.x -= map->tiles[i].rectangleSize;

			break;
		case PATH:
			Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cBlack, true);
			startRect.x -= map->tiles[i].rectangleSize;

			break;
		case START:
			
			Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cWhite, true);
			startRect.x -= map->tiles[i].rectangleSize;

			break;
		case END:
			
			Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cGreen, true);
			startRect.x -= map->tiles[i].rectangleSize;


			break;
		default:
			break;
		}
		if (firstTime == true) {
			
			map->tiles[i].position.push_back(startRect.x + 20);
			map->tiles[i].position.push_back(startRect.y + 10);
			if (map->tiles[i].type == START) {
				map->startTile = map->tiles[i];
			}else if (map->tiles[i].type == END) {
				map->endTile = map->tiles[i];
			}
		}
		if (i == 1) {
			switch (map->tiles[0].type)
			{

			case WALL:
				Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cRed, true);
				startRect.x -= map->tiles[i].rectangleSize;

				break;
			case PATH:
				Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cWhite, true);
				startRect.x -= map->tiles[i].rectangleSize;

				break;
			case START:
				Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cYellow, true);
				startRect.x -= map->tiles[i].rectangleSize;

				break;
			case END:
				Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cGreen, true);
				startRect.x -= map->tiles[i].rectangleSize;


				break;
			default:
				break;
			}
			if (firstTime == true) {
				map->tiles[0].position.push_back((startRect.x +20));
				map->tiles[0].position.push_back(startRect.y + 10);
			}
		}

	}
	
}

void DrawPath(AStar a, Tile* end, Timer timer, Play::Point2D pos) {
	bool ownerFound = true;

	

	timer.startTimer();
	a.AStarAlgorithm(*end);
	timer.stopTimer();
	std::string s = std::to_string(timer.time) +  " microsec";
	Play::DrawDebugText(pos, s.c_str());

	Tile* t = prev(a.closedList.end())->second;
	for (auto as : a.closedList)
	{
		Play::Point2D pos1 = Play::Vector2D(as.second->position[0] - 9, as.second->position[1] - 9);

		Play::Point2D pos2 = Play::Vector2D(as.second->position[0] - 1, as.second->position[1] - 1);
		Play::DrawRect(pos1, pos2, Play::cBlue, true);
		//t = as;

	}
	for (auto as : a.openList)
	{
		Play::Point2D pos1 = Play::Vector2D(as.second->position[0] - 9, as.second->position[1] - 9);

		Play::Point2D pos2 = Play::Vector2D(as.second->position[0] - 1, as.second->position[1] - 1);
		Play::DrawRect(pos1, pos2, Play::cGrey, true);
		//t = as;

	}
	while (ownerFound)
	{
		Play::Point2D pos1 = Play::Vector2D(t->position[0] - 9, t->position[1] - 9);

		Play::Point2D pos2 = Play::Vector2D(t->position[0] - 1, t->position[1] - 1);
		Play::DrawRect(pos1, pos2, Play::cYellow, true);
		if (t->owner != NULL) {
			t = t->owner;
		}
		else
		{
			ownerFound = false;
		}
	}
}



void PaintNeighbours(MapMaking* map) {
	/*int i = 58;
	for (int j = 0; j < map->tiles[i].neighbours.size(); j++)
	{
		if (map->tiles[i].neighbours[j]->type != WALL && map->tiles[i].type != WALL) {
			Play::Vector2D start = Play::Vector2D(map->tiles[i].position[0] - 5, map->tiles[i].position[1] - 5);

			Play::Vector2D end = Play::Vector2D(map->tiles[i].neighbours[j]->position[0] - 5, map->tiles[i].neighbours[j]->position[1] - 5);

			Play::DrawLine(start, end, Play::cBlack);
		}

	}*/

	for (int i = 0; i < map->tiles.size(); i++)
	{
		for (int j = 0; j < map->tiles[i].neighbours.size(); j++)
		{
			if (map->tiles[i].neighbours[j]->type != WALL && map->tiles[i].type != WALL) {
				Play::Vector2D start = Play::Vector2D(map->tiles[i].position[0]-5, map->tiles[i].position[1]-5);

				Play::Vector2D end = Play::Vector2D(map->tiles[i].neighbours[j]->position[0]-5, map->tiles[i].neighbours[j]->position[1]-5);

				Play::DrawLine(start, end, Play::cBlack);
			}
			
		}
		
	}
}



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	map1.MakeMap("../Maps/Map1.txt");
	
	
	map2.MakeMap("../Maps/Map2.txt");
	map3.MakeMap("../Maps/Map3.txt");
	a1.openList.insert(pair<int, Tile*>(map1.startTile.id, &map1.startTile));
	a2.openList.insert(pair<int, Tile*>(map2.startTile.id, &map2.startTile));
	a3.openList.insert(pair<int, Tile*>(map3.startTile.id, &map3.startTile));
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer(cBlack);
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Hello World!" );
	
	DrawMap(&map1,startRect);

	//startRect = startPosition;
	startRect = Play::Vector2D(startPosition.x +10 + map1.tiles[0].width * map1.tiles[0].rectangleSize, startPosition.y);
	DrawMap(&map2,startRect);
	startRect = startPosition;
	startRect = Play::Vector2D(60 + map1.tiles[0].width * map1.tiles[0].rectangleSize + map2.tiles[0].width * map2.tiles[0].rectangleSize, startPosition.y);
	Play::Vector2D o = startRect;
	DrawMap(&map3, o);
	if (firstTime == true) {
		firstTime = false;
		a1.currentcell = map1.startTile;
		
		a2.currentcell = map2.startTile;
		a3.currentcell = map3.startTile;
	}
	

	//debug neighbours
	/*PaintNeighbours(&map1);
	PaintNeighbours(&map2);
	PaintNeighbours(&map3);*/
	

	DrawPath(a1,&map1.endTile,t1, Play::Point2D(75, 200));
	
	DrawPath(a2,&map2.endTile,t2, Play::Point2D(245, 200));
	
	DrawPath(a3,&map3.endTile,t3, Play::Point2D(435, 290));
	
	
	Play::PresentDrawingBuffer();
	startRect = startPosition;
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}





