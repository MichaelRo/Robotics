/*
 * Map.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Map.h"

Map::~Map() {
	delete _map;
}

Map::Map(int width, int height, float resolution) {
	_width = width;
	_height = height;
	_resolution = resolution;

	for (int i = 0; i < MAP_ROWS ; i++) {
		for (int j = 0; j < MAP_COLUMNS ; j++)
			_map[i][j] = UNKNOWN_CELL;
	}
}

int Map::getWidth() {
	return _width;
}

int Map::getHeight() {
	return _height;
}

float Map::getResolution() {
	return _resolution;
}

int Map::getCellValue(int x, int y) {
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	return _map[xIndex][yIndex];
}

void Map::setCellValue(int x, int y, int value) {
	int xIndex = calculateXIndex(x);
	int yIndex = calculateYIndex(y);
	_map[xIndex][yIndex] = value;
}

void Map::readMap() {
	// Load PNG file from disk to memory first, then decode to raw pixels in memory.
	std::vector<unsigned char> pngFile;
	std::vector<unsigned char> imagePixelsVector;
	unsigned width, height;

	// Load and decode the map file
	lodepng::load_file(pngFile, "/home/colman/Documents/RoboticsFinalProj/PcBotWorld/roboticLabMap.png");
	lodepng::decode(imagePixelsVector, width, height, pngFile);

	// The map pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA.
	// Therefore we need to order it in a new matrix (1 bytes per pixel)
	for (int i = 0; i < MAP_COLUMNS * MAP_ROWS * BYTES_PER_PIXEL; i += BYTES_PER_PIXEL) {
		int mapRow = floor((i/BYTES_PER_PIXEL)/MAP_COLUMNS);
		int mapColumn = (i/BYTES_PER_PIXEL)%MAP_COLUMNS;
		int *currentMapPixel;
		currentMapPixel = &_map[mapRow][mapColumn];
		bool isCurrentPixelOccupied = imagePixelsVector[i] != 255 ||
									  imagePixelsVector[i+1] != 255 ||
									  imagePixelsVector[i+2] != 255;

		if (isCurrentPixelOccupied)
			*currentMapPixel = OCCUPIED_CELL;
		else
			*currentMapPixel = FREE_CELL;
	}
}

void Map::printMap(string fileName) {
	ofstream outputFile(fileName.c_str());
	cout << "Printing Map: " << endl;

	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLUMNS; j++) {
			cout << _map[i][j];
			outputFile << _map[i][j];
		}

		cout << endl;
		outputFile << endl;
	}

	outputFile.close();
}

void Map::padACell(int i, int j, int tempMap[MAP_ROWS][MAP_COLUMNS], int factor) {
	for (int x = i - factor; x <= i + factor; x++) {
		if (!(x < 0 || x >= MAP_ROWS)) {
			for (int y = j - factor; y <= j + factor; y++) {
				if (!(y < 0 || y >= MAP_COLUMNS))
					tempMap[x][y] = OCCUPIED_CELL;
			}
		}
	}
}

void Map::padMapObstacles(int factor) {
	int tempMap[MAP_ROWS][MAP_COLUMNS];

	// Initializing the blank temp matrix cells before padding the obstacles
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLUMNS; j++)
			tempMap[i][j] = FREE_CELL;
	}

	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLUMNS; j++) {
			if (_map[i][j] == OCCUPIED_CELL)
				padACell(i, j, tempMap, factor);
		}
	}

	std::swap(_map, tempMap);
}

int Map::calculateXIndex(int x) {
	return (x / MAP_RESOLUTION) + (MAP_COLUMNS / 2);
}

int Map::calculateYIndex(int y) {
	return (y / MAP_RESOLUTION) - (MAP_ROWS / 2);
}
