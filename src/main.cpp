#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(NN_Matrix mat);

int main()
{
	NN_FIO manager("testdata.nn");
	NN test(1, 1, 2, 5);


	manager.save(test);


	std::vector<float> out = test.calculate({5});

	for(unsigned i = 0; i < out.size(); i++)
		std::cout << out[i] << " " ;

	std::cout << std::endl;

	NN loaded = manager.load();
	//NN loaded = test;
	out = loaded.calculate({5});

	for(unsigned i = 0; i < out.size(); i++)
		std::cout << out[i] << " ";

	out = loaded.calculate({5});

	for(unsigned i = 0; i < out.size(); i++)
		std::cout << out[i] << " ";

	std::cout << std::endl;


	test.dump();
	loaded.dump();



	return 0;
}

void print_matrix(NN_Matrix mat)
{
	std::vector<std::vector<float>> data = mat.getData();
	for(unsigned y = 0; y < data.size(); y++)
	{
		for(unsigned x = 0; x < data[y].size(); x++)
			std::cout << data[y][x] << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl;

}
