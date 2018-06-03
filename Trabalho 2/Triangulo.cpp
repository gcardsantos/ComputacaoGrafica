/*
    - Construtor do triangulo e do objeto (caixa envolvente)

    - Desenha a forma do objeto

    - Salvar retangulo
*/

#include "Triangulo.h"
#include "Ponto.h"
#include "Objeto.h"
#include "glCanvas2d.h"

Triangulo::Triangulo(Canvas2D* canvas, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4) : Objeto(canvas, p1, p2, p3, p4, 4){
	
}

void Triangulo::forma(){
    canvas->color(0, 0, 0);
    canvas->line(this->pontos[0]->x, this->pontos[0]->y, (pontos[1]->x + pontos[2]->x)/2, (pontos[1]->y + pontos[2]->y) / 2);
    canvas->line((pontos[1]->x + pontos[2]->x)/2, (pontos[1]->y + pontos[2]->y)/2, this->pontos[3]->x, this->pontos[3]->y);
    canvas->line(this->pontos[3]->x, this->pontos[3]->y, this->pontos[0]->x, this->pontos[0]->y);
}


void Triangulo::salvar(FILE * f){
   
	fwrite((const void*)&ordem, sizeof(int), 1, f);
	for (unsigned int j = 0; j < pontos.size(); j++) {
		fwrite((const void*)&pontos[j]->x, sizeof(double), 1, f);
		fwrite((const void*)&pontos[j]->y, sizeof(double), 1, f);
	}
}
