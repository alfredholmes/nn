#include "nn_fio.h"

NN_FIO::NN_FIO(std::string filename):
	m_filename(filename)
{

}

void NN_FIO::save(NN const &network)
{
	std::ofstream output;
	output.open(m_filename);
	output << network.m_inputs << " " << network.m_outputs << " " << network.m_hiddenlayers << " " << network.m_nodes << " ";

	for(int i = 0; i < network.m_hiddenlayers; i++)
	{
		std::vector<std::vector<float>> matrix = network.m_layers[i].getMatrix();

		for(unsigned x = 0; x < matrix.size(); x++)
		{
			for(unsigned y = 0; y < matrix[0].size(); y++)
				output << matrix[x][y] << " ";
		}
	}

	output.close();
}

NN NN_FIO::load()
{


	std::ifstream input(m_filename);

	std::vector<float> data;
	std::string file;
	
	std::stringstream ss;

	while (std::getline(input, file))
		ss << file;
	

	std::cout << file << std::endl;

	float temp;
	while(ss >> temp)
		data.push_back(temp);

	int inputs = (int)data[0];
	int output = (int)data[1];
	int hiddenlayers = (int)data[2];
	int nodes = (int)data[3];
	


	



}