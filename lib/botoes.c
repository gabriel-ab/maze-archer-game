#include "botoes.h"
#include "tela.h"

Rectangle* getBotoesMenu() {
    for (int i = 0; i < 4; i++)
    {
        botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    return botoesMenu;
}

Rectangle* getBotoesConfiguracao() {
    for (int i = 0; i < 3; i++)
    {
        botoesConfiguracao[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    return botoesConfiguracao;
}


Rectangle* getBotoesPausa() {
    for (int i = 0; i < 4; i++)
    {
        botoesPausa[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    return botoesPausa;
}

Rectangle* getBotoesFracasso() {
    for (int i = 0; i < 2; i++)
    {
        botoesFracasso[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/1.4, 200, 50};
    }
    return botoesFracasso;
}


void atualizarPosicaoBotoes() {
    getBotoesMenu();
    getBotoesConfiguracao();
    getBotoesPausa();
    getBotoesFracasso();
}