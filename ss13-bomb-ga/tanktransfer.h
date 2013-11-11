#ifndef TANKTRANSFER_H
#define TANKTRANSFER_H

#include "tank.h"
#include <vector>
#include <fstream>

class TankTransfer
{
public:

	TankTransfer();
	void mergeGases();

	Tank *m_tankOne;
	Tank *m_tankTwo;

	void loadGenome();
	void hardLoadGenome();
	void fileLoadGenome(std::ifstream &genomes);
	
	void setGenome(std::vector<float> theGenome){m_genome = theGenome;}

	int m_processAmount;
	int m_index;
	std::vector<float> m_genome;

private:

};

#endif