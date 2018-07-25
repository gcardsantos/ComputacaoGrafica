#include "Biela.h"
#include "Vetor.h"
#include "GL/glut.h"
#include "Vetor.h"
#include "Cilindro.h"

#include <math.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846

Biela::Biela(Vetor* pos)
{
    tam_biela    = 7;
    visible      = true;
    vel_rotacao  = 0;
    ang_rotacao  = 0;
    vira_raio    = 2.5;
    pos_encaixeV = new Vetor(0, pos->y + 4, 0);
    pos_encaixeP = new Vetor(0, pos->y + 4, 0);
    biela_pistao = new Cilindro(new Vetor(-1,   0, 0), new Vetor(0, 1, 0), 30, 0.6, 2, 90, 0, 1, 0, true);
    biela_vira   = new Cilindro(new Vetor(-1,  -6.5, 0), new Vetor(0, 1, 0), 30, 0.6, 2, 90, 0, 1, 0, true);
    biela        = new Cilindro(new Vetor( 0,   -0.5, 0), new Vetor(1, 0, 0),  5, 0.5, 5.8, 90, 0, 0, 1, true);
}

void Biela::setAngRotacao()
{
    distanciaZ = pos_encaixeV->z - pos_encaixeP->z;
    distanciaY = pos_encaixeV->y - pos_encaixeP->y;
    ang_rotacao = -radianosToGraus(atan(distanciaZ/distanciaY));
}

void Biela::render()
{
    if(visible){
        glPushMatrix();
            glTranslated(0,(pos_encaixeV->y - tam_biela + 0.5)*-1, 0);
            glRotated(ang_rotacao, 1, 0, 0);
            biela->render();
            //biela_pistao->render();
            //biela_vira->render();
        glPopMatrix();
    }

}

double Biela::radianosToGraus(double num)
{
    return (num*(180/M_PI));
}


Biela::~Biela()
{
    //dtor
}
