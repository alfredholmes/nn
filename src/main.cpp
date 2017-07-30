#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(NN_Matrix mat);

float encode(float);

int main()
{
	std::ifstream races;
	races.open("data/output.csv");
	std::string line;

	NN_FIO manager("predictor.nn");
	NN predictor(25, 25, 3, 25);
	int iter = 0;
	while (std::getline(races, line))
	{
		std::cout << iter++ << std::endl;
		
		std::stringstream ss;
		ss << line;
		
		std::vector<float> data;
		float temp;
		while(ss >> temp)
			data.push_back(temp);

		int size = data.size();
	
	
		if(size % 2 != 0)
			continue;
		
		
		std::vector<float> output;
		std::vector<float> input;
		
		for(int i = 0; i < size / 2; i++)
			output.push_back(data[i]);
			
		for(int i = size / 2; i < size; i++)
			input.push_back(encode(data[i]));
			
		for(int i = size / 2; i < 25; i++)
		{
			input.push_back(0);
			output.push_back(0);
		}
		
		predictor.backpropagation(input, output);
			
		}
		races.close();
		
		
		manager.save(predictor);
		
		std::vector<float> predictions = predictor.calculate({encode(20), encode(16), encode(9.4), encode(3.7), encode(3.55),encode(13.5), encode(9), encode(7.2), encode(20), 0,0, 0, 0, 0, 0,0, 0, 0, 0, 0,0, 0, 0, 0, 0});
		for(float prob : predictions)
		{
			std::cout << prob  << "\n";
			
		}
		std::cout << std::endl;
		
		return 0;
		
}

float encode(float x)
{
	return 1.0f / (1.0f + exp(-x));
}

