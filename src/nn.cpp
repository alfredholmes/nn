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
	//return x;
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
	{
		std::cout << "WARN LAYER REQUEST OUT OF RANGE, WILL RETURN FULL NETWORK CALCULATION" << std::endl;
		layer = m_layers.size();
	}
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
void NN::backpropagation(std::vector<float> const &inputs, std::vector<float> const &outputs)
{
	
	//loop through the network layer by layer backwards
	//l will be the id of the layer matrix in the m_layers vector
	for(int l = m_hidden_layers - 1; l >= 0; l--)
	{
		
		float err = error(calculate(inputs), outputs); //useful thing to have
		
		//get a list of the prevous layer outputs or inputs to this layer
		std::vector<float> in = calculate(inputs, l); //not l - 1 because l is the less than value in for loop
		
		//loop through the layer matrix
		for(int y = 0; y < m_layers[l].getHeight(); y++)
		{
			for(int x = 0; x < m_layers[l].getWidth(); x++)
			{
				//We are considering the weight (x, y) in the matrix
				//this value is the weight from in[x] to out[y]
				float o_i = in[x];
				//the delta function is concerned with the next layer
				float d_j = delta(y, l + 1, inputs, outputs);
				
				float change = -1 * pow(err, 0.5) * o_i * d_j; 
			
				m_layers[l].alterValue(x, y, change);
			}
		}
	}
	//clean cache
	delta_cache = {};
}

float NN::delta(int j, int layer, std::vector<float> const &inputs, std::vector<float> const &outputs)
{
	
	if(delta_cache.count(layer) == 1)
	{
		if(delta_cache[layer].count(j) == 1)
			return delta_cache[layer][j];
	}
	
	std::vector<float> out = calculate(inputs, layer);
	
	//if this is the output layer then no recursion required
	if(layer == m_hidden_layers)
	{
		delta_cache[layer][j] = (out[j] - outputs[j]) * out[j] *  (1 - out[j]);
		return (out[j] - outputs[j]) * out[j] *  (1 - out[j]);

	}
	//otherwise do some dank recursion
	//this is the sum in the wikipedia page
	//the nuber of outputs connected to this neuron is the height of the matrix
	float total = 0;
	for(int l = 0; l < m_layers[layer].getHeight(); l++)
	{
		//for each output that the node is connected to we are intrested in
		//the connecting weight and the delta of that node
		float weight = m_layers[layer].getValue(j, l); //just from weight matrix
		//float weight = 0;
		
		float d = delta(l, layer + 1, inputs, outputs);
		
		total += weight * d;
		
	}
	
	float r = total * out[j] * (1 - out[j]);
	delta_cache[layer][j] = r;
	return r;
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
