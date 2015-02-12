#include "sr_engine.h"

#include "database.h"
#include "util.h"
#include "device.h"
#include "iobserver.h"
#include "point.h"
#include "mfcc_processor.h"
#include "endpoint_detector.h"

#include <fftw3\fftw3.h>

#include <iostream>
using namespace std;

sr_engine* sr_engine::m_instance = nullptr;

sr_engine* sr_engine::instance()
{
	if (!m_instance)
		m_instance = new sr_engine();
	return m_instance;
}

sr_engine::sr_engine() 
{
	m_device = new device();
	m_running = false;
	m_speech_state = false;
	m_endpoint_detector = new endpoint_detector(7.0e6 / FRAME_WIDTH);
	m_mfcc_processor = new mfcc_processor();
	m_database = new database();
}

sr_engine::~sr_engine()
{
	if (m_device)
		delete m_device;
	if (m_endpoint_detector)
		delete m_endpoint_detector;
	if (m_mfcc_processor)
		delete m_mfcc_processor;
	if (m_database)
		delete m_database;
}

void sr_engine::start()
{
	if (m_running)
		return;
	m_endpoint_detector->reset();
	m_running = true;
	m_device->start();
}

void sr_engine::stop()
{
	if (!m_running)
		return;
	m_running = false;
	m_device->stop();
}

void sr_engine::notify(const std::string& word)
{
	for (auto it = m_observers.cbegin(); it != m_observers.cend(); it++)
	{
		if (*it)
			(*it)->update(word);
	}
}

void sr_engine::process_frame(short frame[], size_t length)
{
	if (length > 0)
	{
		double *data = new double[FFT_WIDTH]{};

		//Pre-process frame
		//i.e. apply pre-emphasis filters and windowing function
		for (size_t i = 0; i < length; i++)
		{
			double sample = frame[i];

			//Pre-emphasize sample
			sample = sample - 0.95*(i > 0 ? frame[i - 1] : 0);

			//Apply Hanning window function to the sample
			sample = sample * (0.5 * (1 - cos((i * PI) / (FRAME_WIDTH-1))));

			//Finish
			data[i] = sample;
			emit sample_read(frame[i]);
		}
		
		bool is_speech_frame = m_endpoint_detector->is_speech_frame(data, length);
		if (!m_speech_state && is_speech_frame)
		{
			cout << "Starting speech" << endl;
			m_speech_state = true;
		}
		else if (m_speech_state && !is_speech_frame)
		{
			//PROCESS SPEECH AND FIRE EVENT
			cout << "Processing speech..." << endl;
			stop();
			notify(recognize_word());
			start();
			cout << "Done" << endl;

			m_speech_state = false;
			//CLEAR CURRENT WORD MODEL
			m_current_cepstral_set.clear();
		}

		if (m_speech_state)
		{
			double* power_spectrum = get_power_spectrum(data);
			m_current_cepstral_set.push_back(m_mfcc_processor->calculate_cepstrals(power_spectrum));

			//CLEAN UP
			delete[] power_spectrum;
		}
		delete[] data;
	}
}

std::string sr_engine::recognize_word()
{
	//CALCULATE DELTAS
	double_vector cepstrals_delta = calculate_delta(m_current_cepstral_set, 2);
	double_vector delta_delta = calculate_delta(cepstrals_delta, 1);

	//COMBINE FEATURE VECTOR
	const size_t SET_LENGTH = m_current_cepstral_set.size();
	const size_t NUM_OF_CEPSTRALS = mfcc_processor::NUM_OF_CEPSTRALS;
	
	double_vector feature_set(SET_LENGTH, std::vector<double>(3*NUM_OF_CEPSTRALS));
	//SIMPLY APPENT CEPSTRALS, DELTA, AND DELTA-DELTA INTO 1 VECTOR
	for (size_t i = 0; i < m_current_cepstral_set.size(); i++)
	{
		for (size_t m = 0; m < NUM_OF_CEPSTRALS; m++)
			feature_set[i][m] = m_current_cepstral_set[i][m];
		for (size_t m = NUM_OF_CEPSTRALS; m < 2 * NUM_OF_CEPSTRALS; m++)
			feature_set[i][m] = cepstrals_delta[i][m - NUM_OF_CEPSTRALS];
		for (size_t m = 2 * NUM_OF_CEPSTRALS; m < 3 * NUM_OF_CEPSTRALS; m++)
			feature_set[i][m] = delta_delta[i][m - 2 * NUM_OF_CEPSTRALS];
	}
	
	/*std::vector<point> points;
	for (size_t i = 0; i < feature_set.size(); i++)
		points.push_back(point(feature_set[i]));
	std::vector<int> quantized = m_database->get_codebook()->quantitize(points);*/
	/*
		HMM STUFFS HERE
	*/
	return "I'm deaf at the moment :D";
}

double_vector sr_engine::calculate_delta(double_vector data, size_t regression_window)
{
	const size_t SET_LENGTH = data.size(); 
	const size_t NUM_OF_CEPSTRALS = mfcc_processor::NUM_OF_CEPSTRALS;
	double denominator = 0;
	for (int i = -regression_window; i < regression_window; i++) {
		denominator += pow(i, 2.0);
	}

	double_vector delta(SET_LENGTH, std::vector<double>(NUM_OF_CEPSTRALS));
	for (int i = 0; i < NUM_OF_CEPSTRALS; i++) {
		for (int k = 0; k < regression_window; k++) {
			delta[k][i] = data[k][i];
		}
		for (int k = SET_LENGTH - regression_window; k < regression_window; k++) {
			delta[k][i] = data[k][i];
		}
		for (int j = regression_window; j < SET_LENGTH - regression_window; j++) {
			double numerator = 0;
			for (int m = -regression_window; m <= regression_window; m++) {
				numerator += m * data[m + j][i];
			}
			delta[j][i] = numerator / denominator;
		}
	}
	return delta;
}

double* sr_engine::get_power_spectrum(double frame[])
{
	//GET FFT OF FRAME AND CALCULATE POWER SPECTRUM
	//POSSIBLE OPTIMIZATION HERE BY USING FFTW_MEASURE INSTEAD OF FFTW_ESTIMATE
	fftw_complex *out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex)*FFT_WIDTH));
	fftw_plan fft_plan = fftw_plan_dft_r2c_1d(sr_engine::FFT_WIDTH, frame, out, FFTW_ESTIMATE);

	fftw_execute(fft_plan);

	double *power_spectrum = new double[FFT_WIDTH];
	for (size_t i = 0; i < FFT_WIDTH; i++)
		power_spectrum[i] = pow(out[i][0], 2.0) + pow(out[i][1], 2.0);

	fftw_destroy_plan(fft_plan);
	fftw_free(out);

	return power_spectrum;
}



