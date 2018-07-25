#include "Virabrequim.h"

#include "Cilindro.h"
#include "Vetor.h"
#include <math.h>
#include <vector>
#include <stdio.h>

#define M_PI 3.14159265358979323846

Virabrequim::Virabrequim(Vetor* pos, double ang)
{
    visible = true;
    angulo = 0;
    //cilindros verticais
    base.push_back(new Cilindro(new Vetor(-2.5f, 0.0f, 0.0f), new Vetor(1.0f, 0.0f, 0.0f), 5, 0.5, 1.5, ang, 1.0, 0.0, 0.0, true));
    base.push_back(new Cilindro(new Vetor( 2.5f, 0.0f, 0.0f), new Vetor(1.0f, 0.0f, 0.0f), 5, 0.5, 1.5, ang, 1.0, 0.0, 0.0, true));
    //cilindros horizontais         Vetor de posicao             Vetor de eixo rotacao
    base.push_back(new Cilindro(new Vetor(   -5, 0.0f, 0.0f), new Vetor(0.0f, 1.0f, 0.0f), 40, 0.5, 3, ang, 1.0, 0.0, 0.0, true));
    base.push_back(new Cilindro(new Vetor(    2, 0.0f, 0.0f), new Vetor(0.0f, 1.0f, 0.0f), 40, 0.5, 3, ang, 1.0, 0.0, 0.0, true));
    //base ligamento com o virabrequim
    ligamentos =   new Cilindro(new Vetor(   -3,   -2, 0.0f), new Vetor(0.0f, 1.0f, 0.0f), 30, 0.5, 6, ang, 0.0, 0.0, 1.0, true);
    vira_biela =   new Cilindro(new Vetor(   -1,   -2, 0.0f), new Vetor(0.0f, 1.0f, 0.0f), 30, 0.6, 2, ang, 0.0, 1.0, 0.0, true);
    pos_encaixeB = new Vetor(-3, -2, 0.0);
}

double Radianos(float n){
    return (n*(M_PI/180.0));
}

void Virabrequim::Rotaciona(){
    pos_encaixeB->z = 2 * sin(Radianos(angulo));
    pos_encaixeB->y = 2 * cos(Radianos(angulo));
}

void Virabrequim::render()
{
    if(visible){
        glPushMatrix();
            glRotated(angulo, 1, 0, 0);
            ligamentos->render();
            vira_biela->render();
            for(unsigned int i = 0; i < base.size(); i++)
                base[i]->render();
        glPopMatrix();
    }
}



Virabrequim::~Virabrequim()
{
    //dtor
}
