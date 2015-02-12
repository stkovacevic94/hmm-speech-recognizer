#ifndef MFCC_PROCESSOR
#define MFCC_PROCESSOR

#include <vector>

class mfcc_processor
{
public:
	static const unsigned short NUM_OF_CEPSTRALS	= 13;
	static const unsigned short NUM_OF_FILTERBANKS	= 26;
	static const unsigned short LOWER_FREQUENCY		= 300;
	static const unsigned short UPPER_FREQUENCY		= 8000;

	mfcc_processor();
	~mfcc_processor();

	std::vector<double> calculate_cepstrals(double* power_spectrum);
private:
	void calculate_fft_bins();
	unsigned get_nearest_fft_bin(double freq_filter);

	double*	m_fft_bins;
	bool	m_calculated;
};

#endif

