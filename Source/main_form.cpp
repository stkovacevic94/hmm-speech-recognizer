#include "main_form.h"
#include "sr_engine.h"
#include <QTimer>

main_form::main_form(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	g_engine = sr_engine::instance();

	m_sample_view = new QCustomPlot;
	m_sample_view->addGraph();
	ui.sampleGLayout->addWidget(m_sample_view);

	m_debug_view = new QCustomPlot;
	m_debug_view->addGraph();
	ui.debugGLayout->addWidget(m_debug_view);

	m_sample_view->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	m_sample_view->xAxis->setDateTimeFormat("ss");
	m_sample_view->xAxis->setAutoTickStep(false);
	m_sample_view->xAxis->setTickStep(2);
	m_sample_view->axisRect()->setupFullAxesBox();

	m_debug_view->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	m_debug_view->xAxis->setDateTimeFormat("ss");
	m_debug_view->xAxis->setAutoTickStep(false);
	m_debug_view->xAxis->setTickStep(2);
	m_debug_view->axisRect()->setupFullAxesBox();

	m_timer = new QTimer;

	connect(m_sample_view->xAxis, SIGNAL(rangeChanged(QCPRange)), m_sample_view->xAxis2, SLOT(setRange(QCPRange)));
	connect(m_sample_view->yAxis, SIGNAL(rangeChanged(QCPRange)), m_sample_view->yAxis2, SLOT(setRange(QCPRange)));
	connect(m_debug_view->xAxis, SIGNAL(rangeChanged(QCPRange)), m_debug_view->xAxis2, SLOT(setRange(QCPRange)));
	connect(m_debug_view->yAxis, SIGNAL(rangeChanged(QCPRange)), m_debug_view->yAxis2, SLOT(setRange(QCPRange)));

	connect(m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
	connect(ui.toogleSRBtn, SIGNAL(clicked()), this, SLOT(toogle_engine()));
}

main_form::~main_form()
{
	if (m_sample_view)
		delete m_sample_view;
	if (m_timer)
	{
		m_timer->stop();
		delete m_timer;
	}
	if (g_engine)
		delete g_engine;
}

void main_form::toogle_engine()
{
	if (g_engine->is_running())
	{
		m_timer->stop();
		disconnect(g_engine, 0, this, 0);
		g_engine->stop();
		m_sample_view->graph(0)->clearData();
	}
	else
	{
		m_timer->start(0);
		connect(g_engine, SIGNAL(sample_read(short)), this, SLOT(update_data(short)));
		connect(g_engine, SIGNAL(debug_signal(double)), this, SLOT(debug_slot(double)));
		g_engine->start();
	}
}

void main_form::repaint()
{
	double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
	static double lastPointKey = 0;
	if (key - lastPointKey > 0.025) 
	{
		m_sample_view->graph(0)->rescaleValueAxis();
		m_debug_view->graph(0)->rescaleValueAxis();
		lastPointKey = key;
	}
	m_sample_view->xAxis->setRange(key + 0.25, 5, Qt::AlignRight);
	m_sample_view->replot();

	m_debug_view->xAxis->setRange(key + 0.25, 5, Qt::AlignRight);
	m_debug_view->replot();

	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key - lastFpsKey > 2) 
	{
		ui.statusbar->showMessage(
			QString("%1 FPS, Total Data points: %2")
			.arg(frameCount / (key - lastFpsKey), 0, 'f', 0)
			.arg(m_sample_view->graph(0)->data()->count())
			, 0);
		lastFpsKey = key;
		frameCount = 0;
	}
}

void main_form::update_data(short sample)
{
	double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
	static double lastPointKey = 0;

	m_sample_view->graph(0)->addData(key, sample);
	m_sample_view->graph(0)->removeDataBefore(key - 5);
	lastPointKey = key;
}

void main_form::debug_slot(double sample)
{
	double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
	static double lastPointKey = 0;

	m_debug_view->graph(0)->addData(key, sample);
	m_debug_view->graph(0)->removeDataBefore(key - 5);
	lastPointKey = key;
}