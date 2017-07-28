#pragma once

#include "nn_matrix.h"


#include <fstream>

class NN
{
friend class NN_FIO;
public:
	NN(int inputs, int outputs, int hidden_layers, int nodes_per_layer);

	void save(const char* filename);

	std::vector<float> calculate(std::vector<float> input);

	int getNLayers() { return (int)m_layers.size(); }

	NN_Matrix getLayer(int id) { return m_layers[id]; }

	void setLayers(std::vector<NN_Matrix> layers) { m_layers = layers; }


private:
	std::vector<NN_Matrix> m_layers;
	int m_inputs, m_outputs, m_hiddenlayers, m_nodes;

};
