#ifndef MAIN_FORM
#define MAIN_FORM

#include <QtWidgets\QMainWindow>
#include <QCustomPlot\qcustomplot.h>

#include "ui_main_form.h"

class sr_engine;

class main_form : public QMainWindow
{
	Q_OBJECT
public:
	main_form(QWidget *parent = nullptr);
	~main_form();

private slots:
	void toogle_engine();
	void repaint();
	void update_data(short);
	void debug_slot(double);
private:
	Ui::MainForm ui;
	QCustomPlot*  m_sample_view;
	QCustomPlot*  m_debug_view;

	sr_engine* g_engine;
	QTimer* m_timer;
};

#endif