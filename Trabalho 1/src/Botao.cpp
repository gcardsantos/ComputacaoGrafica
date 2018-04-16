#include "Botao.h"
#include "gl_canvas2d.h"

Botao::Botao(int x, int y, string s):Control(x, y, s, true){

}

void Botao::render(){
    color(0.5,0.5,0.5);
    rectFill(x, y, x+100, y+30);
    color(0,0,0);
    text(x+10, y+10, label.c_str());
}

bool Botao::colisao(int l, int c){
    if((l > x && l < x+100) && (c > y && c < y+30)){
        return true;
    }else{
        return false;
    }
}

Botao::~Botao()
{
    //dtor
}
