#include "Cilindro.h"

#include "Vetor.h"
#include <stdio.h>
#include "GL/glut.h"

Cilindro::Cilindro(Vetor* pos, Vetor* pos_ang, GLint nlados, GLdouble raio, GLdouble tam, GLdouble ang_rotacao, GLfloat r, GLfloat g, GLfloat b, bool completa)
{
    this->completa = completa;
    this->pos = new Vetor(pos);
    this->pos_rotacao = new Vetor(pos_ang);
    this->tam = tam;
    this->obj = gluNewQuadric();
    this->nlados = nlados;
    this->raio = raio;
    this->ang_rotacao = ang_rotacao;
    this->ang_translacao = 0;
    this->vel_rotacao = 0;
    this->vel_translacao = 0;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Cilindro::render(){
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslated(pos->x, pos->y, pos->z);
        glRotated(ang_rotacao, pos_rotacao->x, pos_rotacao->y, pos_rotacao->z);
        gluDisk(obj, 0, raio, nlados, 1);
        gluCylinder(obj, raio, raio, tam, nlados, 1);

        if(completa){
            glPushMatrix();
                glTranslated(0, 0, tam);
                gluDisk(obj, 0, raio, nlados, 1);
            glPopMatrix();
        }
    glPopMatrix();
}

void Cilindro::setAngRotacao(GLdouble ang)
{
    this->ang_rotacao = ang;
}

Cilindro::~Cilindro()
{
    //dtor
}
