#ifndef INCLUDED_DRAW_H
#define INCLUDED_DRAW_H

#include <raylib.h>
#include "personagem.h"
#include "projetil.h"

int currentFrame = 0;
int frameCount = 0;

void drawXala(Personagem* xala);
void drawFlecha(Projetil flecha[], Personagem fulano);
void drawInimigos(Personagem inimigos[], int quantidade);
void drawParedes(Rectangle PAREDES[], int tamanho);
void drawPiso(Rectangle PISO[], int tamanho);
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho);
void drawArmadilhasRec(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec);
void drawSprite(Sprite sprite, Vector2 posicao, Vector2 origem, float rotacao, float escala, Color cor);
void drawMenuBackground(Color cor);

//-------------- HUD ---------------//
void drawHUD(int quantidadeVida, int quantidadeArrow);

//Segmentos do spritesheet de animação de xala
Segmento segmentos_xala[] = {
    0, 0, 3, //linha, inicio e final
    1, 0, 3
};

#endif