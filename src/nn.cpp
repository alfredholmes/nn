#include "nn.h"

NN::NN(int inputs, int outputs, int hidden_layers, int nodes_per_layer):
	m_inputs(inputs), m_outputs(outputs), m_hiddenlayers(hidden_layers), m_nodes(nodes_per_layer)
{
	for(int i = 0; i < m_hiddenlayers; i++)
	{
		if(i == 0)
			m_layers.push_back(NN_Matrix(nodes_per_layer, inputs));
		else if(i == m_hiddenlayers - 1)
			m_layers.push_back(NN_Matrix(nodes_per_layer, outputs));
		else
			m_layers.push_back(NN_Matrix(nodes_per_layer, nodes_per_layer));
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
	NN_Matrix in(1, input.size(), 0);
	in.setColumn(0, input);
	for(unsigned i = 0; i < m_layers.size(); i++)
	{
		in = m_layers[i] * in;

		std::vector<float> out = NN::batchActivation(in.getColumn(0));

		NN_Matrix mat(1, out.size(), 0);
		mat.setColumn(0, out);
		in = mat;
	}

	return in.getColumn(0);
}
