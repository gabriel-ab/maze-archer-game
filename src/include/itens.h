#ifndef ITENS_H
#define ITENS_H

#include <raylib.h>
#include "personagem.h"

#define BOM_DAMAGE1 3   //closest
#define BOMB_RANGE1 30

#define BOM_DAMAGE2 2   //midrange
#define BOMB_RANGE2 60

#define BOM_DAMAGE3 1   //farest
#define BOMB_RANGE3 100

typedef struct Item{
    Sprite sprite;
    Vector2 posicao;
    bool ativo;
}Item;

typedef enum TrapStatus{
    TRAP_READY,
    TRAP_ON,
    TRAP_OFF
}TrapStatus;

typedef struct Trap{ //Trap
    Sprite sprite;
    Vector2 posicao;
    int damageFrame;
    int status;    
}Trap;

typedef struct Portal{
    Sprite sprite;
    Vector2 posicao;
    int destino;
}Portal;

void explosionCollision(Trap bomba, Personagem *fulano);
void animarBomba(Trap *bomba);
#endif