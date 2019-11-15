#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

Rectangle tela = {0, 0, LARGURA_TELA, ALTURA_TELA};
Rectangle telaAnterior = {0, 0, LARGURA_TELA, ALTURA_TELA};

bool is_fullscreen = false; 

void telaCheia();
void cameraSegue(Camera2D *cam, Rectangle rec);

#endif
