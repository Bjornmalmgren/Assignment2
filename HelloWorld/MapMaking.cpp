#include "MapMaking.h"
void MapMaking::MakeMap(std::string filepath) {
	string line;
	fstream readFile;
	readFile.open(filepath);
	int row = 0;
	while (getline(readFile,line))
	{
		
		for (int i = 0; i < line.length(); i++)
		{
			
			Tile t;
			t.width = line.length();
			t.setX(i);
			t.setY(row);
			t.id = row + i;
			switch (line[i])
			{
			case 'X':
				t.type = WALL;
				tiles.push_back(t);
				break;
			case '0':
				t.type = PATH;
				tiles.push_back(t);
				break;
			case 'S':
				t.type = START;
				tiles.push_back(t);
				startTile = tiles[i + row* tiles[i].width];
				break;
			case 'G':
				t.type = END;
				tiles.push_back(t);
				endTile = tiles[i + row * tiles[i].width];
				break;
			default:
				break;
			}
			
		}
		row++;
	}
	readFile.close();
	for (int i = 0; i < tiles.size(); i++)
	{
		if (i == 19) {
			int a = 2;
		}
		//up
		if (tiles[i].getY() == 0) {

		}
		else
		{
			int t = i - (tiles[0].width );
			tiles[i].neighbours.push_back(&tiles[t]);

		}
		//upper left corner
		if (tiles[i].getY() == 0) {

		}
		else
		{
			int t = i - 1 - (tiles[0].width);
			if (i == tiles[0].width) {
				t = 0;
			}
			tiles[i].neighbours.push_back(&tiles[t]);
		}
		//upper right corner
		if (tiles[i].getY() == 0) {

		}
		else
		{
			int t = i + 1 - (tiles[0].width);
			tiles[i].neighbours.push_back(&tiles[t]);
		}
		//left
		if (tiles[i].getX() == 0) {

		}
		else
		{
			int t = i - 1;
			tiles[i].neighbours.push_back(&tiles[t]);
		}
		//right
		if (tiles[i].getX() == tiles[i].width-1) {
;
		}
		else
		{
			int t = i + 1;
			tiles[i].neighbours.push_back(&tiles[t]);
		}
		//bottom
		if (tiles[i].getY() == row - 1) {
		}
		else
		{
			int t = i + (tiles[0].width);
			tiles[i].neighbours.push_back(&tiles[t]);
		}
		//bottom left corner
		if (tiles[i].getY() == row - 1) {
		}
		else
		{
			int t = i - 1 + (tiles[0].width);
			tiles[i].neighbours.push_back(&tiles[t]);
		}
		//bottom right corner
		if (tiles[i].getY() == row - 1) {

		}
		else
		{
			
			int t = i + 1 + (tiles[0].width);
			if (t <= 255) {
				tiles[i].neighbours.push_back(&tiles[t]);
			}
			
		}
	}
}
