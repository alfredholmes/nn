#include "nn.h"

NN::NN(int inputs, int outputs, int hidden_layers, int nodes_per_layer):
	m_inputs(inputs), m_outputs(outputs), m_hiddenlayers(hidden_layers), m_nodes(nodes_per_layer)
{
	for(int i = 0; i < m_hiddenlayers; i++)
	{
		if(i == 0)
			m_layers.push_back(NN_Matrix(nodes_per_layer, inputs));
		else if(i == m_hiddenlayers - 1)
			m_layers.push_back(NN_Matrix(outputs, nodes_per_layer));
		else
			m_layers.push_back(NN_Matrix(nodes_per_layer, nodes_per_layer));
	}
}
