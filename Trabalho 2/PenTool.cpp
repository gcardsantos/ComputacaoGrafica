/*
    -Construtor para o objeto e a classe filha

    -Função virtual para desenhar a forma do objeto (a caixa envolvente está no objeto)

    -Desenho da curva

    -Colisao com pontos

    -Movimentação dos pontos de controle

    -Salvar pontos no arquivo
*/

#include "PenTool.h"
#include "glCanvas2d.h"
#include <math.h>

#define RAIO 4

PenTool::PenTool(Canvas2D* canvas, vector<Ponto*> p, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4) : Objeto (canvas, p1, p2, p3, p4, 3)
{
    for(int i = 0; i < p.size(); i++)
        this->p.push_back(p[i]);
}


void PenTool::forma(){
	if (selected) {
		canvas->color(0, 0, 1);
		for (int i = 0; i < p.size(); i++) {
			if(p[i]->selected)
				canvas->color(1, 0, 0);

			canvas->circleFill(p[i]->x, p[i]->y, RAIO, 20);
			canvas->color(0, 0, 1);
		}
	}
	canvas->color(0, 0, 0);

	for (float t = 0; t <= 1; t += 0.001) {
		double p1 = (pow(1 - t, 3) * p[0]->x) + (3 * t*pow(1 - t, 2) * p[1]->x) + (3 * pow(t, 2)* (1 - t) * p[2]->x) + (pow(t, 3) * p[3]->x);
		double p2 = (pow(1 - t, 3) * p[0]->y) + (3 * t*pow(1 - t, 2) * p[1]->y) + (3 * pow(t, 2)* (1 - t) * p[2]->y) + (pow(t, 3) * p[3]->y);
		canvas->point(p1, p2);
	}
    /*
    //  equação geral do bezier
    for (float t = 0; t <= 1; t += 0.001) {
        for (int k = 1; k < p.size(); ++k){
            for (int i = 0; i < p.size() - k; ++i) {
                px = (1 - t) * p[i]->x + t * p[i + 1]->x;
                py = (1 - t) * p[i]->y + t * p[i + 1]->y;
            }
        }
        canvas->point(px, py);
    }

    // b -spline
    for(int n=0;n<p.size();n++){
        for(double i=0;i<1;i+=0.001){
            px = ((pow(i,3)/6)*p[n]->x) + (((-3*pow(i,3)+3*pow(i,2)+3*i+1)/6)*p[n+1]->x) + (((3*pow(i,3)-6*pow(i,2)+4)/6)*p[n+2]->x) + ((pow(1-i,3)/6)*p[n+3]->x);
            py = ((pow(i,3)/6)*p[n]->y) + (((-3*pow(i,3)+3*pow(i,2)+3*i+1)/6)*p[n+1]->y) + (((3*pow(i,3)-6*pow(i,2)+4)/6)*p[n+2]->y) + ((pow(1-i,3)/6)*p[n+3]->y);
            canvas->point(px, py);
        }
    }*/
}

void PenTool::setSelectedPontos(bool v) {
	for (unsigned int i = 0; i < p.size(); i++) {
		p[i]->selected = v;
	}
}

void PenTool::escala(vector<Ponto *> p, double num) {
	Objeto::escala(pontos, num);
	Objeto::escala(this->p, num);
	AtualizaPontos(this->p);
}

bool PenTool::ColisaoPonto(int x, int y) {
	for (unsigned int i = 0; i < p.size(); i++) {
		if ((x <= p[i]->x + RAIO && x >= p[i]->x - RAIO) && (y <= p[i]->y + RAIO && y >= p[i]->y - RAIO)) {
			p[i]->selected = !p[i]->selected;
			return true;
		}
	}
	return false;
}

void PenTool::movimenta(int x, int y) {
	for (unsigned int i = 0; i < p.size(); i++) {
		if (p[i]->selected) {
			p[i]->x = x;
			p[i]->y = y;
			AtualizaPontos(p);
			return;
		}	
	}

	int xm = abs((pontos[0]->x + pontos[2]->x) / 2);
	int ym = abs((pontos[0]->y + pontos[2]->y) / 2);

	Translada(pontos, xm * -1, ym * -1);
	Translada(pontos, x, y);

	Translada(p, xm * -1, ym * -1);
	Translada(p, x, y);
}

void PenTool::salvar(FILE * f)
{
	fwrite((const void*)&ordem, sizeof(int), 1, f);
	for (unsigned int j = 0; j < p.size(); j++) {

		fwrite((const void*)&p[j]->x, sizeof(double), 1, f);
		fwrite((const void*)&p[j]->y, sizeof(double), 1, f);
	}
}
