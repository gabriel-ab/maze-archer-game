#ifndef MOVIMENTA_H_INCLUDED
#define MOVIMENTA_H_INCLUDED

#include <raylib.h>
#include "personagem.h"
#include "projetil.h"

int colisaoCima(Personagem *fulano, Rectangle *MAPA, int tamMapa);
int colisaoBaixo(Personagem *fulano, Rectangle *MAPA, int tamMapa);
int colisaoEsquerda(Personagem *fulano, Rectangle *MAPA, int tamMapa);
int colisaoDireita(Personagem *fulano, Rectangle *MAPA, int tamMapa);

void colisaoPersonagem(Personagem *fulano, Rectangle *MAPA, int tamMapa);

void atualizarLinhasColisao(Personagem *fulano);
void atualizarPersonagem(Personagem *inimigo);

void aplicarInercia(Personagem *fulano);
void aplicarInerciaV(Vector2 *posicao, Vector2 velocidade);

void aplicarAtrito(Personagem *fulano, float taxa);
void aplicarAtritoProjetil(Projetil *bala, float taxa);

void movimentar(Personagem *fulano);
void movimentarV(Vector2 *coisa);

#endif
