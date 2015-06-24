/*
 * Matrix.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Matrix.h"

Matrix::Matrix(int width, int height, int value) {
	_matrix = vector<int>();

	setWidth(width);
	setHeight(height);

	if (value != -1)
	initializeMatrix(value);
}

int Matrix::getHeight() const {
	return _height;
}

void Matrix::setHeight(int height) {
	_height = height;
}

int Matrix::getWidth() const {
	return _width;
}

void Matrix::setWidth(int width) {
	_width = width;
}

vector<int> Matrix::getMatrix() {
	return _matrix;
}

int Matrix::getCellValue(int column, int row) {
	return _matrix.at((row * getWidth()) + column);
}

void Matrix::setCellValue(int column, int row, int value) {
	_matrix[(row * getWidth()) + column] = value;
}

void Matrix::initializeMatrix(int value) {
	for (int rowsIndex = 0; rowsIndex < getHeight() ; rowsIndex++)
		for (int columnsIndex = 0; columnsIndex < getWidth() ; columnsIndex++)
			_matrix.push_back(value);
}

void Matrix::swap(Matrix otherMatrix) {
	_matrix.swap(otherMatrix._matrix);
}
