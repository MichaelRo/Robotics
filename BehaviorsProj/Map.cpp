/*
 * Map.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Map.h"

/**
	Destructs the map
*/
Map::~Map() {
	delete _grid;
}

/**
	Initializes a new Map

	@param configurationManager - configurationManager that holds the configuration properties.
*/
Map::Map(ConfigurationManager * configurationManager) {
	_configurationManager = configurationManager;
	_gridResolution = configurationManager->getGridResolutionCM();
	_mapResolution = configurationManager->getMapResolutionCM();
	_grid = NULL;
	_height = 0;
	_width = 0;
}

/**
	Sets the map's grid dimensions and initializes all the cells with UNKNOWN_CELL value.

	@param width - the map's width
	@param height - the map's height
*/
void Map::initializeGrid(int width, int height) {
	setWidth(width);
	setHeight(height);

	// Initializes the grid with the given dimensions but with the needed resolution
	// The resolution: (Grid's resolution / Map's (png) resolution) / 2
	_grid = new Matrix(ceil(getWidth() / (getGridMapResolutionRatio() / 2)),
					   ceil(getHeight() / (getGridMapResolutionRatio() / 2)),
					   UNKNOWN_CELL);
}

/**
	Returns the map's width

	@return - width
*/
int Map::getWidth() {
	return _width;
}

/**
	Sets the map's width

	@param width
*/
void Map::setWidth(int width) {
	_width = width;
}

/**
	Returns the map's height

	@return - height
*/
int Map::getHeight() {
	return _height;
}

/**
	Sets the map's height

	@param height
*/
void Map::setHeight(int height) {
	_height = height;
}

/**
	Returns the grid's resolution

	@return - resolution
*/
float Map::getGridResolution() {
	return _gridResolution;
}

/**
	Sets the grid's resolution

	@param resolution
*/
void Map::setGridResolution(float resolution) {
	_gridResolution = resolution;
}

/**
	Returns the map's resolution

	@return - resolution
*/
float Map::getMapResolution() {
	return _mapResolution;
}

/**
	Sets the map's resolution

	@param resolution
*/
void Map::setMapResolution(float resolution) {
	_mapResolution = resolution;
}

/**
	Returns the ratio between the grid's and the map's resolution

	@return - ratio
*/
float Map::getGridMapResolutionRatio() {
	return getGridResolution() / getMapResolution();
}

/**
	Gets a certain cell value

	@param column - the cell's column
	@param row - the cell's row
	@param resolution - wanted resolution
	@return - the cell value
*/
int Map::getCellValue(int column, int row, float resolution) {
	return _grid->getCellValue(column / ceil(((getGridResolution() / resolution) / 2)),
							   row / ceil(((getGridResolution() / resolution) / 2)));
}

/**
	Sets a certain cell value

	@param column - the cell's column
	@param row - the cell's row
	@param value - the cell value
	@param resolution - wanted resolution
*/
void Map::setCellValue(int column, int row, int value, float resolution) {
	_grid->setCellValue(round(column / ceil(((getGridResolution() / resolution) / 2))),
						round(row / ceil(((getGridResolution() / resolution) / 2))),
						value);
}

