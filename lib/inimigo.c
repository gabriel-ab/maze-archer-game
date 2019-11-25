#include "inimigo.h"
#include "tela.h"

Inimigo inimigoContructor() {
    Inimigo inimigo;
    inimigo.position.x = tela.width/2;
    inimigo.position.y = tela.height/2;
    inimigo.altura = inimigo.sprite.height/8;
    inimigo.largura = inimigo.sprite.width/12;
    inimigo.linhaColisaoCima = (Rectangle){inimigo.position.x, inimigo.position.y -1, inimigo.largura, 1};
    inimigo.linhaColisaoBaixo = (Rectangle){inimigo.position.x, inimigo.position.y + inimigo.altura, inimigo.largura, 1};
    inimigo.linhaColisaoEsquerda  = (Rectangle){inimigo.position.x - 1, inimigo.position.y, 1, inimigo.altura};
    inimigo.linhaColisaoDireita = (Rectangle){inimigo.position.x + inimigo.largura, inimigo.position.y, 1, inimigo.altura};
    inimigo.vida = 5;
    return inimigo;
}
