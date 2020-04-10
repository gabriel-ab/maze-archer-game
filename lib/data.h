#ifndef DATA_H
#define DATA_H
#include <raylib.h>
#include <stdio.h>
#include "window.h"

// CONFIGURAÇÕES DO PROGRAMA
#define MAX_RETANGULOS 200
#define MAX_ITENS 50
#define MAX_INIMIGOS 100

#define paredeH3 (Rectangle) { 0, 0, 32, 128 }
#define paredeV3 (Rectangle) { 0, 0, 128, 32 }
#define paredeH5 (Rectangle) { 0, 0, 32, 6 * 32 }
#define paredeV5 (Rectangle) { 0, 0, 6 * 32, 32 }
#define paredeH8 (Rectangle) { 0, 0, 32, 320 }
#define paredeV8 (Rectangle) { 0, 0, 320, 32 }

#define piso2_2 (Rectangle) { 0, 0, 64, 64 }
#define piso4_4 (Rectangle) { 0, 0, 4 * 32, 4 * 32 }
#define piso6_6 (Rectangle) { 0, 0, 6 * 32, 6 * 32 }
#define piso8_8 (Rectangle) { 0, 0, 8 * 32, 8 * 32 }
#define piso16_6 (Rectangle) { 0, 0, 16 * 32, 6 * 32 }
#define piso6_16 (Rectangle) { 0, 0, 6 * 32, 16 * 32 }

typedef enum TiposObjetos{
    NENHUM = -1,
    PAREDE,
    PISO,
    INIMIGO,
    VIDA,
    FLECHA
} TiposObjetos;

typedef enum Opcoes{
    OPCAO_INICIO = 0,
    OPCAO_FIM,
} Opcoes;

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