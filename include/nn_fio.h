#pragma once

#include <string>
#include <sstream>
#include <fstream>

#include "nn.h"

class NN_FIO
{
public:
	NN_FIO(std::string filename);
	NN load();
	void save(NN const &network);

private:
	std::string m_filename;
};