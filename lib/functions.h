#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <raylib.h>
#include "tela.h"

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
    OPCAO_VIDA,
    OPCAO_INIMIGO
} Opcoes;

void desenhaGrid(void);
void desenhaTelaAjuda(void);
void telaOpcoes(int *tipo, Mapa *fase);
void telaBotaoDireito(int *opcao);
int telaSair(Mapa fase);

#endif