#include <iostream>
#include "nn_matrix.h"

void print_matrix(std::vector<std::vector<float>> mat);

int main()
{

	NN_Matrix mat1(2, 2, 1);
	NN_Matrix mat2(2, 2, 5);

	print_matrix(mat1.multiply(mat2).getMatrix());

	return 0;
}


void print_matrix(std::vector<std::vector<float>> mat)
{
	std::cout << "[" << std::endl;
	for(int y = 0; y < mat[0].size(); y++)
	{
		for(int x = 0; x < mat.size(); x++)
		{
			std::cout << mat[x][y] << "     ";
		}
		std::cout << std::endl;
	}

	std::cout << "]" << std::endl;
}