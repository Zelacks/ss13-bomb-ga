#include "tank.h"
#define R_IDEAL_GAS_EQUATION	8.31



#define ONE_ATMOSPHERE			101.325	
#define TANK_RUPTURE_PRESSURE	(40.*ONE_ATMOSPHERE)
#define TANK_FRAGMENT_PRESSURE	(50.*ONE_ATMOSPHERE)
#define TANK_LEAK_PRESSURE		(30.*ONE_ATMOSPHERE)

Tank::Tank()
{
	m_gasMix = new GasMix();
	m_volume = 70;
}

Tank::~Tank()
{
	if (m_gasMix)
	{
		delete [] m_gasMix;
		m_gasMix = 0;
	}
}

void Tank::process()
{
	m_gasMix->react();
	checkStatus();
}

void Tank::checkStatus()
{
	float thePressure = m_gasMix->getPressure();

	if (thePressure >  TANK_FRAGMENT_PRESSURE)
	{
		m_gasMix->react();
		m_gasMix->react();
		m_gasMix->react();
		explosiveFitness = m_gasMix->getPressure();
		isDeleted = true;
	}
	else if (thePressure > TANK_RUPTURE_PRESSURE)
	{
		if (integrity <= 0)
		{
			isDeleted = true;
		}
		else
		{
			integrity--;
		}
	}
	else if (thePressure > TANK_LEAK_PRESSURE)
	{
		if(integrity <= 0)
		{
			m_gasMix->remove_ratio(0.25);
		}
		else
		{
			integrity--;
		}
	}

	else if (integrity < 3)
	{
		integrity++;
	}

}

void Tank::calcStartMoles(std::vector<float> tankVals)
{
	m_gasMix->m_temperature = 20+tankVals[4]*90000;

	float molesNeeded = (1013.25 * m_gasMix->m_volume) / (m_gasMix->m_temperature * R_IDEAL_GAS_EQUATION);

	float oxygenRatio = tankVals[0];
	float carbonDioxideRatio = tankVals[1];
	float nitrogenRatio = tankVals[2];
	float toxinsRatio = tankVals[3];
	float totalRatio = oxygenRatio + carbonDioxideRatio + nitrogenRatio + toxinsRatio;

	m_gasMix->m_oxygen = molesNeeded * (oxygenRatio / totalRatio);
	m_gasMix->m_carbonDioxide = molesNeeded * (carbonDioxideRatio / totalRatio);
	m_gasMix->m_nitrogen = molesNeeded * (nitrogenRatio / totalRatio);
	m_gasMix->m_toxins = molesNeeded * (toxinsRatio  /totalRatio);
}