#include "Cilindro.h"
#include "glCanvas2d.h"
#include "Ponto.h"
#define PI 3.14159265

#include <iostream>
#include <QMessageBox>

using namespace std;
Cilindro::Cilindro(Canvas2D* canvas, float r, float h, Ponto *centro, int n)
{
    this->canvas = canvas;
    this->centro = centro; //CENTRO DO OBJETO
    visible = true;
    float x = 0, z = 0;
    float yMax = centro->y + h/2; //PEGA A CIRCUNFERENCIA SUPERIOR
    float yMin = centro->y - h/2; //PEGA A CIRCUNFERENCIA INFERIOR
    qDebug("%f - %f\n", yMax, yMin);
    float ang = (PI*2)/ n;

    for(float i = 0; i <= PI * 2; i+= ang){
        x = r * cos(i);
        z = r * sin(i);
        Ponto* p = new Ponto(centro->x + x, yMax, centro->y + z);
        pUp.push_back(p);
        Ponto* p1 = new Ponto(centro->x + x, yMin, centro->z + z);
        pDown.push_back(p1);
    }
}

void Cilindro::exibir(){
    canvas->color(1, 0, 0);
    if(this->visible){
        for(unsigned int i = 0; i < pUp.size() - 1; i++){
            canvas->line(pUp[i]->x, pUp[i]->y, pUp[i+1]->x, pUp[i+1]->y);
            canvas->line(pDown[i]->x, pDown[i]->y, pDown[i+1]->x, pDown[i+1]->y);
        }
        canvas->line(pUp[pUp.size()-1]->x, pUp[pUp.size()-1]->y, pUp[0]->x, pUp[0]->y);
        canvas->line(pDown[pUp.size()-1]->x, pDown[pUp.size()-1]->y, pDown[0]->x, pDown[0]->y);

        for(unsigned int i = 0; i< pDown.size() - 1; i++){
            canvas->line(pUp[i]->x, pUp[i]->y, pDown[i]->x, pDown[i]->y);
        }
        canvas->line(pUp[pUp.size()-1]->x, pUp[pUp.size()-1]->y, pDown[0]->x, pDown[0]->y);


    }
}
