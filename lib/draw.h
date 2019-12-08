#ifndef INCLUDED_DRAW_H
#define INCLUDED_DRAW_H

#include <raylib.h>
#include "personagem.h"
#include "projetil.h"

int count = 0;
int currentFrame = 0;
int frameCount = 0;

void drawXala(Personagem* xala, int contador);
void drawFlecha(Projetil flecha[], int quantidade);
void drawInimigos(Personagem inimigos[], int quantidade);
void drawParedes(Rectangle PAREDES[], int tamanho);
void drawPiso(Rectangle PISO[], int tamanho);
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho);
void drawArmadilhasRec(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec);

#endif