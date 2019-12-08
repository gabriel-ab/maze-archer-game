#ifndef TELA_H_INCLUDED
#define TELA_H_INCLUDED

#include <raylib.h>
#include "personagem.h"

#define LARGURA_TELA 1366
#define ALTURA_TELA 768

Rectangle tela = {100, 100, LARGURA_TELA, ALTURA_TELA};
int larguraAnterior = 800;
int alturaAnterior = 500;

int telaAtual = 0;
int telaAnterior = 0;

typedef enum TELAS {
    TELA_FRACASSO = -2,
    TELA_CONFIG = -1,
    TELA_MENU = 0,
    TELA_FASE_1 = 1,
    TELA_FASE_2 = 2,
    TELA_FASE_3 = 3,
    TELA_FASE_4 = 4,
    BOSS_FIGHT = 5
}TELAS;

bool is_fullscreen = false; 

void telaCheia();
void atualizarCamera(Camera2D *cam, Vector2 posicao);
void verificarTamanhoTela();

//-------------- BACKGROUND ---------------//
Texture2D background;
char* pathImageBackground;
char* pathImageBackgroundAnterior;

void setPathImageBackground(char* imagePath);
void setImageBackground(Image backgroundImage);
void updateBackground();

//-------------- HUD ---------------//

void drawHUD(int quantidadeVida, int quantidadeArrow);

//-------------- TEXTURE ---------------//

Texture2D vidaTexture;     //HUD 
Texture2D arrowTexture;    //HUD

Texture2D flechasTexture;  
Texture2D paredeTexture;
Texture2D pisoTexture;
Texture2D armadilhaTexture;
Texture2D xalaTexture;
Texture2D portalTexture;

void setTexture(Texture* texture, char* spritePath, int altura, int largura);
void setTextureCropped(Texture* texture, char* spritePath, Rectangle crop);

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
