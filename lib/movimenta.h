#include <raylib.h>
#include "personagem.h"

#ifndef MOVIMENTA_H_INCLUDED
#define MOVIMENTA_H_INCLUDED

#define VELOCIDADE_MAX 0.05
#define ACELERACAO 0.5
#define TAXA_ATRITO 0.05

//Temporario
#define TAM_MAPA 4
Color colideCima = GREEN;
Color colideBaixo = GREEN;
Color colideEsq = GREEN;
Color colideDir = GREEN;
//Temporario

int colisaoCima(Personagem *fulano, Rectangle *MAPA);
int colisaoBaixo(Personagem *fulano, Rectangle *MAPA);
int colisaoEsquerda(Personagem *fulano, Rectangle *MAPA);
int colisaoDireita(Personagem *fulano, Rectangle *MAPA);

void atualizarColisao(Personagem *fulano);
void aplicarInercia(Personagem *fulano);
void aplicarAtrito(Personagem *fulano, float taxa);

void movimentar(Personagem *fulano, Rectangle *MAPA, float *angle);
void movimentarV(Vector2 *coisa);

#endif