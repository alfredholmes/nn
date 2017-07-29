#include "nn_fio.h"

NN_FIO::NN_FIO(std::string filename):
	m_filename(filename)
{

}

void NN_FIO::save(NN const &network)
{
	std::ofstream output;
	output.open(m_filename);
	output << network.m_inputs << " " << network.m_outputs << " " << network.m_hidden_layers << " " << network.m_nodes << " ";

	for(int i = 0; i < network.m_hidden_layers; i++)
	{
		std::vector<std::vector<float>> matrix = network.m_layers[i].getData();

		for(unsigned y = 0; y < matrix.size(); y++)
		{
			for(unsigned x = 0; x < matrix[y].size(); x++)
				output << matrix[y][x] << " ";
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




	float temp;
	while(ss >> temp)
		data.push_back(temp);

	int inputs = (int)data[0];
	int outputs = (int)data[1];
	int hidden_layers = (int)data[2];
	int nodes = (int)data[3];

	std::vector<NN_Matrix> layers;
	int offset = 4;
	if(hidden_layers == 1)
	{

		NN_Matrix mat(outputs, inputs);
		for(int y = 0; y < inputs; y++)
		{
			for(int x = 0; x < outputs; x++)
				mat.setValue(x, y, data[offset + x + y * inputs]);
		}

		layers.push_back(mat);
	}else{
		for(int i = 0; i < hidden_layers; i++)
		{
			if(i == 0)
			{
				NN_Matrix mat(inputs, nodes);
				for(int y = 0; y < nodes; y++)
				{
					for(int x = 0; x < inputs; x++)
						mat.setValue(x, y, data[offset + x + y * inputs]);
				}
				layers.push_back(mat);
			}else if(i == hidden_layers - 1)
			{
				NN_Matrix mat(nodes, outputs);

				for(int y = 0; y < outputs; y++)
				{

					for(int x = 0; x < nodes; x++)
					{

						mat.setValue(x, y, data[offset + (i-1) * nodes * nodes + inputs * nodes + x + y * nodes]);
					}

				}
				layers.push_back(mat);
			}else{
				NN_Matrix mat(nodes, nodes);
				for(int y = 0; y < nodes; y++)
				{
					for(int x = 0; x < nodes; x++)
						mat.setValue(x, y, data[offset + nodes*inputs + (i-1)*nodes * nodes + x + y * nodes]);
				}
				layers.push_back(mat);
			}
		}
	}


	 NN network(inputs, outputs, hidden_layers, nodes);
	 network.setLayers(layers);


	 return network;



}
