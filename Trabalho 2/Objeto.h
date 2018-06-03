#ifndef OBJETO_H
#define OBJETO_H

#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

#include "Ponto.h"
#include "glCanvas2d.h"

using namespace std;


class Objeto
{
    public:
        Canvas2D* canvas;
        vector<Ponto*> pontos;

        int tipo;
        int ordem;
        float r, g, b;
        bool focus, selected;

        Objeto(Canvas2D* canvas, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4, int tipo);

        void render();
        
        Objeto* ColisaoObjeto(int x, int y);
		void rotaciona(bool d);
		void setOrdem(int i);
		void AtualizaPontos(vector<Ponto*> p);
		void Translada(vector<Ponto*> p,int x, int y);
        void floodFill(int x, int y, int corvelha);

		virtual void escala(vector<Ponto*> p, double num);
		virtual void setSelectedPontos(bool v);
		virtual void movimenta(int x, int y);
		virtual void salvar(FILE* f);
        virtual bool ColisaoPonto(int x, int y);
        virtual void forma();
        virtual void setSelected(bool v);
        virtual bool getSelected();
};

#endif // CONTROL_H