/**
	Loads the map's grid from a given png map file

	@param pngFilePath - the png map file path
*/
void Map::loadMap(string pngFilePath) {
	// Load PNG file from disk to memory first, then decodes it to raw pixels in memory.
	vector<unsigned char> pngFile;
	vector<unsigned char> imagePixelsVector;
	unsigned width, height;

	// Load and decode the map file
	lodepng::load_file(pngFile, pngFilePath);
	lodepng::decode(imagePixelsVector, width, height, pngFile);

	initializeGrid(width, height);

	int gridVectorRowsIndex = 0;
	int gridVectorColumnsIndex = 0;

	// Runs overs the imagePixelVector (4 cells each time as the RGBA color type)
	for (int rowsIndex = 0; rowsIndex < getHeight(); rowsIndex += (getGridMapResolutionRatio() / 2)) {
		for (int columnsIndex = 0; columnsIndex < getWidth() * BYTES_PER_PIXEL; columnsIndex += (BYTES_PER_PIXEL * (getGridMapResolutionRatio() / 2))) {
			bool isACertainCellOccupied = false;

			// Runs over neighbor cells in order to unite cells for resolution change (as defined in the configuration file)
			for (int unitedRowsIndex = rowsIndex; (unitedRowsIndex < rowsIndex + (getGridMapResolutionRatio() / 2)) &&
												  (unitedRowsIndex < (_grid->getHeight() * (getGridMapResolutionRatio() / 2)) - 1) && !isACertainCellOccupied; unitedRowsIndex++) {
				for (int unitedColumnsIndex = columnsIndex; (unitedColumnsIndex < columnsIndex + ((getGridMapResolutionRatio() / 2) * BYTES_PER_PIXEL)) &&
															(ceil(unitedColumnsIndex / BYTES_PER_PIXEL) < (_grid->getWidth() * (getGridMapResolutionRatio() / 2)) - 1) && !isACertainCellOccupied; unitedColumnsIndex += BYTES_PER_PIXEL) {
					int cell = (unitedRowsIndex * (width * BYTES_PER_PIXEL)) + unitedColumnsIndex;

					// Checks if the cell is occupied by checking if it isn't white
					// the last cell (the A of RGBA) doesn't matter because it describes the alpha and not the color itself
					if (imagePixelsVector.at(cell) != 255 || imagePixelsVector.at(cell + 1) != 255 || imagePixelsVector.at(cell + 2) != 255)
						isACertainCellOccupied = true;
				}
			}

			// Marks the cell type in the grid
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

/**
	Saves the map's grid to a png file

	@param pngFilePath - the required png file path
*/
void Map::saveMap(string pngFilePath) {
	vector<unsigned char> pngFile = vector<unsigned char>();
	vector<unsigned char> imagePixelsVector = vector<unsigned char>();

	// Runs over all the cells in the grid
	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++){
		for(int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			// Marks the cell by it's type
			if (_grid->getCellValue(columnsIndex, rowsIndex) == FREE_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::WHITE);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == START_LOCATION_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::RED);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == GOAL_LOCATION_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::BLUE);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == ROUTE_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::GREEN);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == WAYPOINT_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::YELLOW);
			} else if (_grid->getCellValue(columnsIndex, rowsIndex) == PADDING_CELL) {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::GRAY);
			} else {
				pushRGBAColorToAVector(&imagePixelsVector, Helper::BLACK);
			}
		}
	}

	// Encodes the  imagePixelVector and saves it to a file
	lodepng::encode(pngFile, imagePixelsVector, _grid->getWidth(), _grid->getHeight());
	lodepng::save_file(pngFile, pngFilePath);
}

