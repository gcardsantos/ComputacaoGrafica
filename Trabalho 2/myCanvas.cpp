
// *********************************************************************
// Canvas para desenho - Versao C.
//  Autor: Cesar Tadeu Pozzer
//         07/2016
//
//  Pode ser utilizada para fazer desenhos ou animacoes, como jogos simples.
//  Tem tratamento de mosue
// *
// *   pozzer@inf.ufsm.br
// *   pozzer3@gmail.com
// *
//

#include "glCanvas2d.h"
#include "mainwindow.h"

#include <math.h>
#include <QWidget>
#include <QMessageBox>
#include <QWheelEvent>
#include <stdio.h>
#include <queue>

#include "Ponto.h"
#include "Retangulo.h"
#include "Reta.h"
#include "PenTool.h"
#include "Triangulo.h"

using namespace std;

#define TAM_INICIAL 10
#define RAIO 4

float global = 0;

vector<Retangulo*> retangulos;
vector<Reta*> retas;
vector<PenTool*> pen;
vector<Ponto*> pontos;
vector<Triangulo*> triangulos;

Objeto* obj;


int tipo = 0;
int cont = 0;
int xmov = 0, ymov = 0;
// *******************************************************************************
//Coloque seu codigo aqui, usando as funcoes da Canvas2D defindas na classe Canvas2D (arquivo glCanvas2d.h).
// *******************************************************************************
void Canvas2D::paintGL() //callback de desenho na canvas. Chamado pelo Timer definido em mainWindow.cpp
{
	clear(0.8, 0.8, 0.8);
	color(1, 0, 0);

	for (unsigned int i = 0; i < pontos.size(); i++)
		circleFill(pontos[i]->x, pontos[i]->y, RAIO, 20);

	for (unsigned int i = 0; i < retangulos.size(); i++)
		retangulos[i]->render();

	for (unsigned int i = 0; i < retas.size(); i++)
		retas[i]->render();

	for (unsigned int i = 0; i < pen.size(); i++)
		pen[i]->render();

    for (unsigned int i = 0; i < triangulos.size(); i++)
        triangulos[i]->render();

}


void Canvas2D::wheelEvent(QWheelEvent *event) //callback de mouse
{
    //ROTACIONA COM A BOLINHA, SE O MOUSE ESTIVER EM CIMA
	qDebug("Mouse Wheel event %d", event->delta());
	if (obj != NULL) {
		if (obj->ColisaoPonto(event->x(), (event->y() - this->height()) * -1)) {
			if (event->delta() > 0)
				obj->rotaciona(false);
			else
				obj->rotaciona(true);
		}
	}
		
}

//GERA RETANGULO
void CriaRetangulo(Canvas2D* c){
    Retangulo* r = new Retangulo(c, pontos[0], pontos[1], pontos[2], pontos[3]);
    retangulos.push_back(r);
    pontos.clear();
}

//GERA LINHA
void CriaLine(Canvas2D* c){
    Reta* r = new Reta(c, pontos[0], pontos[1]);
    retas.push_back(r);
    pontos.clear();
}

//GERA TRIANGULO
void CriaTriangulo(Canvas2D* c) {
	int xmenor = c->width(), xmaior = 0, ymenor = c->height(), ymaior = 0;

	for (unsigned int i = 0; i< pontos.size(); i++) {
		if (pontos[i]->x < xmenor)
			xmenor = pontos[i]->x;
		if (pontos[i]->x > xmaior)
			xmaior = pontos[i]->x;
		if (pontos[i]->y < ymenor)
			ymenor = pontos[i]->y;
		if (pontos[i]->y > ymaior)
			ymaior = pontos[i]->y;
	}

    Triangulo* t = new Triangulo(c, new Ponto(xmenor, ymenor), new Ponto(xmenor, ymaior), new Ponto(xmaior, ymaior), new Ponto(xmaior, ymenor));
    triangulos.push_back(t);
    pontos.clear();
}


