#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <Control.h>


class CheckBox : public Control{
    private:
        bool selected;
    public:
        CheckBox(int x, int y, string s);
        void render();
        bool colisao(int l, int c);

        void setSelected(bool v);
        bool getSelected();
        virtual ~CheckBox();
};


#endif // CHECKBOX_H
