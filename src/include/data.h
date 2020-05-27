#ifndef INCLUDED_SAVE_H
#define INCLUDED_SAVE_H
#include "personagem.h"
#include "itens.h"

//Definições Gerais para regulagem do jogo
#define MAX_RETANGULOS 200  
#define MAX_INIMIGOS 100    // inimigos
#define MAX_ITENS 50        // itens do cenario

char diretorio[128]; //Endereço da pasta de fases

int vida_no_save;
int flechas_no_save;

typedef struct Mapa
{
    Rectangle parede[MAX_RETANGULOS];
    int n_paredes;

    Rectangle piso[MAX_RETANGULOS];
    int n_pisos;
    
    Personagem inimigo[MAX_INIMIGOS];
    int n_inimigos;    
    
    Item vida[MAX_ITENS];
    int n_vidas;    
    
    Item flecha[MAX_ITENS];
    int n_flechas;

    Trap bomba[MAX_RETANGULOS];
    int n_bombas;

    Trap armadilha[MAX_RETANGULOS];
    int n_armadilhas;

    Vector2 inicio;
    Vector2 fim;
} Mapa;

void save();
int load();
Mapa LoadMapa(const char *endereco);

#endif