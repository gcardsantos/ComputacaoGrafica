#ifndef VIRABREQUIM_H
#define VIRABREQUIM_H

#include "Cilindro.h"
#include "Vetor.h"
#include <vector>

using namespace std;

class Virabrequim
{
    public:
        bool visible;
        float ultimo;
        double angulo;
        Vetor* pos_rot;
        Vetor* pos_encaixeB;
        Cilindro* ligamentos;
        Cilindro* vira_biela;
        vector<Cilindro*> base;
        Virabrequim(Vetor* pos, double ang);

        void Rotaciona();
        void AddVira();
        void render();
        virtual ~Virabrequim();
    protected:
    private:
};

#endif // VIRABREQUIM_H
