/*
 * Map.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include "math.h"


Map::~Map() {
	// TODO Auto-generated destructor stub
}

Map::Map()
{
	for (int i = 0; i < MAP_ROWS ; i++)
	{
		for (int j = 0; j < MAP_COLUMNS ; j++)
		{
			_map[i][j] = UNKNOWN_CELL;
		}
	}
}

void Map::readMap()
{
	//Load PNG file from disk to memory first, then decode to raw pixels in memory.
	  std::vector<unsigned char> png;
	  std::vector<unsigned char> image; //the raw pixels
	  unsigned width, height;

	  //load and decode
	  lodepng::load_file(png, "/home/colman/Documents/Robitics Final Project/PcBotWorld/roboticLabMap.png");
	  lodepng::decode(image, width, height, png);

	  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
	  for (int i = 0; i < MAP_COLUMNS * MAP_ROWS * BYTES_PER_PIXEL; i += 4)
	  {
		  if (image[i] != 0 || image[i+1] != 0 || image[i+2] != 0)
			  _map[floor((i/BYTES_PER_PIXEL)/MAP_COLUMNS)][(i/BYTES_PER_PIXEL)%MAP_COLUMNS] = OCCUPIED_CELL;
		  else
			  _map[floor((i/BYTES_PER_PIXEL)/MAP_COLUMNS)][(i/BYTES_PER_PIXEL)%MAP_COLUMNS] = FREE_CELL;
	  }
}

void Map::printMap()
{
	cout << "Printing Map: " << endl;
	for (int i = 0; i < MAP_ROWS ; i++)
	{
		for (int j = 0; j < MAP_COLUMNS ; j++)
		{
			cout << _map[i][j];
		}
		cout << endl;
	}
}

int Map::calculateXIndex(int x)
{
	return (x / MAP_RESOLUTION) + (MAP_COLUMNS / 2);
}

int Map::calculateYIndex(int y)
{
	return (y / MAP_RESOLUTION) - (MAP_ROWS / 2);
}

void Map::getMapCoordinates(double realX,double realY,int &mapX,int &mapY)
{
	mapX = calculateXIndex(realX);
	mapY = calculateYIndex(realY);
}

void Map::setCellValue(int x, int y, int value)
{
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	_map[xIndex][yIndex] = value;
}

int Map::getCellValue(int x, int y)
{
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	return _map[xIndex][yIndex];
}
