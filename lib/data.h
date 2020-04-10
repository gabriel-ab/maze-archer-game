#ifndef DATA_H
#define DATA_H
#include <raylib.h>
#include <stdio.h>
#include "tela.h"

// CONFIGURAÇÕES DO PROGRAMA
#define MAX_RETANGULOS 200
#define MAX_ITENS 50
#define MAX_INIMIGOS 100

typedef struct Mapa
{
    Rectangle parede[MAX_RETANGULOS];
    int parede_atual;

    Rectangle piso[MAX_RETANGULOS];
    int piso_atual;
    
    Vector2 inimigo[MAX_INIMIGOS];
    int inimigo_atual;    
    
    Vector2 vida[MAX_ITENS];
    int vida_atual;    
    
    Vector2 flecha[MAX_ITENS];
    int flecha_atual;

    Vector2 inicio;
    Vector2 fim;
}Mapa;

typedef struct Objeto{
    int tipo;
    int indice;
}Objeto;

void carregar(const char *endereco, Mapa *fase);
void salvar(Mapa fase);
void exportar(Mapa fase);
#endif