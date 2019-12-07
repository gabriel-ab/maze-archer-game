#ifndef BOTOES_H_INCLUDED
#define BOTOES_H_INCLUDED

#include <raylib.h>

//BOTÕES DA TELA DE MENU
const char *textButtonsMenu[] = {
    "START",
    "LOAD",
    "SETTINGS",
    "QUIT"
};
Rectangle botoesMenu[4];
Rectangle* getBotoesMenu();


//BOTÕES DA TELA DE CONFIGURAÇÃO
char *textButtonsConfiguracao[] = {
    "FULLSCREEN: ON",
    "MUTE: OFF",
    "BACK",
};
Rectangle botoesConfiguracao[3];
Rectangle* getBotoesConfiguracao();


//BOTÕES DA TELA DE PAUSA
char *textButtonsPausa[] = {
    "CONTINUE",
    "RESTART",
    "SETTINGS",
    "QUIT",
};
Rectangle botoesPausa[4];
Rectangle* getBotoesPausa();


//BOTÕES DA TELA DE FRACASSO
char *textButtonsFracasso[] = {
    "RESTART",
    "QUIT",
};
Rectangle botoesFracasso[2];
Rectangle* getBotoesFracasso();


void atualizarPosicaoBotoes();


#endif