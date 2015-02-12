#ifndef SR_ENGINE
#define SR_ENGINE

#include <list>
#include <algorithm>

#include <QObject>

class device;
class iobserver;
class endpoint_detector;
class mfcc_processor;
class database;

typedef std::vector<std::vector<double>> double_vector;

class sr_engine : public QObject
{
	Q_OBJECT
public:
	static const unsigned short FFT_WIDTH				= 512;
	static const unsigned short FRAME_WIDTH				= 400;
	
	friend device;

	static sr_engine*	instance();
	~sr_engine();

	void start();
	void stop();

	bool is_running() { return m_running; }

	device* get_device() { return m_device; } //Used mainly for debugging

	//Observer pattern
	void attach(iobserver *observer){ m_observers.push_back(observer); }
	void deatach(iobserver *observer){ m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end()); }
	void notify(const std::string& word);
signals:
	void sample_read(short sample);
	void debug_signal(double sample);
private:
	//Singleton
	sr_engine();
	sr_engine(const sr_engine&);
	sr_engine& operator=(const sr_engine&){};

	void				process_frame(short frame[], size_t length);
	double*				get_power_spectrum(double frame[]);
	std::string			recognize_word();
	double_vector		calculate_delta(double_vector data, size_t regression_window);

	//Engine's subsystems
	device*				m_device;
	endpoint_detector*	m_endpoint_detector;
	mfcc_processor*		m_mfcc_processor;
	database*			m_database;
	//CLASSIFIER

	//State variables
	bool m_running;
	bool m_speech_state;
	std::vector<std::vector<double>> m_current_cepstral_set;

	//Misc
	std::list<iobserver*> m_observers;

	static sr_engine*	m_instance;
};

#endif
