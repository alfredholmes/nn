#include <iostream>
#include "nn.h"
#include "nn_fio.h"

void print_matrix(NN_Matrix mat);

float encode(float);
float decode(float);

void train(int iterations, NN &network);

int main()
{

	//Create new NN
	NN_FIO manager("copycat.nn");
	NN square = manager.load();
	bool running = true;
	while(running)
	{
		std::cout << "Welcome to the NN interface" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "0) Quit." << std::endl;
		std::cout << "1) Run a calculation through the network" << std::endl;
		std::cout << "2) Train the networrk" << std::endl;
		std::string x;
		std::cin >> x;
		int choice = 0;
		try
		{
			choice = std::stoi(x);
		}
		catch(...)
		{
			std::cout << "Error processing input, please try again" << std::endl;
			continue;
		}
		
		if(choice == 0)
			running = false;
			
		if(choice == 1)
		{
			std::cout << "Enter a value between 0 and 1" << std::endl;
			std::cin >> x;
			try
			{
				float in = std::stof(x);
				std::cout << "Result from input: " << in << " " << square.calculate({in})[0] << std::endl;
			}
			catch(...)
			{
				std::cout << "Invalid input" << std::endl;
				continue;
			}
		}
		
		if(choice == 2)
		{
			std::cout << "Enter a the number of iterations" << std::endl;
			std::cin >> x;
			try
			{
				int in = std::stoi(x);
				std::cout << "Starting traning with " << in << " iterations" << std::endl;
				train(in, square);
				std::cout << "Done" << std::endl;

			}
			catch(...)
			{
				std::cout << "Invalid input" << std::endl;
				continue;
			}
		}

	/*for(int i = 0; i < 3000; i++)
	{
		//std::cout << "Iteration " << i << std::endl;
		srand(time(NULL) + i);
		float input = rand()  / (float)RAND_MAX; 
		//float output = input;
		
		//std::cout << output <<std::endl;
		
		//std::cout << 1 / output << std::endl;
		
		if(i % 1000 == 0)
			std::cout << i << "th iteration" << std::endl;
		//std::cout << input << " " << output << std::endl;
		
		square.backpropagation({input}, {input});
		
		}
	*/
	
	}
	
	//square.dump();


//	test.dump();
//	loaded.dump();
	manager.save(square);


	return 0;
}

void train(int iterations, NN &network)
{
	for(int i = 0; i < iterations; i++)
	{
		//std::cout << "Iteration " << i << std::endl;
		srand(time(NULL) + i);
		float input = rand()  / (float)RAND_MAX; 
		//float output = input;
		
		//std::cout << output <<std::endl;
		
		//std::cout << 1 / output << std::endl;
		
		if(i % 1000 == 0)
			std::cout << i << "th iteration" << std::endl;
		//std::cout << input << " " << output << std::endl;
		
		network.backpropagation({input}, {input});
		
		}
}

float encode(float in)
{
	
	return 1.0 / ( 1.0 + exp(-in / 1000));
}

float decode(float out)
{
	return 1000 * log(out / (1.0 - out));
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
