#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MapMaking.h"

int DISPLAY_WIDTH = 1240;
int DISPLAY_HEIGHT = 640;
int DISPLAY_SCALE = 2;
Play::Point2D startRect = Play::Vector2D(20,20);
int rectangleSize = 10;
int row = 0;
MapMaking map1;

void DrawMap(MapMaking map) {
	startRect = Play::Vector2D(20+ map1.tiles.width*rectangleSize, map1.tiles.width * rectangleSize);
	for (size_t i = map.tiles.tiles.size()-1; i > 1; i--)
	{
		
		int t = i + 1;
		if (t % (map1.tiles.width) == 0) {
			startRect.y += rectangleSize;
			startRect.x = 20 + map1.tiles.width * rectangleSize;
		}
		switch (map.tiles.tiles[i])
		{
			
		case WALL:
			Play::DrawRect(startRect, startRect + Play::Vector2D(rectangleSize, rectangleSize), Play::cRed, true);
			startRect.x -= rectangleSize;
		
			break;
		case PATH:
			Play::DrawRect(startRect, startRect + Play::Vector2D(rectangleSize, rectangleSize), Play::cWhite, true);
			startRect.x -= rectangleSize;

			break;
		case START:
			Play::DrawRect(startRect, startRect + Play::Vector2D(rectangleSize, rectangleSize), Play::cYellow, true);
			startRect.x -= rectangleSize;

			break;
		case END:
			Play::DrawRect(startRect, startRect + Play::Vector2D(rectangleSize, rectangleSize), Play::cGreen, true);
			startRect.x -= rectangleSize;

	
			break;
		default:
			break;
		}
	}
	Play::PresentDrawingBuffer();
}
// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	map1.MakeMap("../Maps/Map1.txt");
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer(cWhite);
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Hello World!" );
	
	DrawMap(map1);
	
	startRect = Play::Vector2D(20, 20);
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}



