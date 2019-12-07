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
    xala.vida = vida_maxima;
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
    inimigo.altura = 32;
    inimigo.largura = 32;
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
void inimigoAproximaV(Personagem *inimigo, Vector2 coisa)
{  
    int deltaY = coisa.y -inimigo->posicao.y;
    int deltaX = coisa.x -inimigo->posicao.x;

    float angulo = atan2(deltaY,deltaX);

    float distancia = sqrt(deltaY*deltaY + deltaX*deltaX);
    
    if( distancia < 14 )
    {
        inimigo->velocidade.y = sin(angulo)*VELOCIDADE_XALA*0.8;
        inimigo->velocidade.x = cos(angulo)*VELOCIDADE_XALA*0.8;
    }
}
//Se aproxima de alguem e ataca se estiver proximo
void inimigoAproxima(Personagem *inimigo, Personagem *fulano)
{  
    int deltaY = fulano->posicao.y -inimigo->posicao.y;
    int deltaX = fulano->posicao.x -inimigo->posicao.x;

    float angulo = atan2(deltaY,deltaX);

    float distancia = sqrt(deltaY*deltaY + deltaX*deltaX);

    if( distancia < 15 ) 
    {
        if(!fulano->invulneravel)
        {
            inimigoAtaca(inimigo, fulano);
        }
    }

    else if( distancia < 150 )
    {
        inimigo->velocidade.y = sin(angulo)*VELOCIDADE_INIMIGO;
        inimigo->velocidade.x = cos(angulo)*VELOCIDADE_INIMIGO;
    }
}

void inimigoFoge(Personagem *inimigo, Personagem *fulano)
{
    int deltaY = fulano->posicao.y -inimigo->posicao.y;
    int deltaX = fulano->posicao.x -inimigo->posicao.x;

    float angulo = atan2(deltaY,deltaX);

    float distancia = sqrt(deltaY*deltaY + deltaX*deltaX);
    
    if( distancia < 150 )
    {
        inimigo->velocidade.y = -sin(angulo)*VELOCIDADE_INIMIGO;
        inimigo->velocidade.x = -cos(angulo)*VELOCIDADE_INIMIGO;
    }
}

void inimigoAtaca(Personagem *inimigo, Personagem *fulano)
{
    int deltaY = fulano->posicao.y -inimigo->posicao.y;
    int deltaX = fulano->posicao.x -inimigo->posicao.x;

    float angulo = atan2(deltaY,deltaX);

    Vector2 pontoDeAtaque = {fulano->posicao.x + sin(angulo)*2, fulano->posicao.y + cos(angulo)*2};

    c = pontoDeAtaque; //Temporario , para desenhar no programa
    
    if(CheckCollisionCircles(pontoDeAtaque, 10, fulano->posicao, 16))
    {
        fulano->vida--;
        fulano->invulneravel = 1;
    }
    
}
// A FAZER
void inimigoStandby(Personagem *fulano){

}
