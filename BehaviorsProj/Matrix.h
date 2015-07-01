/*
 * Matrix.h
 *
 *  Created on: Jun 24, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

using namespace std;

class Matrix {
	vector<int> getMatrix();

private:
	vector<int> _matrix;
	int _width;
	int _height;

public:
	Matrix(int width, int height);
	Matrix(int width, int height, int value);

	int getHeight() const;
	void setHeight(int height);
	int getWidth() const;
	void setWidth(int width);

	int getCellValue(int column, int row);
	void setCellValue(int column, int row, int value);
	void initializeMatrix(int value);
	void swap(Matrix * otherMatrix);
};

#endif /* MATRIX_H_ */
