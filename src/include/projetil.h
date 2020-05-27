#ifndef ACAO_H_INCLUDED
#define ACAO_H_INCLUDED

#include <raylib.h>
#include "personagem.h"

#define MAX_FLECHAS 10
#define VELOCIDADE_Projetil 20;

int projetil_atual;

typedef enum Projetil_status {
    MIRANDO,
    ATIVO,
    RESGATAVEL,
    INATIVA
} Projetil_status;
typedef struct projetil {
    Sprite sprite;
    Vector2 posicao;
    Vector2 velocidade;
    float angulo;
    int ativa;
    double tempoParaResgatar;
} Projetil;

void mira(Personagem fulano, Projetil *bala, Camera2D cam);
void atira(Personagem fulano, Projetil *bala);

int colisaoProjetil_inimigo(Projetil *bala, Personagem *inimigo, int n_inimigos);
int colisaoProjetil_mapa(Projetil *bala, Rectangle *MAPA, int n_mapa);

#endif