//GERA CURVA ( PEGA OS MAIORES EIXOS E MENORES EIXOS PARA FAZER O QUADRADO)
void CriaCurva(Canvas2D* c) {
    int xmenor = c->width(), xmaior = 0, ymenor = c->height(), ymaior = 0;

    for(unsigned int i = 0; i< pontos.size(); i++){
        if(pontos[i]->x < xmenor)
            xmenor = pontos[i]->x;
        if(pontos[i]->x > xmaior)
            xmaior = pontos[i]->x;
        if(pontos[i]->y < ymenor)
            ymenor = pontos[i]->y;
        if(pontos[i]->y > ymaior)
            ymaior = pontos[i]->y;
    }

    PenTool* p = new PenTool(c, pontos, new Ponto(xmenor, ymenor), new Ponto(xmenor, ymaior), new Ponto(xmaior, ymaior), new Ponto(xmaior, ymenor));
    pen.push_back(p);
    pontos.clear();
    cont = 0;
}


//VERIFICA COLSAO COM ALGUM OBJETO
bool Colisao(int x, int y){

    for(unsigned int i = 0; i < retangulos.size(); i++){
        obj = retangulos[i]->ColisaoObjeto(x, y);
        if (obj != NULL) {
            return true;
        }
    }

	for (unsigned int i = 0; i < retas.size(); i++) {
		obj = retas[i]->ColisaoObjeto(x, y);
		if (obj != NULL) {
			return true;
		}
	}

    for(unsigned int i = 0; i < triangulos.size(); i++){
		obj = triangulos[i]->ColisaoObjeto(x, y);
		if (obj != NULL) {
			return true;
		}
    }

    for(unsigned int i = 0; i < pen.size(); i++){
		obj = pen[i]->ColisaoObjeto(x, y);
		if (obj != NULL) {
			return true;
		}
    }

    return false;
}

//TROCA COLISAO COM OBJETO (GERALMENTE USADO PRA DESABILITAR CAIXA ENVOLVENTE)
void SetColisaoObjeto(bool v){
    for(unsigned int i = 0; i < retangulos.size(); i++)
        retangulos[i]->setSelected(v);
    for(unsigned int i = 0; i < retas.size(); i++)
        retas[i]->setSelected(v);
    for(unsigned int i = 0; i < pen.size(); i++)
        pen[i]->setSelected(v);
    for(unsigned int i = 0; i < triangulos.size(); i++)
        triangulos[i]->setSelected(v);
}


//AO CLICAR, VERIFICA COLISAO COM ALGUM OBJETO, CASO NÃO HÁ, GERA UM NOVO OBJETO NA REGIÃO ESCOLHIDA AO CLICAR E ARRASTAR O MOUSE
void Canvas2D::mousePressEvent(QMouseEvent *event) //callback de mouse
{
    setFocus();
	
    if(event->buttons() == Qt::LeftButton){
        qDebug("%d", tipo);
        SetColisaoObjeto(false);
        if(pontos.size() > 0 || !Colisao(event->x(), (event->y() - this->height()) * -1)){
            obj = NULL;
            switch(tipo){
                case 1:
                    if(pontos.size() == 0){
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                    }
                    break;
                case 2:
                    if(pontos.size() == 0){
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                    }
                    break;
                case 3:
                    if(pontos.size() == 0){
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        cont++;
                    }else if (cont < 3){
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        cont++;
                    }else{
                        pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
                        CriaCurva(this);
                    }
                    break;
				case 4:
					if (pontos.size() == 0) {
						pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
						pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
						pontos.push_back(new Ponto(event->x(), (event->y() - this->height()) * -1));
					}
					break;
                default:
                    break;
            }
        }else{
            if(obj != NULL){
                if(!obj->ColisaoPonto(event->x(), (event->y() - this->height()) * -1)){
                    obj->movimenta(event->x(), (event->y() - this->height()) * -1);	
				}
            }
        }
    }
}


//GERA O OBJETO QUANDO TERMINA DE CLICAR
void Canvas2D::mouseReleaseEvent(QMouseEvent *event) //callback de mouse
{
    qDebug("\nMouse Release: %d %d", event->x(), event->y());
	
	if(obj != NULL && tipo == 3)
		obj->setSelectedPontos(false);

	if (pontos.size() > 0) {
		switch (tipo) {
			case 1:
				CriaRetangulo(this);
				break;
			case 2:
				CriaLine(this);
				break;
			case 4:
				CriaTriangulo(this);
				break;
			default:
				break;
		}
	}
		
}

