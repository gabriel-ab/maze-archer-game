
#include "personagem.h"
#include "constants.h"

Personagem personagemConstructor() {
    Personagem knight;
    //TODO Definir sprite para personagem principal
    //knight.sprite = LoadTexture("resources/DF_Actor.png");
    knight.positionX = SCREEN_WIDTH/2;
    knight.positionY = SCREEN_HEIGHT/2;
    knight.altura = knight.sprite.height/8;
    knight.largura = knight.sprite.width/12;
    knight.linhaColisaoCima = (Rectangle){knight.positionX, knight.positionY -1, knight.largura, 1};
    knight.linhaColisaoBaixo = (Rectangle){knight.positionX, knight.positionY + knight.altura, knight.largura, 1};
    knight.linhaColisaoEsquerda  = (Rectangle){knight.positionX - 1, knight.positionY, 1, knight.altura};
    knight.linhaColisaoDireita = (Rectangle){knight.positionX + knight.largura, knight.positionY, 1, knight.altura};
    return knight;
}

Personagem inimigoContructor() {
    Personagem inimigo;
    inimigo.positionX = SCREEN_WIDTH/2;
    inimigo.positionY = SCREEN_HEIGHT/2;
    inimigo.altura = inimigo.sprite.height/8;
    inimigo.largura = inimigo.sprite.width/12;
    inimigo.linhaColisaoCima = (Rectangle){inimigo.positionX, inimigo.positionY -1, inimigo.largura, 1};
    inimigo.linhaColisaoBaixo = (Rectangle){inimigo.positionX, inimigo.positionY + inimigo.altura, inimigo.largura, 1};
    inimigo.linhaColisaoEsquerda  = (Rectangle){inimigo.positionX - 1, inimigo.positionY, 1, inimigo.altura};
    inimigo.linhaColisaoDireita = (Rectangle){inimigo.positionX + inimigo.largura, inimigo.positionY, 1, inimigo.altura};
    return inimigo;
}