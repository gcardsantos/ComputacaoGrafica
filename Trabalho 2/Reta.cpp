/*
    - Construtor da reta e do objeto (caixa envolvente)

    - Desenha a forma do objeto

    - Troca a espessura da linha (reta)

    - Salva a reta

*/

#include "Reta.h"
#include "Ponto.h"



#define TAM_RETA 5


Reta::Reta(Canvas2D* canvas, Ponto* p1, Ponto* p2):Objeto(canvas, p1, p1, p2, p2, 2){

}

void Reta::forma(){
    canvas->line(pontos[0]->x, pontos[0]->y, pontos[2]->x, pontos[2]->y);
}

void Reta::setEspessura(int x) {
	espessura = x;
}

void Reta::salvar(FILE * f) {
	
	fwrite((const void*)&ordem, sizeof(int), 1, f);
	
	fwrite((const void*)&pontos[0]->x, sizeof(double), 1, f);
	fwrite((const void*)&pontos[0]->y, sizeof(double), 1, f);
	fwrite((const void*)&pontos[2]->x, sizeof(double), 1, f);
	fwrite((const void*)&pontos[2]->y, sizeof(double), 1, f);
}
