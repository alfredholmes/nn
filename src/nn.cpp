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
	{
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
void NN::backpropergation(std::vector<float> const &inputs, std::vector<float> const &outputs)
{
	float learning_rate = 0.001;
	for(int i = m_layers.size() - 1; i >= 0; i--)
	{
		std::vector<float> previous_layer_output = calculate(inputs, i);

		previous_layer_output = NN::batchActivation(previous_layer_output);

		NN_Matrix input(1, previous_layer_output.size());
		input.setColumn(0, previous_layer_output);
		
		
		std::vector<float> calculated_outputs = input.multiply(m_layers[i]).getColumn(0);
		
		//std::cout << m_layers[i].getData()[0][0] << std::endl;


		for(int y = 0; y < m_layers[i].getHeight(); y++)
		{
			for(int x = 0; x < m_layers[i].getWidth(); x++)
			{
				float o = previous_layer_output[x];
				float d = delta(y, i + 1, outputs, calculated_outputs);
				
				
			
				m_layers[i].alterValue(x, y, -1.0 * learning_rate * o * d);
			}
		}
	}
}

float NN::delta(int j, int layer, std::vector<float> const &outputs, std::vector<float> const &calculated_outputs)
{
	
	if(layer == (int)m_layers.size())
	{

		return (calculated_outputs[j] - outputs[j]) * calculated_outputs[j] * (1 - calculated_outputs[j]);
	}else{
		float total = 0;
		for(int x = 0; x < m_layers[layer].getHeight(); x++)
		{
			
			NN_Matrix input(1, calculated_outputs.size());
			input.setColumn(0, calculated_outputs);
			
			std::vector<float> next_ouput = input.multiply(m_layers[layer]).getColumn(0);
			next_ouput = NN::batchActivation(next_ouput);
			total += delta(x, layer + 1, outputs, next_ouput) * calculated_outputs[j] *  (1 - calculated_outputs[j]);
			
		}
		std::cout << total << std::endl;
		return total;
	}
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
