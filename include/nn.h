#pragma once

#include "math.h"
#include "nn_matrix.h"
#include <map>

#include <fstream>

class NN
{
friend class NN_FIO;
public:
	NN(int inputs, int outputs, int hidden_layers, int nodes_per_layer);

	std::vector<float> calculate(std::vector<float> const &input, int layer=-1);

	void backpropergation(std::vector<float> const &inputs, std::vector<float> const &outputs);



	int getNLayers() { return (int)m_layers.size(); }

	NN_Matrix getLayer(int const &id) { return m_layers[id]; }

	void setLayers(std::vector<NN_Matrix> const  &layers) { m_layers = layers; }
	void selLayer(int layer, NN_Matrix data) { m_layers[layer] = data; }

	void dump();
	
	float error(std::vector<float> const &network, std::vector<float> const &output);

private:
	static inline float activation(float x);
	static inline std::vector<float> batchActivation(std::vector<float> input);
	std::vector<NN_Matrix> m_layers;
	int m_inputs, m_outputs, m_hidden_layers, m_nodes;

	float delta(int j, int layer, std::vector<float> const &inputs, std::vector<float> const &outputs);
	std::map<int, std::map<int, float>> delta_cache;


};
