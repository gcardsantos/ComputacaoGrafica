#ifndef PENTOOL_H
#define PENTOOL_H

#include "Ponto.h"
#include "Objeto.h"
#include "glCanvas2d.h"

class PenTool : public Objeto
{
	public:
        vector<Ponto*> p;

        PenTool(Canvas2D* canvas, vector<Ponto*> p, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4);
        void forma();
		void salvar(FILE * f);
		void setSelectedPontos(bool v);
		void movimenta(int x, int y);
		void escala(vector<Ponto *> p, double num);
		bool ColisaoPonto(int x, int y);
		
};

#endif // PENTOOL_H
