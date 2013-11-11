#include "tanktransfer.h"
#include "genAlg.h"
#include <iostream>
#include <fstream>

GenAlg *geneManager;
TankTransfer currentTank;

long int generation = 0;
void mainGameLoop();
void testOne();
bool stop = false;

std::ofstream outputGene("outputGene.txt");
std::ifstream inputGene("inputGene.txt");
void outputToFileGene(int index);
void fitnessTest();
int processAmount = 0;
bool testOneBool = false;
int main()
{

	geneManager = new GenAlg(15, 11);
	geneManager->setMutationRate(0.35);
	geneManager->setSurvivalRate(0.2);
	geneManager->setCrossoverRate(0.05);
	
	//mainGameLoop();
	testOne();

	return(0);
}

void mainGameLoop()
{
	while(1)
	{
		for (int i = 0; i < geneManager->getPopulationSize(); i++)
		{
			currentTank.setGenome(geneManager->getGenome(i));
			currentTank.loadGenome();
			processAmount = 50 + (geneManager->getGenome(i)[10]*1000);
			fitnessTest();
			geneManager->setFitness(i, currentTank.m_tankTwo->explosiveFitness);
		}

		std::cout << geneManager->getFitness(14) << std::endl;
		if (stop)
		{
			outputToFileGene(14);
		}

		geneManager->newGeneration();
		
		


		generation++;

	}
}



void testOne()
{
	testOneBool = true;
	for (int i = 0;i < 1; i++)
	{
		currentTank.fileLoadGenome(inputGene);
		processAmount = currentTank.m_processAmount;
		//std::cout << currentTank.m_tankOne->m_gasMix->getPressure() << std::endl;
		//std::cout << currentTank.m_tankTwo->m_gasMix->getPressure() << std::endl;
		fitnessTest();
		std::cout << currentTank.m_tankTwo->explosiveFitness << std::endl;
	}
	int test;
		std::cin >> test;
}



void outputToFileGene(int index)
{
	outputGene << "Genome: ";
	for (int i = 0; i < geneManager->getGenomeLength(); i++)
	{
		outputGene << geneManager->getGenome(index)[i];

		if (i != geneManager->getGenomeLength()-1)
		{
			outputGene << " ";
		}
	}
	outputGene << std::endl;
}


void fitnessTest()
{
	for (int k = 0; k < processAmount; k++)
	{
		currentTank.m_tankOne->process();
		currentTank.m_tankTwo->process();
		if (currentTank.m_tankOne->isDeleted || currentTank.m_tankTwo->isDeleted) 
		{
			break;
		}

	}

	if (currentTank.m_tankOne->isDeleted || currentTank.m_tankTwo->isDeleted) 
	{
		currentTank.m_tankTwo->explosiveFitness = 0;
		if (testOneBool)
		{
			std::cout << "Tank Ruptured/Fragmented before merging!" << std::endl;
		}
	}

	else
	{
		currentTank.mergeGases();

		for (int k = 0; k < 10; k++)
		{
			if (currentTank.m_tankOne->isDeleted != true && currentTank.m_tankTwo->isDeleted != true)
			{
				currentTank.m_tankOne->process();
				currentTank.m_tankTwo->process();
			}
			else
			break;
		}
	}
}
			
				
			

