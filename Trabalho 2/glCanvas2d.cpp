// *********************************************************************
// Canvas para desenho - Versao C.
//  Autor: Cesar Tadeu Pozzer
//         01/2016
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
// *
// *   pozzer@inf.ufsm.br
// *   pozzer3@gmail.com
// *
//



//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//OBSERVACAO IMPORTANTE
//*************************************************************
// ESTE ARQUIVO NAO PODE SER MODIFICADO PARA OS TRABALHOS DE COMPUTACAO GRAFICA
//*************************************************************

#include <math.h>
#include <QPainter>

//#include <QPaintEngine>
#include <QCoreApplication>

#include "glCanvas2d.h"


#define PI_2 6.28318530717958

Canvas2D::Canvas2D(MainWindow *_mw)
{
    setMinimumSize(300, 250);
    mw = _mw;
}

Canvas2D::~Canvas2D()
{

}

void Canvas2D::point(int x, int y)
{
   glBegin(GL_POINTS);
      glVertex2d(x, y);
   glEnd();
}

void Canvas2D::line( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
   glEnd();
}

void Canvas2D::rect( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_LINE_LOOP);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void Canvas2D::rectFill( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_QUADS);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void Canvas2D::polygon(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_LINE_LOOP);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void Canvas2D::polygonFill(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_POLYGON);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void Canvas2D::text(int x, int y, const char *t)
{
    QPainter painter;
    painter.begin(this);

    painter.setPen(Qt::black );
    painter.drawText(x, y, t);
    //painter.

    painter.end();
}

void Canvas2D::clear(float r, float g, float b)
{
   glClearColor( r, g, b, 1 );
}

void Canvas2D::circle( int x, int y, int raio, int div )
{
   float ang, x1, y1;
   float inc = PI_2/div;
   glBegin(GL_LINE_LOOP);
      for(ang=0; ang<6.27; ang+=inc) //nao vai ateh PI_2 pois o ultimo ponto eh fechado automaticamente com o primeiro, pois tem o tipo LINE_LOOP
      {
         x1 = (cos(ang)*raio);
         y1 = (sin(ang)*raio);
         glVertex2d(x1+x, y1+y);
      }
   glEnd();
}

void Canvas2D::circleFill( int x, int y, int raio, int div )
{
   float ang, x1, y1;
   float inc = PI_2/div;
   glBegin(GL_POLYGON);
      for(ang=0; ang<6.27; ang+=inc)
      {
         x1 = (cos(ang)*raio);
         y1 = (sin(ang)*raio);
         glVertex2d(x1+x, y1+y);
      }
   glEnd();
}

void Canvas2D::color(float r, float g, float b)
{
   glColor3d(r, g, b  );
}


void Canvas2D::resizeGL(int w, int h)
{
    printf("\n Resize w=%d h=%d", w, h);

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //cria uma projecao ortografica com z entre (-1, 1).
    //parametros: left, right, bottom, top, ou seja, (0,0) --> (largura,altura)
    glOrtho (0.0, (GLdouble) w, 0.0, (GLdouble) h, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}


void Canvas2D::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5,0.5,0.5,1.0);

    glPolygonMode(GL_FRONT, GL_FILL);
}
