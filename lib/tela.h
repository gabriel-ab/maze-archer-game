#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>
#include "personagem.h"

#define LARGURA_TELA 1000
#define ALTURA_TELA 600

Rectangle tela = {100, 100, LARGURA_TELA, ALTURA_TELA};
int larguraAnterior = LARGURA_TELA;
int alturaAnterior = ALTURA_TELA;

int telaAtual = 0;
int telaAnterior = 0;

typedef enum TELAS {
    TELA_SEL_MAPA = -3,
    TELA_FRACASSO = -2,
    TELA_CONFIG = -1,
    TELA_MENU = 0,
    TELA_FASE_1 = 1,
    TELA_FASE_2 = 2,
    TELA_FASE_3 = 3,
    BOSS_FIGHT = 4,
    TELA_FASE_CUSTOM = 5,
}TELAS;

bool is_fullscreen = false; 

void telaCheia();
void atualizarCamera(Camera2D *cam, Vector2 posicao);
void verificarTamanhoTela();


Texture background;
Texture screenshot;

// ------------ SHADERS ----------- //

Shader shader;

void setShader();

//-------------- FONT ---------------//
Font font;

void setFont(char* fontPath);

// ------------- CÂMERA ----------- //
Camera2D cam;
void setTargetCamera(Personagem *target);
#endif
