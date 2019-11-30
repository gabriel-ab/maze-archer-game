#include "personagem.h"
#include "tela.h"
#include "movimenta.h"
#include "define.h"
#include <math.h>


Personagem personagemConstructor() {
    Personagem xala;
    //A FAZER Definir sprite para personagem principal
    //xala.sprite = LoadTexture("resources/DF_Actor.png");
    xala.invulneravel = false;
    xala.vida = 3;
    xala.velocidade = (Vector2){0,0};
    xala.posicao = (Vector2){0,0};
    xala.altura = 8;
    xala.largura = 12;
    xala.linhaColisaoCima = 
        (Rectangle){
            xala.posicao.x - xala.largura/2 +2, 
            xala.posicao.y - xala.altura/2 -1, 
            xala.largura -2, 1
        };

    xala.linhaColisaoBaixo = 
        (Rectangle){
            xala.posicao.x - xala.largura/2 +2,
            xala.posicao.y + xala.altura, 
            xala.largura -2, 1
        };

    xala.linhaColisaoEsquerda  = 
        (Rectangle){
            xala.posicao.x -xala.largura/2 -1, 
            xala.posicao.y -xala.altura/2 +2,
            1, xala.altura -2
        };

    xala.linhaColisaoDireita = 
        (Rectangle){ 
            xala.posicao.x + xala.largura/2, 
            xala.posicao.y - xala.altura/2 +2, 
            1, xala.altura -2
        };

    return xala;
}

Personagem inimigoContructor() {
    Personagem inimigo;
    inimigo.invulneravel = false;
    inimigo.vida = 3;
    inimigo.velocidade = (Vector2){0,0};
    inimigo.posicao = (Vector2){0,0};
    inimigo.altura = 8;
    inimigo.largura = 12;
    inimigo.linhaColisaoCima = 
        (Rectangle){
            inimigo.posicao.x - inimigo.largura/2 +2, 
            inimigo.posicao.y - inimigo.altura/2 -1, 
            inimigo.largura -2, 1
        };

    inimigo.linhaColisaoBaixo = 
        (Rectangle){
            inimigo.posicao.x - inimigo.largura/2 +2,
            inimigo.posicao.y + inimigo.altura, 
            inimigo.largura -2, 1
        };

    inimigo.linhaColisaoEsquerda  = 
        (Rectangle){
            inimigo.posicao.x -inimigo.largura/2 -1, 
            inimigo.posicao.y -inimigo.altura/2 +2,
            1, inimigo.altura -2
        };

    inimigo.linhaColisaoDireita = 
        (Rectangle){ 
            inimigo.posicao.x + inimigo.largura/2, 
            inimigo.posicao.y - inimigo.altura/2 +2, 
            1, inimigo.altura -2
        };
    return inimigo;
}

// Movimentação do inimigo para perseguir algo
void inimigoAproxima(Personagem *inimigo, Vector2 coisa)
{  
    int deltaY = coisa.y -inimigo->posicao.y;
    int deltaX = coisa.x -inimigo->posicao.x;

    float angulo = atan2(deltaY,deltaX);

    distancia = sqrt(deltaY*deltaY + deltaX*deltaX);

    if( sqrt(deltaY*deltaY + deltaX*deltaX) < 200 )
    {
        inimigo->velocidade.y = sin(angulo)*VEL_MAX_PERSONAGEM*0.6;
        inimigo->velocidade.x = cos(angulo)*VEL_MAX_PERSONAGEM*0.6;
    }
}

void inimigoFoge(Personagem *inimigo, Vector2 coisa)
{
    int deltaY = coisa.y -inimigo->posicao.y;
    int deltaX = coisa.x -inimigo->posicao.x;

    float angulo = atan2(deltaY,deltaX);
    
    if( sqrt(deltaY*deltaY + deltaX*deltaX) < 14 )
    {
        inimigo->velocidade.y = -sin(angulo)*VEL_MAX_PERSONAGEM;
        inimigo->velocidade.x = -cos(angulo)*VEL_MAX_PERSONAGEM;
    }
}

// A FAZER
void inimigoStandby(Personagem *fulano){

}
