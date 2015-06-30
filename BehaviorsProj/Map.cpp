/*
 * Map.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Map.h"

Map::~Map() {
	delete _configurationManager;
}

Map::Map(ConfigurationManager* configurationManager) {
	_configurationManager = configurationManager;
	_gridMapResolutionRatio = (_configurationManager->getGridResolutionCM() / _configurationManager->getMapResolutionCM());
}

void Map::initializeGrid(int width, int height) {
	setWidth(width);
	setHeight(height);

	_grid = new Matrix(ceil(getWidth() / (_gridMapResolutionRatio / 2)),
					   ceil(getHeight() / (_gridMapResolutionRatio / 2)),
					   UNKNOWN_CELL);
}

int Map::getWidth() {
	return _width;
}

void Map::setWidth(int width) {
	_width = width;
}

int Map::getHeight() {
	return _height;
}

void Map::setHeight(int height) {
	_height = height;
}

int Map::getCellValue(int column, int row) {
	return _grid->getCellValue(column / (_gridMapResolutionRatio / 2),
							   row / (_gridMapResolutionRatio));
}

void Map::loadMap(string pngFilePath) {
	// Load PNG file from disk to memory first, then decode to raw pixels in memory.
	vector<unsigned char> pngFile;
	vector<unsigned char> imagePixelsVector;
	unsigned width, height;

	// Load and decode the map file
	lodepng::load_file(pngFile, pngFilePath);
	lodepng::decode(imagePixelsVector, width, height, pngFile);

	initializeGrid(width, height);

	int gridVectorRowsIndex = 0;
	int gridVectorColumnsIndex = 0;

	for (int rowsIndex = 0; rowsIndex < getHeight(); rowsIndex += (_gridMapResolutionRatio / 2)) {
		for (int columnsIndex = 0; columnsIndex < getWidth() * BYTES_PER_PIXEL; columnsIndex += (BYTES_PER_PIXEL * (_gridMapResolutionRatio / 2))) {
			bool isACertainCellOccupied = false;

			for (int unitedRowsIndex = rowsIndex; (unitedRowsIndex < rowsIndex + (_gridMapResolutionRatio / 2)) &&
												  (unitedRowsIndex < (_grid->getHeight() * (_gridMapResolutionRatio / 2)) - 1) && !isACertainCellOccupied; unitedRowsIndex++) {
				for (int unitedColumnsIndex = columnsIndex; (unitedColumnsIndex < columnsIndex + ((_gridMapResolutionRatio / 2) * BYTES_PER_PIXEL)) &&
															(ceil(unitedColumnsIndex / BYTES_PER_PIXEL) < (_grid->getWidth() * (_gridMapResolutionRatio / 2)) - 1) && !isACertainCellOccupied; unitedColumnsIndex += BYTES_PER_PIXEL) {
					int cell = (unitedRowsIndex * (width * BYTES_PER_PIXEL)) + unitedColumnsIndex;

					if (imagePixelsVector.at(cell) != 255 || imagePixelsVector.at(cell + 1) != 255 || imagePixelsVector.at(cell + 2) != 255)
						isACertainCellOccupied = true;
				}
			}

			if (isACertainCellOccupied)
				_grid->setCellValue(gridVectorColumnsIndex, gridVectorRowsIndex, OCCUPIED_CELL);
			else
				_grid->setCellValue(gridVectorColumnsIndex, gridVectorRowsIndex, FREE_CELL);

			gridVectorColumnsIndex++;
		}

		gridVectorColumnsIndex = 0;
		gridVectorRowsIndex++;
	}
}

void Map::saveMap(string pngFilePath) {
	vector<unsigned char> pngFile = vector<unsigned char>();
	vector<unsigned char> imagePixelsVector = vector<unsigned char>();

	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++){
		for(int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			if (_grid->getCellValue(columnsIndex, rowsIndex) == FREE_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::WHITE);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == START_LOCATION_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::RED);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == GOAL_LOCATION_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::BLUE);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == ROUTE_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::GREEN);
			} else {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::BLACK);
			}
		}
	}

	lodepng::encode(pngFile, imagePixelsVector, _grid->getWidth(), _grid->getHeight());
	lodepng::save_file(pngFile, pngFilePath);
}

void Map::printMap(string fileName) {
	ofstream vectorOutputFile((fileName).c_str());
	cout << "Printing Map: " << endl;

	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++) {
		for (int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			cout << _grid->getCellValue(columnsIndex, rowsIndex);
			vectorOutputFile << _grid->getCellValue(columnsIndex, rowsIndex);
		}

		cout << endl;
		vectorOutputFile << endl;
	}

	vectorOutputFile.close();
}

void Map::padACell(int column, int row, int factor) {
	for (int rowsIndex = row - factor; rowsIndex <= row + factor; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _grid->getHeight())) {
			for (int columnsIndex = column - factor; columnsIndex <= column + factor; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _grid->getWidth()))
					_grid->setCellValue(columnsIndex, rowsIndex, OCCUPIED_CELL);
			}
		}
	}
}

void Map::padMapObstacles(int factor) {
	Matrix tempMatrix = Matrix(_grid->getWidth(), _grid->getHeight(), FREE_CELL);

	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++) {
		for (int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			if (_grid->getCellValue(columnsIndex, rowsIndex) == OCCUPIED_CELL)
				padACell(columnsIndex, rowsIndex, factor);
		}
	}

	_grid->swap(tempMatrix);
}

void Map::pushRGBAColorToAVector(vector<unsigned char> * vector, int color) {
	const int* rgbaColor = Helper::getRGBA(color);

	vector->push_back(rgbaColor[0]);
	vector->push_back(rgbaColor[1]);
	vector->push_back(rgbaColor[2]);
	vector->push_back(rgbaColor[3]);
}
