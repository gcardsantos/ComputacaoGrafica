#ifndef PONTO_H
#define PONTO_H


class Ponto
{
public:
    float x, y, z;

    Ponto(float x, float y, float z);
    void Translada(float x, float y, float z);
    void RotacaoX(float ang);
    void RotacaoY(float ang);
    void RotacaoZ(float ang);
};

#endif // PONTO_H
