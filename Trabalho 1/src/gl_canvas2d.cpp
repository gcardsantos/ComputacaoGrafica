/**
*   Programa para ilustrar os elementos mais basicos do OpenGL e Glut.
*   - Apresenta os principais recursos do sistema de Janelas GLUT
*
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
* Referencias GLUT: http://www.opengl.org/documentation/specs/glut/
*                   http://www.opengl.org/documentation/specs/glut/spec3/node1.html
**/


//*****************************************************************************
//modificacoes
//*****************************************************************************
//- passar tamanho da janela
//- retangulo preenchido em qualquer orientacao (polygon)
//-

#include "gl_canvas2d.h"

#include <GL/glut.h>
//#include <GL/freeglut_ext.h> //callback da wheel do mouse.

int largura, altura;

void point(int x, int y)
{
   glBegin(GL_POINTS);
      glVertex2d(x, y);
   glEnd();
}

void line( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
   glEnd();
}

void rect( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_LINE_LOOP);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void rectFill( int x1, int y1, int x2, int y2 )
{
   glBegin(GL_QUADS);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void polygon(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_LINE_LOOP);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void polygonFill(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_POLYGON);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}

void text(int x, int y, const char *t)
{
    int tam = (int)strlen(t);
    int c;

    for(c=0; c<tam; c++)
    {
      glRasterPos2i(x + c*10, y);
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void clear(float r, float g, float b)
{
   glClearColor( r, g, b, 1 );
}

void circle( int x, int y, int raio, int div )
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

void circleFill( int x, int y, int raio, int div )
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

void color(float r, float g, float b)
{
   glColor3d(r, g, b  );
}

void special(int key, int , int )
{
   keyboard(key+100);
}

void specialUp(int key, int , int )
{
   keyboardUp(key+100);
}

void keyb(unsigned char key, int , int )
{
   keyboard(key);
}

void keybUp(unsigned char key, int , int )
{
   keyboardUp(key);
}

void mouseClick(int button, int state, int x, int y)
{
   mouse(button, state, x, y);
   printf("\nmouse click %d %d", button, state);
}

void mouseWheelCB(int wheel, int direction, int x, int y)
{
	printf("\nMouseWheel: %d %d \n", x, y);
}


void motion(int x, int y)
{
   mouse(-1, -1, x, y);
   printf("\nmotion %d %d", x, y);
}

void reshape (int w, int h)
{
   largura = w;
   altura  = h;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   //cria uma projecao ortografica com z entre (-1, 1).
   //parametros: left, right, bottom, top, ou seja, (0,0) --> (largura,altura)
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

void inicializa()
{
   //definicao de valores para limpar buffers
   glClearColor(1,1,1,1);
   glColor3f(1, 0, 0);  // red
   glPolygonMode(GL_FRONT, GL_FILL);
   glClear(GL_COLOR_BUFFER_BIT );
}

void display (void)
{
   glClear(GL_COLOR_BUFFER_BIT );

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   //cria uma projecao ortografica com z entre (-1, 1).
   //parametros: left, right, bottom, top, ou seja, (0,0) --> (largura,altura)
   gluOrtho2D (0.0, largura, 0.0, altura);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   render();

   glFlush();
   glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////////////
//  inicializa o OpenGL
////////////////////////////////////////////////////////////////////////////////////////
void initCanvas(int w, int h)
{
   int argc = 1;
   char arg1[] = "teste";
   char* argv[] = {arg1};

   glutInit(&argc, argv);

   largura = w;
   altura  = h;

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

   glutInitWindowSize (w, h);
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("Canvas 2D");

   inicializa();

   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyb);
   glutKeyboardUpFunc(keybUp);
   glutSpecialUpFunc(specialUp);
   glutSpecialFunc(special);

   glutIdleFunc(display);
   glutMouseFunc(mouseClick);
   glutPassiveMotionFunc(motion);
   glutMotionFunc(motion);
   glutMouseWheelFunc(mouseWheelCB);


    printf("GL Version: %s", glGetString(GL_VERSION));

}

void runCanvas()
{
   glutMainLoop();
}

