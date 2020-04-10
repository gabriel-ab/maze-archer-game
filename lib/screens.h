#ifndef SCREENS_H
#define SCREENS_H
#include <raylib.h>
#include "draw.h"
#include "data.h"

void telaOpcoes(int *tipo, Mapa *fase);
void telaBotaoDireito(int *opcao);
int telaSair(Mapa fase);

#endif