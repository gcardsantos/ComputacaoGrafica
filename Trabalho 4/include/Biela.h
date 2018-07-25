#ifndef BIELA_H
#define BIELA_H

#include "Cilindro.h"
#include "Vetor.h"
#include <vector>

using namespace std;

class Biela
{
    public:
        bool visible;
        double tam_biela;
        double ang_rotacao;
        double vel_rotacao;
        double vira_raio;
        double distanciaY;
        double distanciaZ;
        Vetor* pos_encaixeV;
        Vetor* pos_encaixeP;
        Cilindro* biela;
        Cilindro* biela_pistao;
        Cilindro* biela_vira;

        Biela(Vetor* pos);

        double radianosToGraus(double num);
        void render();
        void setAngRotacao();
        void AddBiela();
        virtual ~Biela();
    protected:
    private:
};

#endif // BIELA_H
