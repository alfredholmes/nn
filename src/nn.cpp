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
	return 1.0f / (1.0f + exp(-1.0f * x));
}

std::vector<float> NN::batchActivation(std::vector<float> input)
{

	std::vector<float> output;

	for(unsigned i = 0; i < input.size(); i++)
		output.push_back(NN::activation(input[i]));

	return output;

}


std::vector<float> NN::calculate(std::vector<float> const &input, int layer)
{
	if(layer == -1)
		layer = m_layers.size();
	if(layer > m_layers.size())
		layer = m_layers.size();
	NN_Matrix in(1, m_inputs, 0);
	in.setColumn(0, input);
	for(int i = 0; i < layer; i++)
	{
		in = in.multiply(m_layers[i]);

		std::vector<float> out = NN::batchActivation(in.getColumn(0));

		NN_Matrix mat(1, out.size(), 0);
		mat.setColumn(0, out);
		in = mat;
	}

	return in.getColumn(0);
}

//algorithm copied from https://en.wikipedia.org/wiki/Backpropagation#Derivation
void NN::backpropergation(std::vector<float> const &inputs, std::vector<float> const &outputs)
{
	//std::cout << outputs[0] << std::endl;
//	std::cout << e << std::endl;
	float e = error(calculate(inputs), outputs);
	
	for(int i = m_hidden_layers; i > 0; i--)
	{
		//std::cout << i << std::endl;
		//calculate the vector for o_i
		std::vector<float> input_vector = calculate(inputs, i);
		
		//loop through the rows in the later matrix
		//the rows of the matrix are the input weights for one of the next nodes
		for(int x = 0; x < m_layers[i - 1].getWidth(); x++)
		{
			//loop through the layer inputs, the element in matrix with coords (m, y) is
			//the weight of the arc connecting the jth element in the inputs to the yth
			//output
			for(unsigned m = 0; m < input_vector.size(); m++)
			{
				float o_i = input_vector[m];
				float d_j = delta(m, i, inputs, outputs);
				
				//std::cout << m_layers[i - 1].getValue(x, j) << std::endl;
				//std::cout << input_vector.size() << " " << m_layers[i -1].getWidth() << " " << m_layers[i -1].getHeight() << std::endl;
				m_layers[i - 1].alterValue(x, m, -.01 * e * o_i * d_j);
			}
		}
		
	}
}

float NN::delta(int j, int layer, std::vector<float> const &inputs, std::vector<float> const &outputs)
{

	if(delta_cache.count(layer) == 1)
	{
		if(delta_cache[layer].count(j) == 1)
			return delta_cache[layer][j];
	}
	float o_j = calculate(inputs, layer)[j];
	
	//easy to compute of neuron is output
	if(layer == m_hidden_layers)
	{
		delta_cache[layer][j] = (o_j - outputs[j]) * o_j * (1 - o_j);
		return (o_j - outputs[j]) * o_j * (1 - o_j);
	}
	//otherwise sum all the deltas multiplied by the weights to calculate this
	//to do this go through the vertical of the matrix and pick out the jth horizontal element
	float total = 0;
	for(int y = 0; y  < m_layers[layer].getHeight(); y++)
	{
		float weight = m_layers[layer].getValue(j, y);

		float d = delta(y, layer + 1, inputs, outputs);
		
		total += d * weight;
	}
	delta_cache[layer][j] = total * o_j * (1 - o_j);
	return total * o_j * (1 - o_j);
	
}

float NN::error(std::vector<float> const &network, std::vector<float> const &output)
{
	if(network.size() != output.size())
	{
		std::cout << "ERROR CALCULATING ERROR FUNCTION, SIZE MISMATCH" << std::endl;
		return -1;
	}
	float total = 0;
	for(unsigned i = 0; i < network.size(); i++)
	{
		total += pow((network[i] - output[i]), 2);
	}
	return total;
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
