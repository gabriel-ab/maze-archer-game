#ifndef MOVIMENTA_H_INCLUDED
#define MOVIMENTA_H_INCLUDED

#include <raylib.h>
#include "personagem.h"
#include "acao.h"



//Temporario

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
void aplicarInerciaV(Vector2 *posicao, Vector2 velocidade);

void aplicarAtrito(Personagem *fulano, float taxa);
void aplicarAtritoProjetil(Projetil *bala, float taxa);

void movimentar(Personagem *fulano, Rectangle *MAPA);
void movimentarV(Vector2 *coisa);

#endif
