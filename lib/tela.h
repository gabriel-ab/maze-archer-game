#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

Rectangle tela = {0, 0, LARGURA_TELA, ALTURA_TELA};
Rectangle telaAnterior = {0, 0, LARGURA_TELA, ALTURA_TELA};

int telaAtual = 0;

typedef enum{
    TELA_FRACASSO = -2,
    TELA_CONFIG = -1,
    TELA_MENU = 0,
    TELA_FASE1 = 1,
    TELA_FASE_3 = 3,
};

bool is_fullscreen = false; 

void telaCheia();
void cameraSegueFocoRec(Camera2D *cam, Vector2 foco, Rectangle rec);


//-------------- BACKGROUND ---------------//
Texture2D background;
char* pathImageBackground;
char* pathImageBackgroundAnterior;

void setImageBackground(char* imagePath);

void updateBackground();




//-------------- HUD ---------------//
Texture2D vida;

void setVidaSprite(char* spritePath);
void drawHUD(int quantidadeVida);


#endif
