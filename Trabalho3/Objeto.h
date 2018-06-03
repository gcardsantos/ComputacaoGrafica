#ifndef OBJETO_H
#define OBJETO_H

#include "Ponto.h"
#include <vector>

using namespace std;

class Objeto
{
    public:
        Ponto* centro;
        Objeto(Ponto* c);
        virtual void render();
};

#endif // OBJETO_H
