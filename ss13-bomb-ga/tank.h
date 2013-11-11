#ifndef TANK_H
#define TANK_H

#include "gasmix.h"
#include <vector>


class Tank
{
public:
	Tank();

	void process();
	void checkStatus();

	int m_volume;
	GasMix *m_gasMix;

	void calcStartMoles(std::vector<float> tankVals);

	float explosiveFitness;
	bool isDeleted;
	int integrity;
	~Tank();
private:
	
	
};

#endif