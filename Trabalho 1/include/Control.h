#ifndef CONTROL_H
#define CONTROL_H

#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Control
{
    public:
        int x, y;
        bool visible;
        bool focus;
        string label;
        signed short valor;

        Control(int a, int b, bool v);
        Control(int a, int b, string t, bool v);
        Control(int a, int b, signed short num, bool vis);
        void setVisible(bool v);
        virtual void render();
        virtual bool colisao(int l, int c);
        virtual void setSelected(bool v);
        virtual bool getSelected();
        ~Control();
};

#endif // CONTROL_H
