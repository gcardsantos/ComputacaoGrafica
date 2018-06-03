
// *********************************************************************
// Canvas para desenho - Versao C.
//  Autor: Cesar Tadeu Pozzer
//         07/2016
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
// *
// *   pozzer@inf.ufsm.br
// *   pozzer3@gmail.com
// *
//

#include "glCanvas2d.h"
#include "mainwindow.h"
#include "Cilindro.h"
#include "Ponto.h"


#include <math.h>
#include <QWidget>
#include <QMessageBox>
#include <QWheelEvent>
#include <stdio.h>
#include <queue>



using namespace std;

// *******************************************************************************
//Coloque seu codigo aqui, usando as funcoes da Canvas2D defindas na classe Canvas2D (arquivo glCanvas2d.h).
// *******************************************************************************

Cilindro* pistao;

void Canvas2D::paintGL() //callback de desenho na canvas. Chamado pelo Timer definido em mainWindow.cpp
{
	clear(0.8, 0.8, 0.8);
	color(1, 0, 0);

    if(pistao != NULL)
        pistao->exibir();
}


void Canvas2D::wheelEvent(QWheelEvent *event) //callback de mouse
{
	qDebug("Mouse Wheel event %d", event->delta());
}


void Canvas2D::mousePressEvent(QMouseEvent *event) //callback de mouse
{
    setFocus();
}

void Canvas2D::mouseReleaseEvent(QMouseEvent *event) //callback de mouse
{
    qDebug("\nMouse Release: %d %d", event->x(), event->y());		
}

void Canvas2D::mouseMoveEvent(QMouseEvent * event) //callback de mouse
{
    qDebug("\nMouse Move: %d %d", event->x(), event->y());

    if(event->buttons() == Qt::LeftButton){

    }
}

void Canvas2D::keyPressEvent(QKeyEvent* event)
{
    qDebug("\nTecla pessionada  %d", event->key() );
}

//callback para botao definido na mainWindow.
void Canvas2D::showMsg()
{
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("Msg GlWidget");
    msg->show();
}

void Canvas2D::btnStart(){
    pistao = new Cilindro(this, 40, 100, new Ponto(200, 300, 200), 30);
}

void Canvas2D::chkBiela()
{

}

void Canvas2D::chkCamisa()
{

}
void Canvas2D::chkPistao()
{

}
void Canvas2D::chkVira()
{
    pistao->visible = !pistao->visible;
}
