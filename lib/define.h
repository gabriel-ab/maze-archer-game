#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

//Definições Gerais para regulagem do jogo

bool jogo_rodando = true;


#define ACELERACAO 0.5
#define TAXA_ATRITO 0.05
#define N_MAX_PROJETEIS 5 //NUMERO MAXIMO DE PROJETEIS POSSIVEIS NO JOGO
#define TEMPO_MAX_INVULNERAVEL 2
#define TAM_MAPA1 30 //temporario

bool jogo_rodando = true;
bool isPaused;
bool isRestarting;

int tempo_invunerabilidade = TEMPO_MAX_INVULNERAVEL;
int vida_maxima = 3;


#endif
