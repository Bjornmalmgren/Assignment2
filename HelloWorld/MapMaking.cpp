#include "MapMaking.h"
void MapMaking::MakeMap(std::string filepath) {
	string line;
	fstream readFile;
	readFile.open(filepath);
	while (getline(readFile,line))
	{
		tiles.width = line.length();
		for (int i = 0; i < line.length(); i++)
		{
			switch (line[i])
			{
			case 'X':
				tiles.tiles.push_back(WALL);
				break;
			case '0':
				tiles.tiles.push_back(PATH);
				break;
			case 'S':
				tiles.tiles.push_back(START);
				break;
			case 'G':
				tiles.tiles.push_back(END);
				break;
			default:
				break;
			}
		}
	}
	readFile.close();
}
