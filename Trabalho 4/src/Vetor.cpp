#include "Vetor.h"

Vetor::Vetor()
{
    x = 0;
    y = 0;
    z = 0;
}

Vetor::Vetor(const float tx, const float ty, const float tz)
{
    x = tx;
    y = ty;
    z = tz;
};

//	construtor de copia
Vetor::Vetor( const Vetor* v )
{
    this->x = v->x;
    this->y = v->y;
    this->z = v->z;
};

void Vetor::setValor( const float tx, const float ty, const float tz )
{
    x = tx;
    y = ty;
    z = tz;
};
    //inicializacao de vetor
void Vetor::setValor(const Vetor v)
{
    x = v.x;
    y = v.y;
    z = v.z;
};

void Vetor::Add(const Vetor v){
    x += v.x;
    y += v.y;
    z += v.z;
}

Vetor::~Vetor()
{
    //dtor
}
