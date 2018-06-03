#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Objeto.h"
#include "glCanvas2d.h"

class Triangulo : public Objeto
{
    public:
        Triangulo(Canvas2D* canvas, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4);
        void forma();
        void salvar(FILE * f);
};

#endif // TRIANGULO_H
