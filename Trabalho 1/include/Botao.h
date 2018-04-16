#ifndef BOTAO_H
#define BOTAO_H

#include <Control.h>


class Botao : public Control{
    public:
        Botao(int x, int y, string s);
        void render();

        bool colisao(int l, int c);
        virtual ~Botao();
};

#endif // BOTAO_H
