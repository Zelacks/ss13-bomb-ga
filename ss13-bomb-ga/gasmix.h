#ifndef GASMIX_H
#define GASMIX_H

class GasMix
{
public:

	GasMix operator = (GasMix);
	float getPressure();
	bool react();
	GasMix remove_ratio(float ratio);
	void merge(GasMix &Giver);

	float m_oxygen;
	float m_carbonDioxide;
	float m_nitrogen;
	float m_toxins;
	float m_fuelBurnt;
	bool m_reacting;
	int m_volume;
	float m_temperature;

	float fire();
	float heat_capacity();
private:

};

#endif