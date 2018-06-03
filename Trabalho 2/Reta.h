#ifndef RETA_H
#define RETA_H

#include "Ponto.h"
#include "Objeto.h"

class Reta : public Objeto
{
public:
	vector<Ponto*> p;
	int espessura;

    Reta(Canvas2D* canvas, Ponto* p1, Ponto* p2);
    void forma();
	void setEspessura(int espessura);
	void salvar(FILE * f);
};

#endif // RETA_H
