#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(NN_Matrix mat);

float encode(float);
float decode(float);

int main()
{

	//Create new NN

	NN square(1, 1, 1, 1000);


	for(int i = 0; i < 1000000; i++)
	{
		//std::cout << "Iteration " << i << std::endl;
		srand(time(NULL) + i);
		float input = ((float)rand() / (float)RAND_MAX); 
		float output = input;
		
		//std::cout << output <<std::endl;
		
		//std::cout << 1 / output << std::endl;
		
		if(i % 1000 == 0)
			std::cout << i << "th iteration" << std::endl;
		//std::cout << input << " " << output << std::endl;
		
		square.backpropergation({input}, {output});
		
		}
	
	

	
	std::cout << square.calculate({0.5f})[0] << std::endl;

	square.dump();


//	test.dump();
//	loaded.dump();



	return 0;
}

float encode(float in)
{
	return 1.0f / ( 1.0f + exp(-in));
}

float decode(float out)
{
	return log(out / (out - 1.0f));
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
