#include <raylib.h>
#include "personagem.h"
#include "tela.h"


Personagem personagemConstructor() {
    Personagem xala;
    //A FAZER Definir sprite para personagem principal
    //xala.sprite = LoadTexture("resources/DF_Actor.png");
    xala.invulneravel = false;
    xala.vida = 3;
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
