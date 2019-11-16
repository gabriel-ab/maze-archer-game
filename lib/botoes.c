#include "botoes.h"
#include "tela.h"

Rectangle* getBotoesMenu() {
    for (int i = 0; i < 4; i++)
    {
        botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    return &botoesMenu;
}

Rectangle* getBotoesConfiguracao() {
    for (int i = 0; i < 3; i++)
    {
        botoesConfiguracao[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    return &botoesConfiguracao;
}

Rectangle* getBotoesResolucao() {
    for (int i = 0; i < 4; i++)
    {
        botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
    }

    botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};
    return &botoesResolucao;
}

Rectangle* getBotoesPausa() {
    for (int i = 0; i < 4; i++)
    {
        botoesPausa[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    return &botoesPausa;
}


void atualizarPosicaoBotoes() {
    getBotoesMenu();
    getBotoesConfiguracao();
    getBotoesResolucao();
    getBotoesPausa();
}