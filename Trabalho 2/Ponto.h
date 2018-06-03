#ifndef PONTO_H
#define PONTO_H

#include "glCanvas2d.h"

class Ponto
{
    public:
        double x, y;
        bool selected;
        Ponto(int x1, int y1);
};

#endif // PONTO_H
