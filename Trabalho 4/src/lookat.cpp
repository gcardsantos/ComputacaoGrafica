/**
*   Programa para ilustrar:
*   - Uso da gluLookAt
*   - Pilha de transformacoes
*   - Projecao pespectiva
*   - Interacao com o mouse/teclado
*   - cullFace, frontFace

*   Autor: Cesar Tadeu Pozzer
*   UFSM - 15/06/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glut.h>
//#include <GL/freeglut_ext.h> //callback da wheel do mouse.
#include "Cilindro.h"
#include "Virabrequim.h"
#include "Biela.h"
#include "Pistao.h"
#include "Fps.h"
#include "Vetor.h"


#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define SCREEN_X 1280
#define SCREEN_Y 720

void display(void);
static void CreateLight(void);
static void CreateMaterial(void);

int   polygonMode = 1;
float rx = 0, rz = 0;

float angulo = 0;
float abertura = 120.0;
float znear  = 1;
float zfar   = 2000;
float aspect = 1.6;

float fps = 0;
float fps_old = 0;
float vel_rotacao = 0;

bool perspective;

Virabrequim* vira;
Biela* biela;
Pistao* pistao;

Virabrequim* vira1;
Biela* biela1;
Pistao* pistao1;

Vetor* pos_camera;
Vetor* pos_visao;
Fps* frames;

void init()
{
    pos_camera = new Vetor(20, 0, 20);
    pos_visao = new Vetor(0, 0, 0);
    perspective = true;
    vira = new Virabrequim(new Vetor(0, 0, 0), 90);
    biela = new Biela(new Vetor(0, 0, 0));
    pistao = new Pistao(new Vetor(0, 0, 0));

    frames = new Fps();
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0, 0, 0, 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    CreateLight();
    CreateMaterial();

    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_SHININESS);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

static void CreateMaterial(void)
{
  	float _mat_amb[4], _mat_dif[4], _mat_esp[4], _mat_shi[1];

    _mat_amb[0] = 0.5f;   _mat_amb[1] = 0.5f;   _mat_amb[2] = 0.5f;   _mat_amb[3] = 0.2f;
    _mat_dif[0] = 0.6f;   _mat_dif[1] = 0.6f;   _mat_dif[2] = 0.1f;   _mat_dif[3] = 0.2f;
    _mat_esp[0] = 0.4f;   _mat_esp[1] = 0.4f;   _mat_esp[2] = 0.4f;   _mat_esp[3] = 0.2f;
    _mat_shi[0] = 25.0f;

    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, _mat_amb);
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, _mat_dif);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, _mat_esp);
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, _mat_shi);
}

static void CreateLight(void)
{
   GLfloat pos[4], amb[4], dif[4], esp[4], shi[1];

   pos[0] = 10.0f;  pos[1] = 5.0f,  pos[2] = 0.0f;   pos[3] = 3.0f;
   amb[0] = 0.2f;   amb[1] = 0.2f,   amb[2] = 0.2f;   amb[3] = 1.0f;
   dif[0] = 0.7f;   dif[1] = 0.7f,   dif[2] = 0.7f;   dif[3] = 1.0f;
   esp[0] = 1.0f;   esp[1] = 1.0f,   esp[2] = 1.0f;   esp[3] = 1.0f;
   shi[0] = 10;

   glLightfv (GL_LIGHT0, GL_POSITION, pos);
	glLightfv (GL_LIGHT0, GL_AMBIENT,  amb);
	glLightfv (GL_LIGHT0, GL_DIFFUSE,  dif);
	glLightfv (GL_LIGHT0, GL_SPECULAR, esp);
	glLightfv (GL_LIGHT0, GL_SHININESS,  shi);
}


////////////////////////////////////////////////////////////////////////////////////////
void display(void)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(perspective)
        gluPerspective(abertura, aspect, znear, zfar);
    else
        glOrtho(-30, 30, -20, 20, znear, zfar);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(pos_camera->x, pos_camera->y, pos_camera->z,  //from. Posicao onde a camera esta posicionada
              pos_visao->x, pos_visao->y, pos_visao->z,  //to. Posicao absoluta onde a camera esta vendo
              0, 1, 0); //up. Vetor Up.

    fps = frames->getFrames();

    glRotatef ((GLfloat) rx, 0.0f, 1.0f, 0.0f);
    glRotatef ((GLfloat) rz, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fps_old = fps;
    vira->angulo = angulo;
    vira->Rotaciona();


    vira->render();

    pistao->setAngRotacao(vira->pos_encaixeB->y + biela->tam_biela - (biela->biela->raio * 2));

    biela->pos_encaixeP = pistao->posicao_encaixeB;
    biela->pos_encaixeV = vira->pos_encaixeB;

    biela->setAngRotacao();
    pistao->render();
    biela->render();

    angulo += vel_rotacao;

    biela->ang_rotacao = angulo;
    glutSwapBuffers();
}


//faz a leitura da entrada do usuario
void keyboard(unsigned char key, int x, int y)
{
    printf("%c", key);
    key = tolower(key);
    switch(key)
    {
        case 27:
            exit(0);
        break;
        case 'a':
            vel_rotacao += 0.08;
        break;
        case 'd':
            vel_rotacao -= 0.08;
        break;
        case 'c':
            pistao->c_visible = !pistao->c_visible;
        break;
        case 'p':
            pistao->p_visible = !pistao->p_visible;
        break;
        case 'v':
            vira->visible = !vira->visible;
        break;
        case 'b':
            biela->visible = !biela->visible;
        break;

        case 't':

        break;
        case 'w': //wireframe
            if(polygonMode==1)
            {
                polygonMode=0;
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            else
            {
                polygonMode=1;
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
        break;
        case 'o':
            perspective = !perspective;
        break;
        case '+':
            abertura+=1;
        break;
        case '-':
            abertura-=1;
        break;
    }
}

void MotionFunc(int x, int y)
{
   float dx, dy;
   //printf("\nX = %d Y = %d", x, y);
   rx = x;
   rz = y;
}

void MouseFunc(int botao, int estado, int x, int y)
{

    //glutPostRedisplay();
   //printf("\n%d %d %d %d", botao, estado, x, y);
}

////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
   int  argc=1;
   char *argv[1] = {"teste"};
   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   glutInitWindowSize (SCREEN_X, SCREEN_Y);
   glutInitWindowPosition (300, 0);
   /* create window */
   glutCreateWindow ("GluLookAt Demo");
   init();
   glutDisplayFunc(display);
   glutMotionFunc(MotionFunc);
   glutMouseFunc(MouseFunc);
   glutIdleFunc(display);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}
