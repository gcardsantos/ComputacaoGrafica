#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Control.h"
#include "Bola.h"
#include "Botao.h"
#include "CheckBox.h"
#include "gl_canvas2d.h"
#include "Bmp.h"

#define ALTURA 720
#define LARGURA 1280
#define INIT_X 20
#define MIDDLE_Y 450
#define INIT_DCT 730
#define MIDDLE_DCT 330
#define M_PI 3.1416
#define RAIO 5
using namespace std;

unsigned int qtd_amostras = 0;
int escala = 0;
string num_amostras;
int distancia = 0;

vector<Control*> amostras;
vector<Control*> dct;
vector<Control*> idct;
vector<Control*> diferencas;
vector<Control*> objetos;

vector<signed short> numeros_dct;
vector<signed short> quantizacao;


//desenha toda interface principal que nao seja um controle
void CriaBarra(){
    color(0, 0, 0);
    line(INIT_X, MIDDLE_Y-200, INIT_X, MIDDLE_Y+200);
    line(INIT_X, MIDDLE_Y, INIT_X + 600, MIDDLE_Y);
    text(INIT_X + 100, MIDDLE_Y + 250, "Quantidade amostras: ");
    text(INIT_X + 310, MIDDLE_Y + 250, num_amostras.c_str());
    text(INIT_X + 520, MIDDLE_Y - 180, "Original");
    text(INIT_X + 520, MIDDLE_Y - 200, "IDCT");
    text(INIT_X + 520, MIDDLE_Y - 220, "Diferencas");
    text(INIT_X, MIDDLE_Y - 220, "-100");
    text(INIT_X, MIDDLE_Y + 210, "+100");
    rect(INIT_X - 15, MIDDLE_Y - 230, INIT_X + 630, MIDDLE_Y + 230);
    rect(INIT_DCT - 10, MIDDLE_DCT - 110, INIT_DCT +260, MIDDLE_DCT + 110);

    line(INIT_DCT, MIDDLE_DCT - 100, INIT_DCT, MIDDLE_DCT + 100);
    line(INIT_DCT, MIDDLE_DCT, INIT_DCT + 250, MIDDLE_DCT);
    text(INIT_DCT + 110, MIDDLE_DCT + 90, "DCT");
    color(1, 0, 0);
    circleFill(INIT_X + 510, MIDDLE_Y - 176, 4, 4);
    color(0, 0, 1);
    circleFill(INIT_X + 510, MIDDLE_Y - 196, 4, 4);
    color(0, 1, 0);
    circleFill(INIT_X + 510, MIDDLE_Y - 216, 4, 4);
    color(0,0,0);
}


//limpa os vetores pra iniciar uma nova aplicaçao
void Reiniciar(){
    amostras.clear();
    dct.clear();
    idct.clear();
    diferencas.clear();
    qtd_amostras = 0;
    num_amostras.clear();
    quantizacao.clear();
}

void ler_arq(){
    signed short num = 0;
    FILE* f = fopen("samples.dct", "r");
    stringstream ss;

    if(f != NULL){
        if(amostras.size() > 0){
            Reiniciar();
        }
        fread(&qtd_amostras, sizeof(unsigned int), 1, f);
        distancia = 600/qtd_amostras;

        //variavel '' num_amostras '' usada pra printar na tela a qtd de amostras
        ss << qtd_amostras;
        num_amostras = ss.str();

        //le cada amostra e coloca no vetor de amostras
        for(int i = 0; i < qtd_amostras; i++){
            fread(&num, sizeof(signed short), 1, f);
            //tamanho da reta coincidiu com o MIDDLE_Y
            amostras.push_back(new Bola((INIT_X+10) + i * distancia, (num* 2) + MIDDLE_Y, RAIO, 1, 0, 0, num, false));
        }
        fclose(f);
    }
}

void Gravar(){
    cout << "------------------------------------" << endl;
    signed short num = 0;
    stringstream ss;
    FILE* f = fopen("samples.dct", "w");
    if(f == NULL) return;
    fwrite((const void*)&qtd_amostras, sizeof(unsigned int), 1, f);
    for(int i = 0; i < qtd_amostras; i++){
        fwrite((const void*)&idct[i]->valor, sizeof(signed short ), 1, f);
    }
    fclose(f);
}

