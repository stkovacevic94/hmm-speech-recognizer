#include "device.h"
#include "sr_engine.h"

device::device()
	:	m_input_info(QAudioDeviceInfo::defaultInputDevice()),
		m_input(0),
		m_input_dev(0),
		m_buffer(INPUT_BUFFER_SIZE, 0)
{
	m_format.setSampleRate(SAMPLE_RATE);
	m_format.setChannelCount(1);
	m_format.setSampleSize(16);
	m_format.setSampleType(QAudioFormat::UnSignedInt);
	m_format.setByteOrder(QAudioFormat::LittleEndian);
	m_format.setCodec("audio/pcm");

	QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
	if (!infoIn.isFormatSupported(m_format))
		m_format = infoIn.nearestFormat(m_format);

	m_input = new QAudioInput(m_input_info, m_format, this);
	m_input->setBufferSize(sr_engine::FRAME_WIDTH * 5);
}

device::~device()
{
	if (m_input)
		delete m_input;
	if (m_input_dev)
		delete m_input_dev;
}

void device::start()
{
	m_input_dev = m_input->start();
	connect(m_input_dev, SIGNAL(readyRead()), this, SLOT(read_frame()));
}

void device::stop()
{
	if (m_input_dev != 0)
	{
		disconnect(m_input_dev, 0, this, 0);
		m_input_dev = 0;
	}
}

void device::read_frame()
{
	if (!m_input)
		return;

	qint64 len = m_input->bytesReady();
	if (len > 400)
		len = 400;
	qint64 l = m_input_dev->read(m_buffer.data(), len);

	sr_engine::instance()->process_frame((short*)m_buffer.data(), l);
}