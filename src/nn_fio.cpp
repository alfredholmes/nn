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
	int outputs = (int)data[1];
	int hiddenlayers = (int)data[2];
	int nodes = (int)data[3];

	std::vector<NN_Matrix> layers;
	int offset = 3;
	for(int i = 0; i < hiddenlayers; i++)
	{
		std::cout << "Creating layer " << i << std::endl;
		if(i == 0)
		{
			NN_Matrix mat(inputs, nodes);
			for(int y = 0; y < nodes; y++)
			{
				for(int x = 0; x < inputs; x++)
					mat.setValue(data[offset + x + y * inputs], x, y);
			}
			layers.push_back(mat);
		}else if(i == hiddenlayers - 1)
		{
			NN_Matrix(nodes, nodes);
			NN_Matrix mat(nodes, nodes);
			for(int y = 0; y < nodes; y++)
			{
				for(int x = 0; x < nodes; x++)
					mat.setValue(data[offset + nodes*inputs + (i-1)*nodes * nodes + x + y * nodes], x, y);
			}
			layers.push_back(mat);
		}else{
			NN_Matrix(nodes, outputs);
			NN_Matrix mat(nodes, outputs);
			for(int y = 0; y < outputs; y++)
			{
				for(int x = 0; x < nodes; x++)
					mat.setValue(data[offset + nodes*inputs + (i-1)*nodes * nodes + x + y * nodes], x, y);
			}
			layers.push_back(mat);
		}
	}

	 NN network(inputs, outputs, hiddenlayers, nodes);
	 network.setLayers(layers);

	 return network;



}
