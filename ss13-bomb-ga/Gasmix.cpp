#include "gasmix.h"
#include <cmath>



#define T0C										273.15
#define FIRE_MINIMUM_TEMPERATURE_TO_EXIST		100+T0C
#define SPECIFIC_HEAT_CDO						30
#define SPECIFIC_HEAT_TOXIN						200
#define SPECIFIC_HEAT_AIR						20
#define MINIMUM_HEAT_CAPACITY					0.0003
#define PLASMA_UPPER_TEMPERATURE				1370+T0C
#define PLASMA_MINIMUM_BURN_TEMPERATURE			100+T0C
#define PLASMA_OXYGEN_FULLBURN					10
#define FIRE_PLASMA_ENERGY_RELEASED				3000000
#define MINIMUM_TEMPERATURE_DELTA_TO_CONSIDER	0.5
#define R_IDEAL_GAS_EQUATION					8.31

bool GasMix::react()
{
	m_fuelBurnt = 0;
	m_reacting = false;
	if (m_temperature >  FIRE_MINIMUM_TEMPERATURE_TO_EXIST)
	{
		if (fire() > 0)
		{
			m_reacting = true;		
		}
	}
	return(m_reacting);
}

float GasMix::fire()
{
	float energy_released = 0;
	float old_heat_capacity = heat_capacity();

	if (m_toxins > MINIMUM_HEAT_CAPACITY)
	{
		float plasma_burn_rate = 0;
		float oxygen_burn_rate = 0;
		float temperature_scale;

		if (m_temperature > PLASMA_UPPER_TEMPERATURE)
		{
			temperature_scale = 1;
		}
		else
		{
			temperature_scale = (m_temperature - PLASMA_MINIMUM_BURN_TEMPERATURE) / (PLASMA_UPPER_TEMPERATURE - PLASMA_MINIMUM_BURN_TEMPERATURE);
		}

		if (temperature_scale > 0)
		{
			oxygen_burn_rate = 1.4 - temperature_scale;

			if (m_oxygen > m_toxins * PLASMA_OXYGEN_FULLBURN)
			{
				plasma_burn_rate = (m_toxins * temperature_scale)/4;
			}
			else
			{
				plasma_burn_rate = (temperature_scale * (m_oxygen / PLASMA_OXYGEN_FULLBURN)) / 4;
			}

			if (plasma_burn_rate > MINIMUM_HEAT_CAPACITY)
			{
				m_toxins -= plasma_burn_rate;
				m_oxygen -= plasma_burn_rate*oxygen_burn_rate;
				m_carbonDioxide += plasma_burn_rate;
				energy_released += FIRE_PLASMA_ENERGY_RELEASED * (plasma_burn_rate);
				m_fuelBurnt += (plasma_burn_rate) * (1 + oxygen_burn_rate);
			}
		}
	}

	if(energy_released > 0)
	{
		float new_heat_capacity = heat_capacity();
		if (new_heat_capacity > MINIMUM_HEAT_CAPACITY)
		{
			m_temperature = (m_temperature * old_heat_capacity + energy_released) / new_heat_capacity;
		}
	}
	return m_fuelBurnt;
}


float GasMix::heat_capacity()
{
	return(m_carbonDioxide * SPECIFIC_HEAT_CDO + (m_oxygen + m_nitrogen) * SPECIFIC_HEAT_AIR + m_toxins * SPECIFIC_HEAT_TOXIN);
}

GasMix GasMix::remove_ratio(float ratio)
{
	GasMix tempGas;

	tempGas.m_oxygen = m_oxygen*ratio;
	tempGas.m_nitrogen = m_nitrogen*ratio;
	tempGas.m_carbonDioxide = m_carbonDioxide*ratio;
	tempGas.m_toxins = m_toxins*ratio;

	m_oxygen -= m_oxygen*ratio;
	m_nitrogen -= m_nitrogen*ratio;
	m_carbonDioxide -= m_carbonDioxide*ratio;
	m_toxins -= m_toxins*ratio;

	tempGas.m_temperature = m_temperature;
	return(tempGas);
}

void GasMix::merge(GasMix &Giver)
{
	if(abs(m_temperature-Giver.m_temperature) > MINIMUM_TEMPERATURE_DELTA_TO_CONSIDER)
	{
		float combined_heat_capacity = Giver.heat_capacity() + heat_capacity();

		if (combined_heat_capacity != 0)
		{
			m_temperature = (Giver.m_temperature * Giver.heat_capacity() + m_temperature*heat_capacity() ) / combined_heat_capacity;
		}
	}

	m_oxygen += Giver.m_oxygen;
	m_carbonDioxide += Giver.m_carbonDioxide;
	m_nitrogen += Giver.m_nitrogen;
	m_toxins += Giver.m_toxins;
		
}


GasMix GasMix::operator= (GasMix param)
{
	m_oxygen = param.m_oxygen;
	m_carbonDioxide = param.m_carbonDioxide;
	m_nitrogen = param.m_nitrogen;
	m_toxins = param.m_toxins;
	m_fuelBurnt = param.m_fuelBurnt;
	m_volume = param.m_volume;
	m_temperature = param.m_temperature;
	return(param);
}

float GasMix::getPressure()
{
	float moles = m_oxygen + m_carbonDioxide + m_nitrogen + m_toxins;
	return (moles*m_temperature*R_IDEAL_GAS_EQUATION/m_volume);
}
