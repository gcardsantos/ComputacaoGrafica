#include "CheckBox.h"
#include "gl_canvas2d.h"


CheckBox::CheckBox(int x, int y, string s):Control(x, y, s, true){
    selected = false;
}

void CheckBox::render(){
    if(selected)
        rectFill(x, y, x+10, y+10);
    else
        rect(x, y, x+10, y+10);

    text(x+20, y, label.c_str());
}

bool CheckBox::colisao(int l, int c){
    if((l > x && l < x+10) && (c > y && c < y+10)){
        return true;
    }else{
        return false;
    }
}

void CheckBox::setSelected(bool v){
    selected = v;
}

bool CheckBox::getSelected(){
    return selected;
}

CheckBox::~CheckBox()
{
    //dtor
}
