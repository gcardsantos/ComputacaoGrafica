#ifndef QUADRADOS_H
#define QUADRADOS_H

#include "Objeto.h"
#include "glCanvas2d.h"

class Retangulo : public Objeto
{
    public:
        vector<Ponto*> p;

        Retangulo(Canvas2D* canvas, Ponto* x1, Ponto* x2, Ponto* x3, Ponto* x4);
        void forma();
		void salvar(FILE * f);		
};

#endif // QUADRADOS_H