//PEGA POSIÇÕES PARA GERAR O OBJETO EM MOVIMENTO
void Canvas2D::mouseMoveEvent(QMouseEvent * event) //callback de mouse
{
    qDebug("\nMouse Move: %d %d", event->x(), event->y());

    if(event->buttons() == Qt::LeftButton){
        if(pontos.size() > 0){
            switch(tipo){
                case 1:
                    pontos[0]->x = event->x();
                    pontos[0]->y = (event->y() - this->height()) * -1;
                    pontos[1]->x = event->x();
                    pontos[3]->y = (event->y() - this->height()) * -1;
                    break;
                case 2:
                    pontos[0]->x = event->x();
                    pontos[0]->y = (event->y() - this->height()) * -1;
                    break;
                case 4:
                    pontos[0]->x = event->x();
                    pontos[0]->y = (event->y() - this->height()) * -1;
                    pontos[1]->y = (event->y() - this->height()) * -1;
                    pontos[2]->x = (pontos[0]->x + pontos[1]->x)/ 2;
                    break;
                default:
                    break;
            }
        }else{
			if(obj != NULL)
				obj->movimenta(event->x(), (event->y() - this->height()) * -1);
        }
    }
}

//callback para botao definido na mainWindow.
void Canvas2D::showMsg()
{
    QMessageBox* msg = new QMessageBox(this);
    msg->setText("Msg GlWidget");
    msg->show();
}

//FAZ LEITURA DO ARQUIVO (LE/SALVA NESTA ORDEM - TIPO, QUANTIDADE DE OBJETOS, OBJETOS)
void Ler(Canvas2D* canvas, FILE* f){
    int qtd, ordem;
	double x, y;
    while(!feof(f)){
		fread(&tipo, sizeof(int), 1, f);
        fread(&qtd, sizeof(int), 1, f);
        switch(tipo){
            // RETANGULO
            case 1:
                //ARRUMAR A ORDEM
                for(int i = 0; i < qtd; i++){
					fread(&ordem, sizeof(int), 1, f);
                    for(int j = 0; j < 4; j++){
                        fread(&x, sizeof(double), 1, f);
                        fread(&y, sizeof(double), 1, f);
                        pontos.push_back(new Ponto(x, y));
                    }
                    CriaRetangulo(canvas);
                }
                break;
            case 2:
            // RETA
                for(int i = 0; i < qtd; i++){
					fread(&ordem, sizeof(int), 1, f);
                    for(int j = 0; j < 2; j++){                        
                        fread(&x, sizeof(double), 1, f);
                        fread(&y, sizeof(double), 1, f);
                        pontos.push_back(new Ponto(x, y));
                    }
                    CriaLine(canvas);
                }
                break;
            case 3:
            // MAO LIVRE
                for(int i = 0; i < qtd; i++){
					fread(&ordem, sizeof(int), 1, f);
                    for(int j = 0; j < 4; j++){
                        fread(&x, sizeof(double), 1, f);
                        fread(&y, sizeof(double), 1, f);
                        pontos.push_back(new Ponto(x, y));
                    }
                    CriaCurva(canvas);
                }
                break;
            case 4:
				//TRIANGULO
                for(int i = 0; i < qtd; i++){
                    fread(&ordem, sizeof(int), 1, f);
                    for(int j = 0; j < 4; j++){
                        fread(&x, sizeof(double), 1, f);
                        fread(&y, sizeof(double), 1, f);
                        pontos.push_back(new Ponto(x, y));
                    }
                    CriaTriangulo(canvas);
                }
                break;
            default:
                break;
        }
    }
}

//-----------------------------SELECOES DA UI DO CNAVAS
void Canvas2D::btnSelecao()
{
    tipo = 0;
    pontos.clear();
    obj = NULL;
}


void Canvas2D::btnRect(){
    if (tipo != 1)
        tipo = 1;
    else
        tipo = 0;
}
void Canvas2D::btnLine(){
    if (pontos.size() == 0) {
        if (tipo != 2)
            tipo = 2;
        else
            tipo = 0;
    }
}

