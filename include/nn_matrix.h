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
	NN_Matrix(int width, int height);

	//Construct matrix with a defailt value of 0
	NN_Matrix(int width, int height, float default_value);

	NN_Matrix multiply(NN_Matrix const &a) const;

	NN_Matrix operator*(NN_Matrix const &a) const { return a.multiply(*this); }

	std::vector<std::vector<float>> getData() const { return m_data; }

	std::vector<float> getRow(int const &r) const { return m_data[r]; };
	std::vector<float> getColumn(int const &c) const;

	void setData(std::vector<std::vector<float>> data) { m_data = data; }

	void setRow(std::vector<float> row, int x) { m_data[x] = row; }
	void setColumn(int id, std::vector<float> column);

	void addRow(std::vector<float> row);
	void addColumn(std::vector<float> column);

	float getValue(int const &x, int const &y) { return m_data[y][x]; }

	void setValue(int const &x, int const &y, float const &value) { m_data[y][x] = value; }
	void alterValue(int const &x, int const &y, float const &delta) { m_data[y][x] += delta; }

	int getHeight(){ return m_height; }
	int getWidth(){ return m_width; }



private:
	std::vector<std::vector<float>> m_data;
	int m_width, m_height;
};
