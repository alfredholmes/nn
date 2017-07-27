#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

//general matrix class of arbirary size
class NN_Matrix
{
public:
	NN_Matrix(int _width, int _height);
	NN_Matrix(int _width, int _height, float default_value);

	NN_Matrix multiply(NN_Matrix const &a);

	std::vector<std::vector<float>> getMatrix() const { return data; }

	std::vector<float> getRow(int r) const;
	std::vector<float> getColumn(int c) const;

	void setRow(std::vector<float> row, int x);
	void setColumn(std::vector<float> column, int y);

	void addRow(std::vector<float> row);
	void addColumn(std::vector<float> column);

	void setValue(float value, int x, int y) { data[x][y] = value; }
private:
	std::vector<std::vector<float>> data; //perhaps better using arrays?
	int width, height;
};