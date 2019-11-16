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
    "RESOLUÇÃO",
    "MUTE: OFF",
    "BACK",
};
Rectangle botoesConfiguracao[3];
Rectangle* getBotoesConfiguracao();


//BOTÕES DE RESOLUÇÃO DE TELA
char *textButtonsResolucao[] = {
    "1920x1080",
    "1280x720",
    "800x600",
    "640x480",
    "BACK"
};
Rectangle botoesResolucao[5];
Rectangle* getBotoesResolucao();


//BOTÕES DA TELA DE CONFIGURAÇÃO
char *textButtonsPausa[] = {
    "CONTINUE",
    "RESTART",
    "SETTINGS",
    "QUIT",
};
Rectangle botoesPausa[4];
Rectangle* getBotoesPausa();


void atualizarPosicaoBotoes();


#endif