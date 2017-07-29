#pragma once

#include "math.h"
#include "nn_matrix.h"


#include <fstream>

class NN
{
friend class NN_FIO;
public:
	NN(int inputs, int outputs, int hidden_layers, int nodes_per_layer);

	std::vector<float> calculate(std::vector<float> input);

	void save(const char* filename);



	int getNLayers() { return (int)m_layers.size(); }

	NN_Matrix getLayer(int id) { return m_layers[id]; }

	void setLayers(std::vector<NN_Matrix> layers) { m_layers = layers; } //do some error checking or automatically update int metadata
	void selLayer(int layer, NN_Matrix data) { m_layers[layer] = data; }


private:
	static inline float activation(float x);
	static inline std::vector<float> batchActivation(std::vector<float> inoput);
	std::vector<NN_Matrix> m_layers;
	int m_inputs, m_outputs, m_hiddenlayers, m_nodes;

};
