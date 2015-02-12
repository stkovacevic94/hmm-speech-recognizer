#ifndef ENDPOINT_DETECTOR
#define ENDPOINT_DETECTOR

#include <list>

class endpoint_detector
{
public:
	static const unsigned short ENERGY_DEPTH = 12;

	endpoint_detector(double treshold);
	
	bool is_speech_frame(double frame[], size_t length);
	void reset();
private:
	std::list<double>	m_past_energies;

	double m_treshold;
};

#endif
