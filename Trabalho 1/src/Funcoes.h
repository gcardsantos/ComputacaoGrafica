#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

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
#include "Botao.h"
#include "Bola.h"
#include "CheckBox.h"
#include "gl_canvas2d.h"

#define ALTURA 720
#define LARGURA 1280
#define INIT_X 20
#define MIDDLE_Y 400
#define M_PI 3.1416
#define RAIO 5
using namespace std;

unsigned int qtd_amostras = 0;
string num_amostras;
int distancia;

std::vector<Control*> amostras;
std::vector<Control*> dct;
std::vector<Control*> idct;
std::vector<Control*> diferencas;
std::vector<Control*> objetos;

void CriaBarra();
void Reiniciar();
void ler_arq();
void Gravar();
void CriaMenu();
void TracaRetas(vector<Control*> v, float r, float g, float b);
void Printar(vector<Control*> v);
void SetVisible(vector<Control*> v, bool b);
void SetSelected(vector<Control*> v, bool b, char* s);
int ColideObjeto(vector<Control*> v, int x, int y);
void DCT(int N);
void IDCT(int N);
void Diferenca(vector<Control*> v1, vector<Control*> v2);
void GeraFuncao(vector<Control*> v);
void ColisaoControles(int x, int y);
void FocusObjeto(vector<Control*> v);
void ColisaoBola(vector<Control*> v, int x, int y);
#endif // FUNCOES_H_INCLUDED
