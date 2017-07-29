#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(NN_Matrix mat);

int main()
{

	//Create new NN

	NN square(1, 1, 2, 10);

	std::cout << 1 / square.calculate({10})[0] << std::endl;

	for(int i = 0; i < 1000; i++)
	{
		//std::cout << "Iteration " << i << std::endl;
		float input = rand() % 1000;
		float output = pow(input, .5);
		//std::cout << input << " " << output << std::endl;
		
		square.backpropergation({1 / input}, {1 / output});
	}
	

	
	std::cout << 1 / square.calculate({500})[0] << std::endl;

	square.dump();


//	test.dump();
//	loaded.dump();



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