//cria objetos funcionais da tela
void CriaMenu(){
    objetos.push_back(new Botao(INIT_X, 100, "CARREGAR"));
    objetos.push_back(new Botao(INIT_X + 110, 100, "SALVAR"));
    objetos.push_back(new Botao(INIT_X + 220, 100, "APLICAR"));
    objetos.push_back(new Botao(INIT_X + 330, 100, "RANDOM"));
    objetos.push_back(new CheckBox(ALTURA, LARGURA - 630, "Originais"));
    objetos.push_back(new CheckBox(ALTURA, LARGURA - 680, "Reconstruidos"));
    objetos.push_back(new CheckBox(ALTURA, LARGURA - 730, "Diferencas"));
    objetos.push_back(new CheckBox(ALTURA, LARGURA - 780, "Lena 2D"));
}

//traca retas entre bolinhas
void TracaRetas(vector<Control*> v, float r, float g, float b){
    if(v.size() > 2){
        color(r, g, b);
        for(int i = 0; i < v.size() - 1; i++){
            if(v[i]->visible == false) return;
            line(v[i]->x,v[i]->y, v[i+1]->x, v[i+1]->y);
        }
    }
}

//Printa qualquer objeto que seja um controle (bola, checkbox, botao)
void Printar(vector<Control*> v){
    for(int i = 0; i < v.size(); i++){
        v[i]->render();
    }
}

//Coloca os controles visiveis
void SetVisible(vector<Control*> v, bool b){
    for(int i = 0; i < v.size(); i++){
        v[i]->visible = b;
    }
}

//ativa e desativa checkbox
void SetSelected(vector<Control*> v, bool b, char* s){
    for(int i = 0; i < v.size(); i++){
        if(v[i]->label.compare(s) == 0){
            v[i]->setSelected(b);
            return;
        }
    }
}

//verifica colisao com qualquer objeto
int ColideObjeto(vector<Control*> v, int x, int y){
    for(int i = 0; i < v.size(); i++){
        if(v[i]->colisao(x, y)){
            return i;
        }
    }
    return -1;
}

//calculo de escala
float CalculoEscala(int maior, int tela){
    if(maior == 0) return 1;
    return ((float)tela/maior);
}

void GeraVetorQuantizacao(int fim){
    vector<int> quantiz;
    for(int i = 1; i < fim + 1; i++)
        quantiz.push_back((0.5*i)+1);

    for(int i = 0; i < qtd_amostras; i++)
        quantizacao.push_back((signed short)(dct[i]->valor / quantiz[i]));
}

void DCT(int N) {
    signed short maior = 0;

    for(int i = 0; i < N; ++i){
        double sum = 0.;
        double s;
        double n;
        if (i == 0) s = sqrt(0.5);
        else s = 1.0;

        for (int n = 0; n < N; ++n)
            sum += s * amostras[n]->valor * cos(M_PI * (n + 0.5) * i / N);

        n = sum * sqrt(2. / N);

        numeros_dct.push_back(n);

        if (n < 0)
            n *=  -1;

        //guarda o maior pra criar a escala do grafico DCT
        if (n > maior)
            maior = n;
    }
    float escala = CalculoEscala(maior * 2, 150);
    float x = 250/qtd_amostras;
    for(int i = 0; i < N; i++){
        dct.push_back(new Bola(INIT_DCT + (i * x), (escala * numeros_dct[i]) + MIDDLE_DCT , 1, 0, 0, 0, numeros_dct[i], true));
    }

}

void IDCT(int N){
    for (int i = 0; i < N; ++i) {
        double soma = 0.;
        double s;
        for (int k = 0; k < N; ++k){
            if(k == 0) s = sqrt(0.5);
            else s = 1.0;
            soma += s * quantizacao[k] * cos(M_PI * (i + 0.5) * k / N);
        }
        idct.push_back(new Bola((INIT_X+10) + i * distancia, (((signed short)(soma * sqrt(2.0 / N)))* 2) + MIDDLE_Y , RAIO, 0, 0, 1, (soma * sqrt(2.0 / N)), true));
    }
}

void Diferenca(vector<Control*> v1, vector<Control*> v2){
    if((v1.size() > 2 && v2.size() > 2) && (v1.size() == v2.size())){
        for(int i = 0; i < v1.size(); i++){
            Bola* b = new Bola(v1[i]->x, (v1[i]->y - v2[i]->y) + MIDDLE_Y, RAIO, 0, 1, 0, (atoi(v1[i]->label.c_str())) - (atoi(v2[i]->label.c_str())), false);
            diferencas.push_back(b);
        }
    }
}

