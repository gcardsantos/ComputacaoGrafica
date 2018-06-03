#include "Ponto.h"
#include <math.h>

Ponto::Ponto(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Ponto::RotacaoX(float ang){
    y = y*cos(ang) - z*sin(ang);
    z = y*sin(ang) + z*cos(ang);
}

void Ponto::RotacaoY(float ang){
    x = x*cos(ang) + z*sin(ang);
    z = -x*sin(ang) + z*cos(ang);
}

void Ponto::RotacaoZ(float ang){
    x = x*cos(ang) - y*sin(ang);
    y = x*sin(ang) + y*cos(ang);
}

void Ponto::Translada(float x, float y, float z){
    this->x += x;
    this->y += y;
    this->z += z;
}
