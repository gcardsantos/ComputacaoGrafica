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
    connect(ui->rbCaixa,        SIGNAL(released()),           canvas, SLOT(btnRect()));
    connect(ui->rbLinha,        SIGNAL(released()),           canvas, SLOT(btnLine()));
    connect(ui->rbCurva,        SIGNAL(released()),           canvas, SLOT(btnPenTool()));
    connect(ui->rbTriangulo,    SIGNAL(released()),           canvas, SLOT(btnTriangulo()));
    connect(ui->rbSelecao,      SIGNAL(released()),           canvas, SLOT(btnSelecao()));
    connect(ui->actionLimpar,   SIGNAL(triggered(bool)),      canvas, SLOT(btnExcluir()));
    connect(ui->actionSalvar,   SIGNAL(triggered(bool)),      canvas, SLOT(btnSalvar()));
    connect(ui->actionAbrir,    SIGNAL(triggered(bool)),      canvas, SLOT(btnAbrir()));
    connect(ui->btnApagar,      SIGNAL(released()),           canvas, SLOT(btnApagar()));
    connect(ui->dsbEscalar,     SIGNAL(valueChanged(double)), canvas, SLOT(btnEscala(double)));
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