//gera uma nova onda
void GeraFuncao(vector<Control*> v){
    signed short num;
    qtd_amostras = rand()%70 + 20;
    distancia = 600/qtd_amostras;
    stringstream ss;
    ss << qtd_amostras;
    num_amostras = ss.str();
    for(int i = 0; i < qtd_amostras; i++){
        num = rand()%200 - 100;
        amostras.push_back(new Bola((INIT_X+10) + i * distancia, (num* 2) + MIDDLE_Y, RAIO, 1, 0, 0, num, true));
    }
}

void DCT_2D(Bmp* imagem){
    for(int i = 0; i < (imagem->getHeight() * imagem->getWidth())*3 + 1; i++)
        cout << i << " -- " <<(int) imagem->getImage()[i] << endl;
}

void IDCT_2D(vector<Control*> v){

}

//colisao com os controles e acoes com cada um
void ColisaoControles(int x, int y){
    int i;
    if((i = ColideObjeto(objetos, x, y)) != -1){
        if(objetos[i]->label.compare("CARREGAR") == 0){
            Reiniciar();
            ler_arq();
            SetVisible(amostras, true);
            SetSelected(objetos, true, "Originais");
            SetSelected(objetos, false, "Reconstruidos");
            SetSelected(objetos, false, "Diferencas");
        }else if(objetos[i]->label.compare("SALVAR") == 0){
            if(idct.size() > 0){
                Gravar();
                Reiniciar();
            }
        }else if(objetos[i]->label.compare("APLICAR") == 0){
            if(idct.size() == 0){
                DCT(qtd_amostras);
                GeraVetorQuantizacao(qtd_amostras);
                IDCT(qtd_amostras);
                SetVisible(dct, true);
                SetSelected(objetos, true, "Reconstruidos");
            }
        }else if(objetos[i]->label.compare("RANDOM") == 0){
            Reiniciar();
            GeraFuncao(amostras);
            SetVisible(amostras, true);
            SetSelected(objetos, false, "Reconstruidos");
        }else if(objetos[i]->label.compare("Originais") == 0){
            objetos[i]->setSelected(!objetos[i]->getSelected());
            SetVisible(amostras, objetos[i]->getSelected());
        }else if(objetos[i]->label.compare("Reconstruidos") == 0){
            objetos[i]->setSelected(!objetos[i]->getSelected());
            SetVisible(idct, objetos[i]->getSelected());
        }else if(objetos[i]->label.compare("Diferencas") == 0){
            diferencas.clear();
            Diferenca(amostras, idct);
            SetVisible(diferencas, !objetos[i]->getSelected());
            objetos[i]->setSelected(!objetos[i]->getSelected());
        }else if(objetos[i]->label.compare("Lena 2D") == 0){
            Reiniciar();
            Bmp* imagem = new Bmp("lena128_24bits.bmp");
            DCT_2D(imagem);
            IDCT_2D(amostras);
            SetVisible(amostras, true);
            SetVisible(dct, true);
            objetos[i]->setSelected(!objetos[i]->getSelected());
        }
        return;
    }
}
//verifica foco no objeto (bolas)
void FocusObjeto(vector<Control*> v){
    for (int i = 0; i < v.size(); i++){
        if(v[i]->focus == true)
            v[i]->focus = false;
    }
}

//colisao para fazer foco na bola
void ColisaoBola(vector<Control*> v, int x, int y){
    int i = ColideObjeto(v, x, y);
    if(i != -1){
        v[i]->focus = true;
    }else{
        FocusObjeto(v);
    }
}

/* ---------------------- Funções Canvas ---------------------- */

void keyboard(int key){

}
void keyboardUp(int key){

}

void mouse(int button, int state, int x, int y)
{
    y = (y-ALTURA)* -1;
    if(button == 0 && state == 0){
        ColisaoControles(x, y);
        return;
    }else{
        ColisaoBola(amostras, x, y);
        ColisaoBola(idct, x, y);
        ColisaoBola(diferencas, x, y);
    }
}

void render(){
    CriaBarra();
    Printar(objetos);
    Printar(amostras);
    Printar(dct);
    Printar(idct);
    Printar(diferencas);
    TracaRetas(amostras, 1, 0, 0);
    TracaRetas(idct, 0, 0, 1);
    TracaRetas(diferencas, 0, 1, 0);
    TracaRetas(dct, 0, 0, 0);
}

int main(void)
{
    CriaMenu();
    initCanvas(LARGURA, ALTURA);
    runCanvas();
}
