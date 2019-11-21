#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

//Definições Gerais para regulagem do jogo

bool jogo_rodando = true;

#define VEL_MAX_PERSONAGEM 3
#define ACELERACAO 0.5
#define TAXA_ATRITO 0.05
#define TAM_MAPA1 30

// 1/3 do tamanho da tela (Centralizado)
#define REC_TELA_1_POR_3 (Rectangle){tela.width/3, tela.height/3 ,tela.width/3, tela.height/3}

#endif
