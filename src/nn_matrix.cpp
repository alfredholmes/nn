#include "nn_matrix.h"

NN_Matrix::NN_Matrix(int _width, int _height)
{
	width = _width;
	height = _height;

	srand(time(NULL));

	for(int x = 0; x < width; x++)
	{
		std::vector<float> column;
		for(int y = 0; y < height; y++)
		{
			column.push_back((float)rand() / (float)RAND_MAX);
		}
		data.push_back(column);
	}
	
}


NN_Matrix::NN_Matrix(int _width, int _height, float default_value)
{
	width = _width;
	height = _height;
	srand(time(NULL));

	for(int x = 0; x < width; x++)
	{
		std::vector<float> column;
		for(int y = 0; y < height; y++)
		{
			column.push_back(default_value);
		}
		data.push_back(column);
	}
	
}


NN_Matrix NN_Matrix::multiply(NN_Matrix const &a) //needs optimisation
{
	if(a.width != height || a.height != width)
		return NN_Matrix(0, 0); //do some logging

	NN_Matrix matrix(width, a.height, 0);

	for(int x = 0; x < width; x++)
	{
		std::vector<float> column = getColumn(x);
		for(int y = 0; y < a.height; y++)
		{
			std::vector<float> row = a.getRow(y);
			float total = 0;
			for(int i = 0; i < a.width; i++)
				total += column[i] * row[i];
			matrix.data[x][y] = total;
		}
	}

	return matrix;
}


std::vector<float> NN_Matrix::getColumn(int c) const
{
	return data[c];
}

std::vector<float> NN_Matrix::getRow(int r) const
{
	std::vector<float> row;
	for(int y = 0; y < height; y++)
	{
		row.push_back(data[r][y]);
	}
	return row;
}

