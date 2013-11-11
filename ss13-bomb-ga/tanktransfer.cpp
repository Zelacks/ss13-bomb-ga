#include "tanktransfer.h"
#include <string>
#include <cstring>
#include <cstdlib>

TankTransfer::TankTransfer()
{
	m_tankOne = new Tank();
	m_tankTwo = new Tank();

}

void TankTransfer::mergeGases()
{
	m_tankTwo->m_gasMix->m_volume += m_tankOne->m_gasMix->m_volume;

	GasMix tempGas;

	tempGas = m_tankOne->m_gasMix->remove_ratio(1);
	m_tankTwo->m_gasMix->merge(tempGas);
}


void TankTransfer::loadGenome()
{
	m_tankOne->m_volume = 70;
	m_tankTwo->m_volume = 70;

	m_tankOne->m_gasMix->m_volume = 70;
	m_tankTwo->m_gasMix->m_volume = 70;

	m_tankOne->explosiveFitness = 0;
	m_tankTwo->explosiveFitness = 0;
	m_tankOne->isDeleted = false;
	m_tankTwo->isDeleted = false;

	m_tankOne->integrity = 3;
	m_tankTwo->integrity = 3;

	std::vector<float> tankOneVals;
	for (int i = 0;i < 5; i++)
	{
		tankOneVals.push_back(m_genome[i]);
	}
	m_tankOne->calcStartMoles(tankOneVals);

	std::vector<float> tankTwoVals;
	for (int i = 5;i < 10; i++)
	{
		tankTwoVals.push_back(m_genome[i]);
	}
	m_tankTwo->calcStartMoles(tankTwoVals);
}

void TankTransfer::hardLoadGenome()
{
	m_tankOne->m_volume = 70;
	m_tankTwo->m_volume = 70;

	m_tankOne->m_gasMix->m_volume = 70;
	m_tankTwo->m_gasMix->m_volume = 70;

	m_tankOne->explosiveFitness = 0;
	m_tankTwo->explosiveFitness = 0;
	m_tankOne->isDeleted = false;
	m_tankTwo->isDeleted = false;

	m_tankOne->integrity = 3;
	m_tankTwo->integrity = 3;

	std::vector<float> tankOneVals;
	tankOneVals.push_back(0.012909329); //oxygen
	tankOneVals.push_back(0.84871978); //carbon dioxide
	tankOneVals.push_back(0.53337198); //nitrogen
	tankOneVals.push_back(0.14142278); //toxins
	tankOneVals.push_back(0.48710594); //temp
	m_tankOne->calcStartMoles(tankOneVals);

	std::vector<float> tankTwoVals;
	tankTwoVals.push_back(0.88125247); //oxygen
	tankTwoVals.push_back(0.00054933317); //carbon dioxide
	tankTwoVals.push_back(0.00000305185); //nitrogen
	tankTwoVals.push_back(0.23960082); //toxins
	tankTwoVals.push_back(0.0025635548); //temp
	m_tankTwo->calcStartMoles(tankTwoVals);
}

void TankTransfer::fileLoadGenome(std::ifstream &genomes)
{
	m_tankOne->m_volume = 70;
	m_tankTwo->m_volume = 70;

	m_tankOne->m_gasMix->m_volume = 70;
	m_tankTwo->m_gasMix->m_volume = 70;

	m_tankOne->explosiveFitness = 0;
	m_tankTwo->explosiveFitness = 0;
	m_tankOne->isDeleted = false;
	m_tankTwo->isDeleted = false;

	m_tankOne->integrity = 3;
	m_tankTwo->integrity = 3;

	std::string strings;
	std::getline(genomes, strings);
	strings = strings.substr(8, strings.size()-1);
	char *cstring = new char [strings.length()+1];
	std::strcpy (cstring, strings.c_str());

	char * pch;
	pch = strtok (cstring, " ");

	std::vector<float> tankOneVals;
	for (int i = 0; i < 5; i++)
	{
		tankOneVals.push_back(atof(pch));
		pch = strtok(NULL," ");
	}
	m_tankOne->calcStartMoles(tankOneVals);

	std::vector<float> tankTwoVals;
	for (int i = 0; i < 5; i++)
	{
		tankTwoVals.push_back(atof(pch));
		pch = strtok(NULL," ");
	}
	m_tankTwo->calcStartMoles(tankTwoVals);


	if (atof(pch))
		m_processAmount = 50 + (atof(pch)*1000);
	else
		m_processAmount = 300;


	delete[] cstring;

}

