#ifndef MOTOR_H
#define MOTOR_H

#include "Virabrequim.h"
#include "Pistao.h"
#include "Biela.h"
class Motor
{
    public:
        Motor();
        Virabrequim* vira;
        Pistao* p;
        Biela* b;
        void AddPistao(Pistao* p);
        virtual ~Motor();
    protected:
    private:
};

#endif // MOTOR_H
