#include "Bola.h"
#include "gl_canvas2d.h"

Bola::Bola(int x, int y, int r, double verm, double verde, double azul, signed short v, bool vis):Control(x, y, v, vis){
    raio = r;
    red = verm;
    green = verde;
    blue = azul;
}

void Bola::render(){
    color(red, green, blue);
    if(visible){
        circleFill(x, y, raio, 20);
        if(focus){
            color(0, 0, 0);
            text(x-5, y+10, label.c_str());
        }
    }
}

bool Bola::colisao(int l, int c){
    if((l > x-raio && l < x+raio) && (c > y-raio && c < y+raio)){
        return true;
    }else{
        return false;
    }
}

Bola::~Bola()
{
    //dtor
}
