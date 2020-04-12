#ifndef INCLUDED_DRAW_H
#define INCLUDED_DRAW_H

#include <raylib.h>
#include "projetil.h"
#include "itens.h"
#include "tela.h"

void drawXala(Personagem* xala);
void drawFlecha(Projetil flecha[], Personagem fulano);
void drawInimigos(Personagem inimigos[], int quantidade);
void drawParedes(Rectangle PAREDES[], int tamanho);
void drawPiso(Rectangle PISO[], int tamanho);
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho);
void drawArmadilhasRec(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec);
void drawSprite(Sprite sprite, Vector2 posicao, Vector2 origem, float rotacao, float escala, Color cor);
void drawMenuBackground(Color cor);
void drawPortal(Portal port, float size, Color color);
void drawButtonD(const char *text, Rectangle button, bool selected);
void drawButtonEx(const char *texto, Rectangle botao, Color cor);

//-------------- HUD ---------------//
void drawHUD(int quantidadeVida, int quantidadeArrow);

#endif