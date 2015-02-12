#include "endpoint_detector.h"

#include <cmath>
#include "sr_engine.h"

endpoint_detector::endpoint_detector(double treshold)
	: m_treshold(treshold)
{
}

void endpoint_detector::reset()
{
	m_past_energies.clear();
}

bool endpoint_detector::is_speech_frame(double frame[], size_t length)
{
	double energy = 0.0;
	for (size_t i = 0; i < length; i++)
		energy += pow(frame[i], 2.0);


	m_past_energies.push_back(energy/length);
	if (m_past_energies.size() == ENERGY_DEPTH + 1)
		m_past_energies.pop_front();

	double average_energy = 0.0;
	for (auto it = m_past_energies.cbegin(); it != m_past_energies.cend(); it++)
		average_energy += *it;
	average_energy /= ENERGY_DEPTH;

	return average_energy >= m_treshold;
}