#ifndef DRAW_H
#define DRAW_H
#include <raylib.h>
#include "data.h"

// ESPACAMENTOS DE TEXTO
#define ESPACAMENTO_P1 20
#define ESPACAMENTO_P2 30
#define ESPACAMENTO_P3 40

void desenhaGrid(void);
void desenhaTelaAjuda(void);

void drawFloor(Rectangle floor);
void drawWall(Rectangle wall);
void drawEnemie(Vector2 enemie);
void drawArrow(Vector2 arrow);
void drawLife(Vector2 life);
void drawPortal(Vector2 portal);
void drawInfoPoint(char *text, Vector2 pos);

#endif