#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "glCanvas2d.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLWidget)

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	Ui::MainWindow *ui;
	Canvas2D* canvas;
    QTimer   *m_timer;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateIntervalChanged(int value);
    void showMsg();
    void sliderChanged(int i);
    void checkBoxChanged(bool b);
};



#endif // MAINWINDOW_H