/**
	Prints the map's grid to a textual file and to the console

	@param fileName - the required text file path
*/
void Map::printMap(string fileName) {
	ofstream vectorOutputFile((fileName).c_str());
	cout << "Printing Map: " << endl;

	// Runs over all the cells and prints it's value
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

/**
	Swaps the map's properties with an other map

	@param map - the map that will be taken
*/
void Map::swapMap(Map * map) {
	delete _configurationManager;
	delete _grid;

	_configurationManager = map->_configurationManager;
	_gridResolution = map->_gridResolution;
	_mapResolution = map->_mapResolution;
	_grid = map->_grid;
	_width = map->_width;
	_height = map->_height;
}

/**
	Pads any obstacle in the map with PADDING_CELL cells around him within a given ratio
	The padding occurs in a temporary matrix and then swaps the main matrix to the temporary

	@param ratio - the padding ratio
*/
void Map::padMapObstacles(int ratio) {
	Matrix tempMatrix(_grid->getWidth(), _grid->getHeight(), FREE_CELL);

	for (int rowsIndex = 0; rowsIndex < _grid->getHeight(); rowsIndex++) {
		for (int columnsIndex = 0; columnsIndex < _grid->getWidth(); columnsIndex++) {
			if (_grid->getCellValue(columnsIndex, rowsIndex) == OCCUPIED_CELL) {
				// Setting the cell itself in the temporary matrix
				tempMatrix.setCellValue(columnsIndex, rowsIndex, OCCUPIED_CELL);

				// Setting the cell's neighbors in the temporary matrix
				padACell(Structs::Point(columnsIndex, rowsIndex), &tempMatrix, ratio);
			}
		}
	}

	_grid->swap(&tempMatrix);
}

/**
	Pads a certain cell within a given matrix

	@param cellPoint - the point of the cell, represented as Structs::Point
	@param matrix - the matrix
	@param ratio - the padding ratio
*/
void Map::padACell(Structs::Point cellPoint, Matrix * matrix, int ratio) {
	list<Structs::Point> neighbors = getCellsNeighbors(cellPoint, matrix, ratio);

	for (list<Structs::Point>::iterator neighborsIterator = neighbors.begin(); neighborsIterator != neighbors.end(); neighborsIterator++) {
		Structs::Point * neighbor = neighborsIterator.operator ->();

		// Sets the neighbor as a neighbor only if it isn't already occupied
		if (_grid->getCellValue(neighbor->getX(), neighbor->getY()) == FREE_CELL)
			matrix->setCellValue(neighbor->getX(), neighbor->getY(), PADDING_CELL);
	}
}

/**
	Marks a given route in the map

	@param route - the given route, represented as list<Structs::Point>
*/
void Map::markRoute(list<Structs::Point> route, float resolution) {
	markCells(route, ROUTE_CELL, resolution);
}

/**
	Marks given waypoints in the map

	@param wayPoints - the waypoints, represented as list<Structs::Point>
*/
void Map::markWayPoints(list<Structs::Point> wayPoints, float resolution) {
	markCells(wayPoints, WAYPOINT_CELL, resolution);
}

/**
	Marks given waypoints in the map

	@param points - the points, represented as list<Structs::Point>
	@param cellType - the cell type that the points will be marked as
*/
void Map::markCells(list<Structs::Point> points, int cellType, float resolution) {
	for (list<Structs::Point>::iterator pointsIterator = points.begin(); pointsIterator != points.end(); ++pointsIterator) {
		Structs::Point * point = pointsIterator.operator ->();

		setCellValue(point->getX(), point->getY(), cellType, resolution);
	}
}

/**
	Returns all the neighbors of a certain cell in a given ratio

	@param point - the cell point
	@param matrix - the matrix that contains the cell
	@param ratio - the neighbors ratio
	@return - the cell's neighbors, represented as list<Structs::Point>
*/
list<Structs::Point> Map::getCellsNeighbors(Structs::Point point, Matrix * matrix, int ratio) {
	list<Structs::Point> neighbors = list<Structs::Point>();

	for (int rowsIndex = point.getY() - ratio; rowsIndex <= point.getY() + ratio; rowsIndex++) {
		// Checks that the current cell is within the matrix row boundaries
		if (!(rowsIndex < 0 || rowsIndex >= matrix->getHeight())) {
			for (int columnsIndex = point.getX() - ratio; columnsIndex <= point.getX() + ratio; columnsIndex++) {
				// Checks that the current cell is within the matrix column boundaries
				if (!(columnsIndex < 0 || columnsIndex >= matrix->getWidth())) {
					Structs::Point neighbor(columnsIndex, rowsIndex);

					if (neighbor != point)
						neighbors.push_back(neighbor);
				}
			}
		}
	}

	return neighbors;
}

/**
	Pushing RGBA colors (4 bytes) to a given vector

	@param vector - the RGBA vector
	@param color - the wanted RGBA color
*/
void Map::pushRGBAColorToAVector(vector<unsigned char> * vector, int color) {
	const int* rgbaColor = Helper::getRGBA(color);

	vector->push_back(rgbaColor[0]);
	vector->push_back(rgbaColor[1]);
	vector->push_back(rgbaColor[2]);
	vector->push_back(rgbaColor[3]);
}
