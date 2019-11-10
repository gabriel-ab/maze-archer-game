
#include "personagem.h"

Personagem personagemConstructor() {
    Personagem knight;
    //TODO Definir sprite para personagem principal
    //knight.sprite = LoadTexture("resources/DF_Actor.png");
    knight.inercia = (Vector2){0,0};
    knight.position = (Vector2){tela.width/2, tela.height/2};
    knight.altura = knight.sprite.height/8;
    knight.largura = knight.sprite.width/12;
    knight.linhaColisaoCima = 
        (Rectangle){
            knight.position.x - knight.largura/2, 
            knight.position.y - knight.altura/2 -1, 
            knight.largura, 1
        };

    knight.linhaColisaoBaixo = 
        (Rectangle){
            knight.position.x - knight.largura/2,
            knight.position.y + knight.altura, 
            knight.largura, 1
        };

    knight.linhaColisaoEsquerda  = 
        (Rectangle){
            knight.position.x -knight.largura/2 -1, 
            knight.position.y -knight.altura/2,
            1, knight.altura
        };

    knight.linhaColisaoDireita = 
        (Rectangle){ 
            knight.position.x + knight.largura/2, 
            knight.position.y - knight.altura/2, 
            1, knight.altura
        };

    return knight;
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
