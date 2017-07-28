#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(std::vector<std::vector<float>> mat);

int main()
{
	NN_FIO manager("testdata.nn");
	NN test = manager.load();


	std::cout << test.getNLayers() << std::endl;
	//manager.save(test);

	return 0;
}
