#include "Control.h"

using namespace std;

Control::Control(int a, int b, bool v){
    x = a;
    y = b;
    visible = v;
    focus = false;
}

Control::Control(int a, int b, string t, bool v){
    x = a;
    y = b;
    label = t;
    visible = v;
}

Control::Control(int a, int b, signed short num, bool vis){
    x = a;
    y = b;
    stringstream aux;
    aux << num;
    label = aux.str();
    valor = num;
    visible = vis;
}

void Control::setVisible(bool v){
    visible = v;
}

void Control::render(){
    cout << "x: "<<x<<endl;
}

bool Control::colisao(int l, int c){
    return false;
}

void Control::setSelected(bool v){

}

bool Control::getSelected(){
    return false;
}

Control::~Control()
{
    //dtor
}