void Canvas2D::btnPenTool(){
    if (pontos.size() == 0) {
        if (tipo != 3)
            tipo = 3;
        else
            tipo = 0;
    }
}

void Canvas2D::btnTriangulo()
{
    if(pontos.size() == 0){
        if (tipo != 4)
            tipo = 4;
        else
            tipo = 0;
    }
}

//FAZ SALVAMENTO DO ARQUIVO (LE/SALVA NESTA ORDEM - TIPO, QUANTIDADE DE OBJETOS, OBJETOS)
void Canvas2D::btnSalvar() {
    if (retangulos.size() > 0 || pen.size() > 0 || retas.size() > 0 || triangulos.size() > 0) {
		int qtd, tipo;
		FILE* file = fopen("dados.bin", "wb");
        if(file == NULL) return;
		
		if (retangulos.size() > 0) {	
			tipo = 1;
			qtd = retangulos.size();
			fwrite((const void*)&tipo, sizeof(int), 1, file);
			fwrite((const void*)&qtd, sizeof(int), 1, file);
			for (unsigned int i = 0; i < retangulos.size(); i++)
				retangulos[i]->salvar(file);
		}

		if (retas.size() > 0) {
			tipo = 2;
			qtd = retas.size();
			fwrite((const void*)&tipo, sizeof(int), 1, file);
			fwrite((const void*)&qtd, sizeof(int), 1, file);
			for (unsigned int i = 0; i < retas.size(); i++)
				retas[i]->salvar(file);
		}
		
		if (pen.size() > 0) {
			tipo = 3;
			qtd = pen.size();
			fwrite((const void*)&tipo, sizeof(int), 1, file);
			fwrite((const void*)&qtd, sizeof(int), 1, file);
			for (unsigned int i = 0; i < pen.size(); i++)
				pen[i]->salvar(file);
		}

        if(triangulos.size() > 0){
            tipo = 4;
            qtd = triangulos.size();
            fwrite((const void*)&tipo, sizeof(int), 1, file);
            fwrite((const void*)&qtd, sizeof(int), 1, file);
            for (unsigned int i = 0; i < triangulos.size(); i++)
                triangulos[i]->salvar(file);
        }

		fclose(file);
		retangulos.clear();
		pen.clear();
		retas.clear();
        triangulos.clear();
        //circulos.clear();
	}
}

void Canvas2D::btnAbrir() {
	retangulos.clear();
	pen.clear();
	retas.clear();

    FILE* file = fopen("dados.bin", "r");
    if(file == NULL) return;

    Ler(this, file);
    fclose(file);
}

void Canvas2D::btnApagar(){
	if (obj != NULL) {
		for (unsigned int i = 0; i < retangulos.size(); i++)
			if (retangulos[i]->selected)
				retangulos.erase(retangulos.begin() + i);

		for (unsigned int i = 0; i < retas.size(); i++)
			if (retas[i]->selected)
				retas.erase(retas.begin() + i);

		for (unsigned int i = 0; i < pen.size(); i++)
			if (pen[i]->selected)
				pen.erase(pen.begin() + i);

		for (unsigned int i = 0; i < triangulos.size(); i++)
			if (triangulos[i]->selected)
				triangulos.erase(triangulos.begin() + i);

    }
}

void Canvas2D::btnEscala(double num)
{
    if(obj != NULL && num > 0)
        obj->escala(obj->pontos, num);
}

void Canvas2D::btnExcluir(){
    retangulos.clear();
    pen.clear();
    retas.clear();
    triangulos.clear();
}


//ROTACIONA COM A TECLA (BOTAO DEL APAGA FIGURA)
void Canvas2D::keyPressEvent(QKeyEvent* event)
{
    qDebug("\nTecla pessionada  %d", event->key() );

    if(obj != NULL && event->key() == 16777223){
		btnApagar();
    }

    if(obj != NULL && event->key() == 16777234){
        for(unsigned int i = 0; i < obj->pontos.size(); i++)
            if(obj->pontos[i]->selected)
                obj->rotaciona(false);
    }
    if(obj != NULL && event->key() == 16777236){
        for(unsigned int i = 0; i < obj->pontos.size(); i++)
            if(obj->pontos[i]->selected)
                obj->rotaciona(true);
    }
}
