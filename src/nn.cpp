#include "nn.h"

NN::NN(int inputs, int outputs, int hidden_layers, int nodes_per_layer):
	m_inputs(inputs), m_outputs(outputs), m_hidden_layers(hidden_layers), m_nodes(nodes_per_layer)
{
	if(m_hidden_layers == 1){
		m_layers.push_back(NN_Matrix(m_inputs, m_outputs));
	}else{
	for(int i = 0; i < m_hidden_layers; i++)
	{
			if(i == 0)
				m_layers.push_back(NN_Matrix(inputs, nodes_per_layer));
			else if(i == m_hidden_layers - 1)
				m_layers.push_back(NN_Matrix(nodes_per_layer, outputs));
			else
				m_layers.push_back(NN_Matrix(nodes_per_layer, nodes_per_layer));
		}
	}
}


float NN::activation(float x)
{
	return 1.0f / (1 + exp(-x));
}

std::vector<float> NN::batchActivation(std::vector<float> input)
{

	std::vector<float> output;

	for(unsigned i = 0; i < input.size(); i++)
		output.push_back(NN::activation(input[i]));

	return output;

}


std::vector<float> NN::calculate(std::vector<float> input)
{
	NN_Matrix in(1, m_inputs, 0);
	in.setColumn(0, input);
	for(unsigned i = 0; i < m_layers.size(); i++)
	{
		in = in.multiply(m_layers[i]);

		std::vector<float> out = NN::batchActivation(in.getColumn(0));

		NN_Matrix mat(1, out.size(), 0);
		mat.setColumn(0, out);
		in = mat;
	}

	return in.getColumn(0);
}

void NN::dump()
{
	std::cout << "DUMPING NEURAL NETWORK TO CL" << std::endl;
	std::cout << "Number of Layers: " << m_layers.size() << std::endl;
	std::cout << "Nodes per layer: " << m_nodes << std::endl;
	std::cout << "Inputs: " << m_inputs << std::endl;
	std::cout << "Outputs " << m_outputs << std::endl;
	std::cout << "Layers:" << std::endl;

	for(unsigned i = 0; i < m_layers.size(); i++)
	{
		std::vector<std::vector<float>> data = m_layers[i].getData();
		for(unsigned y = 0; y < data.size(); y++)
		{
			for(unsigned x = 0; x < data[y].size(); x++)
				std::cout << data[y][x] << " ";
			std::cout << std::endl;
		}

		std::cout << std::endl;
	}
}
