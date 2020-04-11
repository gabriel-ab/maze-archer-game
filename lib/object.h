#ifndef OBJECT_H
#define FUNCTIONS_H
#include <raylib.h>
#include "data.h"

typedef struct Objeto{
    int tipo;
    int indice;
}Objeto;

Objeto selecionarObjeto(Mapa fase, Camera2D camera);
void CheckFileOnScreen(Mapa *fase);

#endif