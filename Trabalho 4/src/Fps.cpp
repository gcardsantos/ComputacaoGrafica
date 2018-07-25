#include "Fps.h"
#include <stdio.h>
#include <time.h>

#define UPDATE_RATE 300   //milisegundos

Fps::Fps() {
    t1 = clock();
    cont_frames = 0;
    fps_old = 0; //valor inicial
}

float Fps::getFrames(){
    double tempo;

    t2 = clock();
    tempo  = (double)(t2 - t1);  //milisegundos
    cont_frames++;
    //apos UPDATE_RATE milisegundos, atualiza o framerate
    if(tempo > UPDATE_RATE){
        t1 = t2;
        fps = cont_frames / (tempo/CLOCKS_PER_SEC);
        cont_frames = 0;
        fps_old = fps;

        return fps;
    }
    //se nao foi decorrido UPDATE_RATE milisegundos, retorna a taxa antiga
    return fps_old;
}

Fps::~Fps()
{
    //dtor
}
