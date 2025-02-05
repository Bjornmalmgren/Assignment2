#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MapMaking.h"
#include "AStar.h"
int DISPLAY_WIDTH = 1240;
int DISPLAY_HEIGHT = 640;
int DISPLAY_SCALE = 2;
Play::Vector2D startRect = Play::Vector2D(20,20);
Play::Vector2D startPosition = Play::Vector2D(20, 20);
bool firstTime = true;
int row = 0;
bool endFound;
MapMaking map1;
MapMaking map2;
MapMaking map3;
AStar a;

void DrawMap(MapMaking* map) {
	startRect = Play::Vector2D(startRect.x+ map->tiles[0].width * map->tiles[0].rectangleSize, startPosition.y);
	for (size_t i = map->tiles.size()-1; i > 0; i--)
	{ 
		
		int t = i + 1;
		if (t % (map->tiles[i].width) == 0) {
			startRect.y += map->tiles[i].rectangleSize;
			startRect.x = startRect.x + map->tiles[i].width * map->tiles[i].rectangleSize;
		}
		switch (map->tiles[i].type)
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
			map->startTile = map->tiles[i];
			Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cYellow, true);
			startRect.x -= map->tiles[i].rectangleSize;

			break;
		case END:
			map->endTile = map->tiles[i];
			Play::DrawRect(startRect, startRect + Play::Vector2D(map->tiles[i].rectangleSize, map->tiles[i].rectangleSize), Play::cGreen, true);
			startRect.x -= map->tiles[i].rectangleSize;


			break;
		default:
			break;
		}
		if (firstTime == true) {
			map->tiles[i].position.push_back(startRect.x + 20);
			map->tiles[i].position.push_back(startRect.y + 10);
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

void PaintNeighbours(MapMaking* map) {
	/*int i = 19;
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
	a.openList.insert(pair<int, Tile*>(map1.startTile.id, &map1.startTile));
	
	map2.MakeMap("../Maps/Map2.txt");
	map3.MakeMap("../Maps/Map3.txt");
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer(cWhite);
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Hello World!" );
	
	DrawMap(&map1);

	//startRect = startPosition;
	startRect = Play::Vector2D(startPosition.x +10 + map1.tiles[0].width * map1.tiles[0].rectangleSize, startPosition.y);
	DrawMap(&map2);
	//startRect = startPosition;
	startRect = Play::Vector2D(-60 + map1.tiles[0].width * map1.tiles[0].rectangleSize + map2.tiles[0].width * map2.tiles[0].rectangleSize, startPosition.y);
	DrawMap(&map3);
	if (firstTime == true) {
		firstTime = false;
		a.currentcell = map1.startTile;
	}
	

	//debug neighbours
	/*PaintNeighbours(&map1);
	PaintNeighbours(&map2);
	PaintNeighbours(&map3);*/
	a.AStarAlgorithm(map1.endTile);
	if (endFound) {
		return true;
	}
	
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





