#ifndef CILINDRO_H
#define CILINDRO_H

#include "Ponto.h"
#include "Objeto.h"
#include "glCanvas2d.h"

#include <vector>

using namespace std;


class Cilindro
{
    public:
        bool visible;
        float r;
        float h;
        Ponto* centro;
        Canvas2D* canvas;

        vector<Ponto*> pUp;
        vector<Ponto*> pDown;

        Cilindro(Canvas2D* canvas, float r, float h, Ponto* centro, int n);
        void exibir();
};

#endif // CILINDRO_H
