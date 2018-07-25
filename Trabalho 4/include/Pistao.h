#ifndef PISTAO_H
#define PISTAO_H

#include "Vetor.h"
#include "Cilindro.h"
#include <vector>

using namespace std;
class Pistao
{
    public:
        bool p_visible;
        bool c_visible;
        double tam_biela;
        double ang_rotacao;
        Vetor* posicao_encaixeB;
        Cilindro* pistao;
        Cilindro* camisa;
        Cilindro* pistao_biela;
        Cilindro* ligamento;
        Pistao(Vetor* v);


        void AddMove(Vetor* v, double tam);
        void render();
        void AddPistao();
        void setAngRotacao(double tam);
        virtual ~Pistao();
    protected:
    private:
};

#endif // PISTAO_H
