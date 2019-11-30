#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>

#define LARGURA_TELA 800
#define ALTURA_TELA 500

Rectangle tela = {100, 100, LARGURA_TELA, ALTURA_TELA};
int larguraAnterior = 800;
int alturaAnterior = 500;

int telaAtual = 0;
int telaAnterior = 0;

typedef enum{
    TELA_FRACASSO = -2,
    TELA_CONFIG = -1,
    TELA_MENU = 0,
    TELA_FASE_1 = 1,
    TELA_FASE_3 = 3,
};

bool is_fullscreen = false; 

void telaCheia();
void atualizarCamera(Camera2D *cam, Vector2 posicao);
void verificarTamanhoTela();

//-------------- BACKGROUND ---------------//
Texture2D background;
char* pathImageBackground;
char* pathImageBackgroundAnterior;

void setImageBackground(char* imagePath);
void updateBackground();

//-------------- HUD ---------------//

void drawHUD(int quantidadeVida, int quantidadeArrow);

//-------------- TEXTURE ---------------//

Texture2D vida;
Texture2D arrow;
Texture2D parede;
Texture2D piso;
Texture2D armadilha;

void setTexture(Texture* texture, char* spritePath, int altura, int largura);
void setTextureCropped(Texture* texture, char* spritePath, Rectangle crop);

//-------------- FONT ---------------//
Font font;

void setFont(char* fontPath);


#endif
