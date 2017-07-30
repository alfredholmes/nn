#include "nn_matrix.h"

NN_Matrix::NN_Matrix(int width, int height):
	m_width(width), m_height(height)
{

	srand(time(NULL));

	for(int y = 0; y < m_height; y++)
	{
		std::vector<float> row;
		for(int x = 0; x < m_width; x++)
		{
			row.push_back(((float)rand() / (float)RAND_MAX - 0.5f) * 2.0f);
		}
		m_data.push_back(row);
	}

}


NN_Matrix::NN_Matrix(int width, int height, float default_value):
	m_width(width), m_height(height)
{

	srand(time(NULL));

	for(int y = 0; y < m_height; y++)
	{
		std::vector<float> row;
		for(int x = 0; x < m_width; x++)
		{
			row.push_back(default_value);
		}
		m_data.push_back(row);
	}

}


NN_Matrix NN_Matrix::multiply(NN_Matrix const &a) const
{
	if(a.m_width != m_height)
	{
		std::cout << "ERROR MATRIX SIZE MISMATCH WITH SIZES: (" << a.m_width << ", " << m_height << ")" << std::endl;
		return NN_Matrix(0, 0);
	}
	NN_Matrix matrix(m_width, a.m_height, 0);

	std::vector<std::vector<float>> row_cache;


	for(int y = 0; y < a.m_height; y++)
	{
		for(int x = 0; x < m_width; x++)
		{
			float total = 0;
			std::vector<float> row = a.getRow(y);
			std::vector<float> column = getColumn(x);
			for(unsigned i = 0; i < row.size(); i++)
			{
				total += row[i] * column[i];
			}
			matrix.m_data[y][x] = total;
		}
	}

	return matrix;
}


std::vector<float> NN_Matrix::getColumn(int const &c) const
{
	std::vector<float> column;
	for(int y = 0; y < m_height; y++)
	{
		column.push_back(m_data[y][c]);
	}
	return column;
}



void NN_Matrix::setColumn(int id, std::vector<float> column)
{
	if(column.size() > (unsigned)m_height)
		std::cout << "WARN: COLUMN SIZE MISMATCH, EXTRA DATA WILL BE IGNORED";
	if(column.size() < (unsigned)m_height)
	{
		std::cout << "WARN: COLUMN SIZE MISMATCH, EXTRA NULL DATA WILL BE ADDDED";
		int diff = m_height - column.size();
		for(int i = 0; i < diff; i++)
			column.push_back(0);
	}
	for(int y = 0; y < m_height; y++)
	{
		m_data[y][id] = column[y];
	}
}
