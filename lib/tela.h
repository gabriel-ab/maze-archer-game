#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

Rectangle tela = {0, 0, LARGURA_TELA, ALTURA_TELA};
Rectangle telaAnterior = {0, 0, LARGURA_TELA, ALTURA_TELA};

int telaAtual = 0;
int previousScreen = 0;

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
void redimensionarTela();

//-------------- BACKGROUND ---------------//
Texture2D background;
char* pathImageBackground;
char* pathImageBackgroundAnterior;

void setImageBackground(char* imagePath);
void updateBackground();

//-------------- HUD ---------------//
Texture2D vida;
Texture2D arrow;
Texture2D parede;
Texture2D piso;
Texture2D armadilha;
Font font;

void setTexture(Texture* texture, char* spritePath, int altura, int largura);
void setTextureCropped(Texture* texture, char* spritePath, Rectangle crop);
void setFont(char* fontPath);


void drawHUD(int quantidadeVida, int quantidadeArrow);


#endif
