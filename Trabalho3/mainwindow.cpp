#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glCanvas2d.h"

#include <qgridlayout.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	Canvas2D *canvas = new Canvas2D(this);
	QGridLayout* gridCanvas = new QGridLayout;
	gridCanvas->addWidget(canvas, 0, 0, 100, 4);
    ui->gbCanvas->setLayout(gridCanvas);
    ui->gbCanvas->setFixedHeight(canvas->height());
	m_timer = new QTimer(this);
	m_timer->setInterval(10);
	m_timer->start();
	
    connect(m_timer,            SIGNAL(timeout()),            canvas, SLOT(update()));
    connect(ui->btnStart,       SIGNAL(released()),           canvas, SLOT(btnStart()));
    connect(ui->chkBiela,       SIGNAL(clicked(bool)),        canvas, SLOT(chkBiela()));
    connect(ui->chkCamisa,      SIGNAL(clicked(bool)),        canvas, SLOT(chkCamisa()));
    connect(ui->chkPistao,      SIGNAL(clicked(bool)),        canvas, SLOT(chkPistao()));
    connect(ui->chkVira,        SIGNAL(clicked(bool)),        canvas, SLOT(chkVira()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMsg()
{

}

void MainWindow::updateIntervalChanged(int value) {
	m_timer->setInterval(value);
	if (m_timer->isActive())
		m_timer->start();
}

void MainWindow::sliderChanged(int i)
{
}

void MainWindow::checkBoxChanged(bool b)
{
}
