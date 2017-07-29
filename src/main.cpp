#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(std::vector<std::vector<float>> mat);

int main()
{
	//NN_FIO manager("testdata.nn");
	NN test(3, 5, 5, 3);

	

	std::vector<float> out = test.calculate({1.25, 7, 8});

	for(unsigned i = 0; i < out.size(); i++)
		std::cout << out[i] << " ";

	std::cout << std::endl;
	return 0;
}
