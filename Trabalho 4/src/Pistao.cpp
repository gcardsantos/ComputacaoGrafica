#include "Pistao.h"
#include "Cilindro.h"
#include "Vetor.h"
#include <vector>
#include <stdio.h>

Pistao::Pistao(Vetor* v)
{
    p_visible = true;
    c_visible = true;
    posicao_encaixeB = new Vetor(0, 0.6, 0);
    pistao =           new Cilindro(new Vetor(v->x,v->y + 5, 0), new Vetor(1, 0, 0), 30, 2.5, 2.5, 90, 1, 0, 0, false);
    camisa =           new Cilindro(new Vetor(0, v->y + 10.5, 0), new Vetor(1, 0, 0), 30, 2.8, 7  , 90, 1, 1, 0, false);
    pistao_biela =     new Cilindro(new Vetor(v->x -2.4, v->y + 3, 0), new Vetor(0, 1, 0), 30, 0.5, 4.8, 90, 0, 0, 1, true);
    ligamento =        new Cilindro(new Vetor(v->x -1, v->y + 3, 0), new Vetor(0, 1, 0), 30, 0.6, 2  , 90, 0, 1, 0, true);
}

void Pistao::setAngRotacao(double tam){
    posicao_encaixeB->y = tam;
}

void Pistao::render(){
    if(c_visible)
        camisa->render();

    if(p_visible){
        glPushMatrix();
            glTranslated(0, pistao->pos->y + 4 + pistao_biela->raio + posicao_encaixeB->y*-1, 0);
            pistao->render();
            pistao_biela->render();
            ligamento->render();
        glPopMatrix();
    }
}

void Pistao::AddMove(Vetor* v, double tam){
//    pos->y = tam + v->y;
}

void Pistao::AddPistao(){

}

Pistao::~Pistao()
{
    //dtor
}
