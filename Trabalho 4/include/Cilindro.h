#ifndef CILINDRO_H
#define CILINDRO_H

#include "Vetor.h"
#include "GL/glut.h"

using namespace std;

class Cilindro
{
    public:
        Cilindro(Vetor* pos, Vetor* pos_ang,GLint nlados, GLdouble raio, GLdouble tam, GLdouble ang_rotacao, GLfloat r, GLfloat g, GLfloat b, bool completa);

        bool completa;
        GLUquadricObj* obj;
        Vetor* pos;
        Vetor* pos_rotacao;

        GLint nlados;
        GLdouble raio, tam;
        GLdouble vel_rotacao, vel_translacao;
        GLdouble ang_rotacao, ang_translacao;
        GLfloat r, g, b;

        void setAngRotacao(GLdouble ang);
        void setVelRotacao(GLdouble vel);
        void render();
        virtual ~Cilindro();
    protected:
    private:
};

#endif // CILINDRO_H
