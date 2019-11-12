#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

Rectangle tela = {LARGURA_TELA, ALTURA_TELA, LARGURA_TELA, ALTURA_TELA};
Rectangle telaAnterior = {LARGURA_TELA, ALTURA_TELA, LARGURA_TELA, ALTURA_TELA};

bool is_fullscreen = false; 

void telaCheia();
void atualizaCamera(Camera2D *camera);

#endif
