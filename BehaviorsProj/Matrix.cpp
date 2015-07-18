/*
 * Matrix.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Matrix.h"

/**
	Initializes the Matrix.

	@param width - the width of the matrix.
	@param height - the height of the matrix.
	@param value - the value to initialize every cell in the matrix.
*/
Matrix::Matrix(int width, int height, int value) {
	_matrix = vector<int>();

	setWidth(width);
	setHeight(height);

	if (value != -1)
	initializeMatrix(value);
}

/**
	GetHeight of the matrix.

	@return - the height of the matrix.
 */
int Matrix::getHeight() const {
	return _height;
}

/**
	SetHeight of the matrix.

	@param height - the height of the matrix.
 */
void Matrix::setHeight(int height) {
	_height = height;
}

/**
	GetWidth of the matrix.

	@return - the width of the matrix.
 */
int Matrix::getWidth() const {
	return _width;
}

/**
	SetWidth of the matrix.

	@param width - the width of the matrix.
 */
void Matrix::setWidth(int width) {
	_width = width;
}

/**
	GetMatrix.

	@return - the matrix.
 */
vector<int> Matrix::getMatrix() {
	return _matrix;
}

/**
	GetCellValue from the matrix by column and row.

	@param column - the column index from the matrix.
	@param row - the row index from the matrix.
	@return - the value in the wanted cell.
 */
int Matrix::getCellValue(int column, int row) {
	return _matrix.at((row * getWidth()) + column);
}

/**
	SetCellValue in the matrix by column and row.

	@param column - the column index from the matrix.
	@param row - the row index from the matrix.
	@param value - the value to set in the wanted cell.
 */
void Matrix::setCellValue(int column, int row, int value) {
	_matrix[(row * getWidth()) + column] = value;
}

/**
	InitializeMatrix with wanted value all the cells in the matrix.

	@param value - the wanted value to set every cell in the matrix.
 */
void Matrix::initializeMatrix(int value) {
	for (int rowsIndex = 0; rowsIndex < getHeight() ; rowsIndex++)
		for (int columnsIndex = 0; columnsIndex < getWidth() ; columnsIndex++)
			_matrix.push_back(value);
}

/**
	This method swap between two matrixes.

	@param otherMatrix - other matrix.
 */
void Matrix::swap(Matrix * otherMatrix) {
	_matrix.swap(otherMatrix->_matrix);
}
