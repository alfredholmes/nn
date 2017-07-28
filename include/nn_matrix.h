#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

#include <iostream>

//general matrix class of arbirary size
class NN_Matrix
{
public:
	//Construct matrix with random values between 0 and 1
	NN_Matrix(int _width, int _height);
	
	//Construct matrix with a defailt value of 0
	NN_Matrix(int _width, int _height, float default_value);

	NN_Matrix multiply(NN_Matrix const &a) const;

	NN_Matrix operator*(NN_Matrix const &a) const { return a.multiply(*this); }

	std::vector<std::vector<float>> getMatrix() const { return m_data; }

	std::vector<float> getRow(int const &r) const;
	std::vector<float> getColumn(int const &c) const;

	void setData(std::vector<std::vector<float>> data) { m_data = data; }

	void setRow(std::vector<float> row, int x);
	void setColumn(std::vector<float> column, int y);

	void addRow(std::vector<float> row);
	void addColumn(std::vector<float> column);

	void setValue(float const &value, int const &x, int const &y) { m_data[x][y] = value; }
private:
	std::vector<std::vector<float>> m_data;
	int width, height;
};