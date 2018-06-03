/*
    - Construtor do retangulo e do objeto (caixa envolvente)

    - Desenha a forma do objeto

    - Troca a espessura da linha (reta)

    - Salvar retangulo
*/


#include "Retangulo.h"
#include "Ponto.h"
#include "Objeto.h"
#include "glCanvas2d.h"

Retangulo::Retangulo(Canvas2D* canvas, Ponto* x1, Ponto* x2, Ponto* x3, Ponto* x4) : Objeto(canvas, x1, x2, x3, x4, 1)
{
    this->p.push_back(x1);
    this->p.push_back(x2);
    this->p.push_back(x3);
    this->p.push_back(x4);
}

void Retangulo::forma(){
    canvas->line(this->p[0]->x, this->p[0]->y, this->p[1]->x, this->p[1]->y);
    canvas->line(this->p[1]->x, this->p[1]->y, this->p[2]->x, this->p[2]->y);
    canvas->line(this->p[2]->x, this->p[2]->y, this->p[3]->x, this->p[3]->y);
    canvas->line(this->p[3]->x, this->p[3]->y, this->p[0]->x, this->p[0]->y);
}

void Retangulo::salvar(FILE * f)
{
	fwrite((const void*)&ordem, sizeof(int), 1, f);
    for (unsigned int j = 0; j < p.size(); j++) {

        fwrite((const void*)&p[j]->x, sizeof(double), 1, f);
        fwrite((const void*)&p[j]->y, sizeof(double), 1, f);
	}
}

