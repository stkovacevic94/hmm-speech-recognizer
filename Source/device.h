#ifndef DEVICE
#define DEVICE

#include <QObject>
#include <QAudioInput>

class sr_engine;

class device : public QObject
{
	Q_OBJECT
public:
	static const unsigned short INPUT_BUFFER_SIZE	= 400*5; //FRAME_WIDTH*5
	static const unsigned short SAMPLE_RATE			= 16000;

	device();
	~device();

	void start();
	void stop();
private slots:
	void read_frame();
private:
	QAudioFormat		m_format;
	QIODevice*			m_input_dev;
	QAudioDeviceInfo	m_input_info;
	QAudioInput*		m_input;
	QByteArray			m_buffer;
};

#endif