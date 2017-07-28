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
		m_data.push_back(column);
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
		m_data.push_back(column);
	}

}


NN_Matrix NN_Matrix::multiply(NN_Matrix const &a) const //needs optimisation
{
	if(a.width != height || a.height != width)
		return NN_Matrix(0, 0); //do some logging

	//create matrix for return
	NN_Matrix matrix(width, a.width, 0);

	//cache rows - there was an odd error here with some really large numbers which
	// is removed when the cache is not used - not sure.
	/*std::vector<std::vector<float>> rows;

	for(int y = 0; y < a.width; y++)
		rows.push_back(a.getRow(y));
	*/
	//calculate the value for each element in new matrix
	//not sure about optimisation for this
	for(int x = 0; x < width; x++)
	{
		std::vector<float> column = getColumn(x);
		for(int y = 0; y < a.width; y++)
		{

			std::vector<float> row = a.getRow(y); //should be using cache
			float total = 0;
			for(int i = 0; i < a.width; i++)
			{
				total += column[i] * row[i];
			}
			matrix.m_data[x][y] = total;
		}
	}

	return matrix;
}


std::vector<float> NN_Matrix::getColumn(int const &c) const
{
	return m_data[c];
}

std::vector<float> NN_Matrix::getRow(int const &r) const
{
	std::vector<float> row;
	for(int y = 0; y < height; y++)
	{
		row.push_back(m_data[r][y]);
	}



	return row;
}
