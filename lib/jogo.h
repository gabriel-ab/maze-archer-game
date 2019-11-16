#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

bool jogo_rodando = true;

int telaAtual = 0;

typedef enum{
    TELA_RESOLUCAO = -2,
    TELA_CONFIG = -1,
    TELA_MENU = 0,
    TELA_FASE1 = 1,
    TELA_FASE_3 = 3,
};

#endif