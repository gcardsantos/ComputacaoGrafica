/*
    - Classe pai de todas, mantem a caixa envolvente
    - Rotaciona os objetos
    - Desenha a caixa envolvente e chama a função que desenha a forma dos filhos
    - Atualiza os pontos de controle dos objetos
    - Movimenta objeto pelo canvas
    - Altera visibilidade do pontos de controle do objeto
*/


#include "glCanvas2d.h"
#include "Ponto.h"
#include "Objeto.h"
#include "math.h"

#define RAIO 5

using namespace std;

Objeto::Objeto(Canvas2D* canvas, Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4, int tipo){
    this->canvas = canvas;
    this->pontos.push_back(p1);
    this->pontos.push_back(p2);
    this->pontos.push_back(p3);
    this->pontos.push_back(p4);
	this->ordem = 0;
    this->tipo = tipo;
    this->selected = false;
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

void Objeto::render(){
    if(this->selected){
        canvas->color(0,0,1);
		if (tipo != 3) {
			for (unsigned int i = 0; i < pontos.size(); i++) {
				if (pontos[i]->selected) {
					canvas->color(1, 0, 0);
				}
				canvas->circleFill(this->pontos[i]->x, this->pontos[i]->y, RAIO, 20);
				canvas->color(0, 0, 1);
			}
		}

        canvas->line(this->pontos[0]->x, this->pontos[0]->y, this->pontos[1]->x, this->pontos[1]->y);
        canvas->line(this->pontos[1]->x, this->pontos[1]->y, this->pontos[2]->x, this->pontos[2]->y);
        canvas->line(this->pontos[2]->x, this->pontos[2]->y, this->pontos[3]->x, this->pontos[3]->y);
        canvas->line(this->pontos[3]->x, this->pontos[3]->y, this->pontos[0]->x, this->pontos[0]->y);
    }
    canvas->color(0,0,0);
    forma();
}

void Objeto::forma(){
    qDebug("Ola");
}

void Objeto::escala(vector<Ponto *> p, double num){
    double x = p[0]->x, y = p[0]->y;

    Translada(p, x * -1, y * -1);
    for(unsigned int i = 0; i < p.size(); i++){
        p[i]->x *= num;
        p[i]->y *= num;
    }
    Translada(p, x, y);
}

Objeto* Objeto::ColisaoObjeto(int x, int y){
    int xmenor = canvas->width(), xmaior = 0, ymenor = canvas->height(), ymaior = 0;

    for(unsigned int i = 0; i < pontos.size(); i++){
        if(pontos[i]->x - RAIO < xmenor)
            xmenor = pontos[i]->x - RAIO;
        if(pontos[i]->x + RAIO > xmaior)
            xmaior = pontos[i]->x + RAIO;
        if(pontos[i]->y - RAIO < ymenor)
            ymenor = pontos[i]->y - RAIO;
        if(pontos[i]->y + RAIO > ymaior)
            ymaior = pontos[i]->y + RAIO;
    }

    if((x > xmenor && x < xmaior)&& (y > ymenor && y < ymaior)){
        this->selected = true;
        return this;
    }
    return NULL;
}

void Objeto::Translada(vector<Ponto*> p, int x, int y){
    for(int i = 0; i < p.size(); i++){
        p[i]->x += x;
        p[i]->y += y;
    }
}

void Objeto::rotaciona(bool d){
	double x, y, xini, yini;
    for(unsigned int i = 0; i < this->pontos.size(); i++)
        if(pontos[i]->selected){
			xini = pontos[i]->x;
			yini = pontos[i]->y;
            Translada(pontos, pontos[i]->x * -1, pontos[i]->y * -1);

            if (d){
                for(unsigned int j = 0; j < pontos.size(); j++){
                    x =  pontos[j]->x * cos(0.08) + pontos[j]->y * sin(0.08);
                    y = -pontos[j]->x * sin(0.08) + pontos[j]->y * cos(0.08);
					pontos[j]->x = x;
					pontos[j]->y = y;
                }
            }else{
                for(unsigned int j = 0; j < pontos.size(); j++){
                    x = pontos[j]->x * cos(0.08) - pontos[j]->y * sin(0.08);
					y = pontos[j]->x * sin(0.08) + pontos[j]->y * cos(0.08);
					pontos[j]->x = x;
					pontos[j]->y = y;
                }
            }
            Translada(pontos, xini, yini);
            return;
        }
}

void Objeto::AtualizaPontos(vector<Ponto*> p) {

	double xmenor = canvas->width(), xmaior = 0, ymenor = canvas->height(), ymaior = 0;

    for (unsigned int i = 0; i< p.size(); i++) {
        if (p[i]->x < xmenor)
            xmenor = p[i]->x;
        if (p[i]->x > xmaior)
            xmaior = p[i]->x;
        if (p[i]->y < ymenor)
            ymenor = p[i]->y;
        if (p[i]->y > ymaior)
            ymaior = p[i]->y;
	}

	pontos[0]->x = xmenor;
	pontos[0]->y = ymenor;
	pontos[1]->x = xmenor;
	pontos[1]->y = ymaior;
	pontos[2]->x = xmaior;
	pontos[2]->y = ymaior;
	pontos[3]->x = xmaior;
	pontos[3]->y = ymenor;
}

void Objeto::movimenta(int x, int y){
	//movimentando
    int xm = abs((pontos[0]->x + pontos[2]->x) / 2);
	int ym = abs((pontos[0]->y + pontos[2]->y) / 2);

    Translada(pontos, xm * -1, ym * -1);
    Translada(pontos, x, y);
}

void Objeto::floodFill(int x, int y, int corvelha){
    canvas->color(r, g, b);
    /*if(getpixel(x, y) == corvelha){

        canvas->point(x,y);
        floodFill(x+1,y,corvelha);
        floodFill(x,y+1,corvelha);
        floodFill(x-1,y,corvelha);
        floodFill(x,y-1,corvelha);
    }*/
}

void Objeto::salvar(FILE * f)
{

}

bool Objeto::ColisaoPonto(int x, int y){
    for(unsigned int i = 0; i < pontos.size(); i++){
        if ((x <= pontos[i]->x+ RAIO && x >= pontos[i]->x - RAIO) && (y <= pontos[i]->y+ RAIO && y >= pontos[i]->y - RAIO)){
            pontos[i]->selected = !pontos[i]->selected;
            return true;
        }
    }
    return false;
}

void Objeto::setOrdem(int i){
    this->ordem = i;
}

void Objeto::setSelectedPontos(bool v) {
	for (unsigned int i = 0; i < pontos.size(); i++) {
		if (pontos[i]->selected) {
			pontos[i]->selected = !pontos[i]->selected;
			return;
		}	
	}
}

void Objeto::setSelected(bool v){
    this->selected = v;
    for(unsigned int i = 0; i < pontos.size(); i++){
        pontos[i]->selected = v;
    }
}

bool Objeto::getSelected(){
    return this->selected;
}
