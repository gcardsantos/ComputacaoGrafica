#ifndef BOLA_H
#define BOLA_H

#include <Control.h>

class Bola : public Control{
    private:
        int raio;
        double red, green, blue;
    public:
        Bola(int x, int y, int r, double verm, double verde, double azul, signed short v, bool vis);
        void render();
        bool colisao(int l, int c);
        virtual ~Bola();
};

#endif // BOLA_H
