#ifndef INCLUDED_DRAW_H
#define INCLUDED_DRAW_H

#include <raylib.h>
#include "personagem.h"

int count = 0;
int currentFrame = 0;
int frameCount = 0;

void drawXala(Personagem* xala, int contador);
void drawParedes(Rectangle PAREDES[], int tamanho);
void drawPiso(Rectangle PISO[], int tamanho, Rectangle frameRec);
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec);

#endif