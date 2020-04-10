#ifndef TELA_H
#include <raylib.h>
#define TELA_H

//********CONFIGURAÇÔES DE TELA*********
#define larguraTela 800
#define alturaTela 500

Rectangle tela;
Rectangle telaAnterior;

// Para saber o estado atual
int Is_Fullscreen;
Vector2 posCam;

//chama a função toggleFulscreen() guardando o tamanho da tela anterior
void telaCheia(void);
void atualizaCamera(Camera2D *camera);
#endif