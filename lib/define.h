#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <raylib.h>
#include "textura.h"
#include "personagem.h"

char diretorio[150]; //Endereço da pasta de fases

bool jogo_rodando = true;
bool isPaused;
bool isRestarting;

//Definições Gerais para regulagem do jogo
#define MAX_RETANGULOS 200
#define MAX_INIMIGOS 100
#define MAX_ITENS 50

#define ACELERACAO 0.5
#define TAXA_ATRITO 0.1
#define TEMPO_MAX_INVULNERAVEL 2

#define MAX_FLECHAS 10

int tempo_invunerabilidade = TEMPO_MAX_INVULNERAVEL;
int vida_no_save = 3;
int flechas_no_save = 2;

double TEMPO; //tempo geral
bool mirando;
int projetil_atual = 0;

#endif
