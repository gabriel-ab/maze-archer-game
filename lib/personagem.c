#include <raylib.h>
#include "personagem.h"
#include "tela.h"


Personagem personagemConstructor() {
    Personagem xala;
    //TODO Definir sprite para personagem principal
    //xala.sprite = LoadTexture("resources/DF_Actor.png");
    xala.velocidade = (Vector2){0,0};
    xala.position = (Vector2){0,0};
    xala.altura = 8;
    xala.largura = 12;
    xala.linhaColisaoCima = 
        (Rectangle){
            xala.position.x - xala.largura/2 +2, 
            xala.position.y - xala.altura/2 -1, 
            xala.largura -2, 1
        };

    xala.linhaColisaoBaixo = 
        (Rectangle){
            xala.position.x - xala.largura/2 +2,
            xala.position.y + xala.altura, 
            xala.largura -2, 1
        };

    xala.linhaColisaoEsquerda  = 
        (Rectangle){
            xala.position.x -xala.largura/2 -1, 
            xala.position.y -xala.altura/2 +2,
            1, xala.altura -2
        };

    xala.linhaColisaoDireita = 
        (Rectangle){ 
            xala.position.x + xala.largura/2, 
            xala.position.y - xala.altura/2 +2, 
            1, xala.altura -2
        };

    return xala;
}

Personagem inimigoContructor() {
    Personagem inimigo;
    inimigo.position.x = tela.width/2;
    inimigo.position.y = tela.height/2;
    inimigo.altura = inimigo.sprite.height/8;
    inimigo.largura = inimigo.sprite.width/12;
    inimigo.linhaColisaoCima = (Rectangle){inimigo.position.x, inimigo.position.y -1, inimigo.largura, 1};
    inimigo.linhaColisaoBaixo = (Rectangle){inimigo.position.x, inimigo.position.y + inimigo.altura, inimigo.largura, 1};
    inimigo.linhaColisaoEsquerda  = (Rectangle){inimigo.position.x - 1, inimigo.position.y, 1, inimigo.altura};
    inimigo.linhaColisaoDireita = (Rectangle){inimigo.position.x + inimigo.largura, inimigo.position.y, 1, inimigo.altura};
    return inimigo;
}
