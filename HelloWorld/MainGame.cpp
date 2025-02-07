#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MapMaking.h"
#include "AStar.h"
#include "Timer.h"
#include "DepthFirst.h"
#include <sstream>
int DISPLAY_WIDTH = 1240;
int DISPLAY_HEIGHT = 640;
int DISPLAY_SCALE = 2;
Play::Vector2D startRect = Play::Vector2D(20,20);
Play::Vector2D startPosition = Play::Vector2D(20, 20);
bool firstTime = true;
int row = 0;
bool runAStar = true;
bool runDepthFirst = false;

std::vector<MapMaking*> maps;
MapMaking m1;
MapMaking m2;
MapMaking m3;


AStar a1;
AStar a2;
AStar a3;
DepthFirst d1;
DepthFirst d2;
DepthFirst d3;

Timer AStartT1;
Timer AStartT2;
Timer AStartT3;

Timer BreadthT1;
Timer BreadthT2;
Timer BreadthT3;

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

void DrawAStarPath(AStar a, Tile* end, Timer timer, Play::Point2D pos) {
	bool ownerFound = true;

	
	if (runAStar) {
		timer.startTimer();
		a.AStarAlgorithm(*end);
		timer.stopTimer();
		std::string s = std::to_string(timer.time) + " microsec";
		Play::DrawDebugText(pos, s.c_str());

	}
	

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

void DrawDepthPath(DepthFirst* d, Tile* end, Timer timer, Play::Point2D pos, int xOffset, int yOffset) {
	
	if (runDepthFirst) {
		timer.startTimer();
		d->TraversMap();
		timer.stopTimer();
		std::string s = std::to_string(timer.time) + " microsec";
		Play::DrawDebugText(pos, s.c_str());

	}
	
	
	for (auto as : d->traversedList)
	{
		Play::Point2D pos1 = Play::Vector2D(as->position[0] - 9+xOffset, as->position[1] - 9 + yOffset);

		Play::Point2D pos2 = Play::Vector2D(as->position[0] - 1 + xOffset, as->position[1] - 1 + yOffset);
		Play::DrawRect(pos1, pos2, Play::cYellow, true);
		//t = as;

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
			Play::Vector2D start = Play::Vector2D(map->tiles[i].position[0] - 5, map->tiles[i].position[1] - 5);

			Play::Vector2D end = Play::Vector2D(map->tiles[i].neighbours[j]->position[0] - 5, map->tiles[i].neighbours[j]->position[1] - 5);

			Play::DrawLine(start, end, Play::cMagenta);
			if (map->tiles[i].neighbours[j]->type != WALL && map->tiles[i].type != WALL) {
				
			}
			
		}
		
	}
}



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	m1.MakeMap("../Maps/Map1.txt");

	m2.MakeMap("../Maps/Map2.txt");

	m3.MakeMap("../Maps/Map3.txt");
	for (int i = 0; i < 2; i++)
	{
		
		
		maps.push_back(&m1);
		maps.push_back(&m2);
		maps.push_back(&m3);
	}
	for (int i = 0; i < maps.size(); i++)
	{
		for (int j = 0; j < maps[i]->tiles.size(); j++)
		{
			if (maps[i]->tiles[j].type == START) {
				maps[i]->startTile = maps[i]->tiles[j];
				break;
			}
		}
	}
	a1.openList.insert(pair<int, Tile*>(maps[0]->startTile.id, &maps[0]->startTile));
	a2.openList.insert(pair<int, Tile*>(maps[1]->startTile.id, &maps[1]->startTile));
	a3.openList.insert(pair<int, Tile*>(maps[2]->startTile.id, &maps[2]->startTile));
	
	d1.startTile = &maps[3]->startTile;
	d1.endTile = &maps[3]->endTile;
	d1.traversedList.push_back(d1.startTile);

	d2.startTile = &maps[4]->startTile;
	d2.endTile = &maps[4]->endTile;
	d2.traversedList.push_back(d2.startTile);

	d3.startTile = &maps[5]->startTile;
	d3.endTile = &maps[5]->endTile;
	d3.traversedList.push_back(d3.startTile);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer(cBlack);
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Hello World!" );
	
		startPosition.y = 20;
		DrawMap(maps[0], startRect);

		//startRect = startPosition;
		startPosition.y += 170 ;
		startRect = Play::Vector2D(startPosition.x, startPosition.y);
		DrawMap(maps[1], startRect);

		startPosition.y += 170 ;
		startRect = startPosition;
		startRect = Play::Vector2D(startPosition.x, startPosition.y);
		Play::Vector2D o = startRect;
		DrawMap(maps[2], o);

		startPosition.y = 20;
		startPosition.x += 390;
		startRect = startPosition;
		DrawMap(maps[3], startRect);

		//startRect = startPosition;
		startPosition.y += 170;
		
		startRect = Play::Vector2D(startPosition.x, startPosition.y);
		DrawMap(maps[4], startRect);

		startPosition.y += 170;
		
		startRect = startPosition;
		startRect = Play::Vector2D(startPosition.x, startPosition.y);
		Play::Vector2D a = startRect;
		DrawMap(maps[5], a);
	
	//PaintNeighbours(&map1);
	//PaintNeighbours(&map2);
	//PaintNeighbours(&map3);
	if (firstTime == true) {
		firstTime = false;
		a1.currentcell = maps[0]->startTile;
		
		a2.currentcell = maps[1]->startTile;
		a3.currentcell = maps[2]->startTile;
		
	}
	DrawAStarPath(a1, &maps[0]->endTile, AStartT1, Play::Point2D(245, 50));

	DrawAStarPath(a2, &maps[1]->endTile, AStartT2, Play::Point2D(245, 220));

	DrawAStarPath(a3, &maps[2]->endTile, AStartT3, Play::Point2D(350, 390));

	//runAStar = false;
	runDepthFirst = true;

	//debug neighbours
	DrawDepthPath(&d1, d1.endTile, BreadthT1, Play::Point2D(245+390, 50), 390,0);
	DrawDepthPath(&d2, d2.endTile, BreadthT2, Play::Point2D(245+390, 220),390,0);
	DrawDepthPath(&d3, d3.endTile, BreadthT3, Play::Point2D(350+390, 390),390,0);
	//runDepthFirst = false;

	
	//Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH/3, DISPLAY_HEIGHT / 3), "A");
	
	

	Play::PresentDrawingBuffer();
	startPosition.x = 20;
	startPosition.y = 20;
	startRect = startPosition;
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}





