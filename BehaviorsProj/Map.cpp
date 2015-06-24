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

Map::Map(int width, int height, ConfigurationManager* configurationManager) {
	_configurationManager = configurationManager;
	_gridMapResolutionRatio = (_configurationManager->getGridResolutionCM() / _configurationManager->getMapResolutionCM());
	_width = width;
	_height = height;

	_grid = new Matrix(ceil(width / (_gridMapResolutionRatio / 2)),
					   ceil(height / (_gridMapResolutionRatio / 2)),
					   UNKNOWN_CELL);
}

int Map::getWidth() {
	return _width;
}

int Map::getHeight() {
	return _height;
}

int Map::getCellValue(int column, int row) {
	return _grid->getCellValue(column / (_gridMapResolutionRatio / 2),
							   row / (_gridMapResolutionRatio));
}

void Map::setCellValue(int column, int row, int value) {
	_grid->setCellValue(column / (_gridMapResolutionRatio / 2),
						row / (_gridMapResolutionRatio / 2),
						value);
}

void Map::readMap() {
	// Load PNG file from disk to memory first, then decode to raw pixels in memory.
	vector<unsigned char> pngFile;
	vector<unsigned char> imagePixelsVector;
	unsigned width, height;

	// Load and decode the map file
	lodepng::load_file(pngFile, "/home/colman/Documents/RoboticsFinalProj/PcBotWorld/roboticLabMap.png");
	lodepng::decode(imagePixelsVector, width, height, pngFile);

	int gridVectorRowsIndex = 0;
	int gridVectorColumnsIndex = 0;

	for (int rowsIndex = 0; rowsIndex < height; rowsIndex += (_gridMapResolutionRatio / 2)) {
		for (int columnsIndex = 0; columnsIndex < width * BYTES_PER_PIXEL; columnsIndex += (BYTES_PER_PIXEL * (_gridMapResolutionRatio / 2))) {
			bool isACertainCellOccupied = false;

			for (int unitedRowsIndex = rowsIndex; (unitedRowsIndex < rowsIndex + (_gridMapResolutionRatio / 2)) && (unitedRowsIndex < (_grid->getHeight() * (_gridMapResolutionRatio / 2)) - 1) && !isACertainCellOccupied; unitedRowsIndex++) {
				for (int unitedColumnsIndex = columnsIndex; (unitedColumnsIndex < columnsIndex + ((_gridMapResolutionRatio / 2) * BYTES_PER_PIXEL)) && (ceil(unitedColumnsIndex / BYTES_PER_PIXEL) < (_grid->getWidth() * (_gridMapResolutionRatio / 2)) - 1) && !isACertainCellOccupied; unitedColumnsIndex += BYTES_PER_PIXEL) {
					int cell = (unitedRowsIndex * (width * BYTES_PER_PIXEL)) + unitedColumnsIndex;

					if (imagePixelsVector.at(cell) != 255 || imagePixelsVector.at(cell + 1) != 255 || imagePixelsVector.at(cell + 2) != 255) {
						isACertainCellOccupied = true;
					}
				}
			}

			if (isACertainCellOccupied) {
				_grid->setCellValue(gridVectorColumnsIndex, gridVectorRowsIndex, OCCUPIED_CELL);
			} else {
				_grid->setCellValue(gridVectorColumnsIndex, gridVectorRowsIndex, FREE_CELL);
			}

			gridVectorColumnsIndex++;
		}

		gridVectorColumnsIndex = 0;
		gridVectorRowsIndex++;
	}
}

void Map::printMap(string fileName) {
	ofstream vectorOutputFile((fileName).c_str());

	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++) {
		for (int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			vectorOutputFile << _grid->getCellValue(columnsIndex, rowsIndex);
		}

		vectorOutputFile << endl;
	}

	vectorOutputFile.close();
}

void Map::padACell(int column, int row, Matrix* matrix, int factor) {
	for (int rowsIndex = row - factor; rowsIndex <= row + factor; rowsIndex++) {
		if (!(rowsIndex < 0 || rowsIndex >= _grid->getHeight())) {
			for (int columnsIndex = column - factor; columnsIndex <= column + factor; columnsIndex++) {
				if (!(columnsIndex < 0 || columnsIndex >= _grid->getWidth()))
					matrix->setCellValue(columnsIndex, rowsIndex, OCCUPIED_CELL);
			}
		}
	}
}

void Map::padMapObstacles(int factor) {
	Matrix tempMatrix = Matrix(_grid->getWidth(), _grid->getHeight(), FREE_CELL);

	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++) {
		for (int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			if (_grid->getCellValue(columnsIndex, rowsIndex) == OCCUPIED_CELL)
				padACell(columnsIndex, rowsIndex, &tempMatrix, factor);
		}
	}

	_grid->swap(tempMatrix);
}
