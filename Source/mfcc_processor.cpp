#include "mfcc_processor.h"

#include "device.h"
#include "sr_engine.h"

#include "util.h"

#include <fftw3\fftw3.h>

mfcc_processor::mfcc_processor()
	: m_fft_bins(new double[NUM_OF_FILTERBANKS + 2]), m_calculated(false)
{}

mfcc_processor::~mfcc_processor()
{
	if (m_fft_bins)
		delete m_fft_bins;
}

std::vector<double> mfcc_processor::calculate_cepstrals(double* power_spectrum)
{
	//CALCULATE LOG FILTER BANKS
	if (!m_calculated)
		calculate_fft_bins();
	double* dct_input = new double[NUM_OF_FILTERBANKS];
	for (size_t m = 1; m <= NUM_OF_FILTERBANKS; m++)
	{
		double first_half = 0.0;
		for (size_t k = m_fft_bins[m - 1]; k <= m_fft_bins[m]; k++)
			first_half += (k - m_fft_bins[m - 1]) / (m_fft_bins[m] - m_fft_bins[m - 1])*power_spectrum[k];
		
		double second_half = 0.0;
		for (size_t k = m_fft_bins[m] + 1; k <= m_fft_bins[m + 1]; k++)
			second_half += (m_fft_bins[m + 1] - k) / (m_fft_bins[m + 1] - m_fft_bins[m])*power_spectrum[k];
		dct_input[m - 1] = log(first_half + second_half);
	}

	//APPLY DCT ON FILTER BANKS
	//POSSIBLE OPTIMIZATION HERE BY USING FFTW_MEASURE INSTEAD OF FFTW_ESTIMATE
	double* filter_banks = new double[NUM_OF_FILTERBANKS];
	fftw_plan dct_plan = fftw_plan_r2r_1d(NUM_OF_FILTERBANKS, dct_input, filter_banks, FFTW_REDFT00, FFTW_ESTIMATE);
	fftw_execute(dct_plan);
	fftw_destroy_plan(dct_plan);
	delete[] dct_input;

	//DO CEPSTRAL MEAN NORMALIZATION
	std::vector<double> cepstrals(NUM_OF_CEPSTRALS);
	double mean = 0.0;
	for (size_t i = 0; i < NUM_OF_CEPSTRALS; i++)
		mean += filter_banks[i];
	mean /= NUM_OF_CEPSTRALS;
	for (size_t i = 0; i < NUM_OF_CEPSTRALS; i++)
		cepstrals[i] = filter_banks[i] - mean;
	delete[] filter_banks;

	return cepstrals;
}

void mfcc_processor::calculate_fft_bins()
{
	//CALCULATE FFT BINS (INDICIES) WITH CORRESPONDING FREQUENCY
	m_fft_bins[0] = get_nearest_fft_bin(LOWER_FREQUENCY);
	m_fft_bins[NUM_OF_FILTERBANKS + 1] = get_nearest_fft_bin(UPPER_FREQUENCY);

	double low_freq_mel = to_mel(LOWER_FREQUENCY);

	double linear_step = (to_mel(UPPER_FREQUENCY) - low_freq_mel) / (NUM_OF_FILTERBANKS + 1);
	for (size_t i = 1; i <= NUM_OF_FILTERBANKS; i++)
	{
		double freq_from_mel = from_mel(low_freq_mel + i*linear_step);
		m_fft_bins[i] = get_nearest_fft_bin(freq_from_mel);
	}

	m_calculated = true;
}

unsigned mfcc_processor::get_nearest_fft_bin(double freq_filter)
{
	return floor((sr_engine::FFT_WIDTH + 1)*freq_filter / device::SAMPLE_RATE);
}