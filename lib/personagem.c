#include "personagem.h"
#include "tela.h"
#include "movimenta.h"
#include "define.h"
#include <math.h>

Personagem personagemConstructor()
{
    Personagem xala;
    //A FAZER Definir sprite para personagem principal
    //xala.sprite = LoadTexture("resources/DF_Actor.png");
    xala.invulneravel = false;
    xala.vida = vida_maxima_xala;
    xala.quantidadeFlechas = quantidade_maxima_flechas;
    xala.velocidade = (Vector2){0,0};
    xala.posicao = (Vector2){0,0};
    xala.altura = 8;
    xala.largura = 12;
    xala.linhaColisaoCima =
        (Rectangle){
            xala.posicao.x - xala.largura / 2 + 2,
            xala.posicao.y - xala.altura / 2 - 1,
            xala.largura - 2, 1};

    xala.linhaColisaoBaixo =
        (Rectangle){
            xala.posicao.x - xala.largura / 2 + 2,
            xala.posicao.y + xala.altura,
            xala.largura - 2, 1};

    xala.linhaColisaoEsquerda =
        (Rectangle){
            xala.posicao.x - xala.largura / 2 - 1,
            xala.posicao.y - xala.altura / 2 + 2,
            1, xala.altura - 2};

    xala.linhaColisaoDireita =
        (Rectangle){
            xala.posicao.x + xala.largura / 2,
            xala.posicao.y - xala.altura / 2 + 2,
            1, xala.altura - 2};

    return xala;
}

Personagem inimigoContructor()
{
    Personagem inimigo;
    inimigo.acao.contador = 0;
    inimigo.acao.duracao = 2;
    inimigo.acao.atual = INIMIGO_DE_BOA;
    inimigo.invulneravel = false;
    inimigo.vida = 3;
    inimigo.velocidade = (Vector2){0, 0};
    inimigo.posicao = (Vector2){0, 0};
    inimigo.altura = 32;
    inimigo.largura = 32;
    inimigo.linhaColisaoCima =
        (Rectangle){
            inimigo.posicao.x - inimigo.largura / 2 + 2,
            inimigo.posicao.y - inimigo.altura / 2 - 1,
            inimigo.largura - 2, 1};

    inimigo.linhaColisaoBaixo =
        (Rectangle){
            inimigo.posicao.x - inimigo.largura / 2 + 2,
            inimigo.posicao.y + inimigo.altura,
            inimigo.largura - 2, 1};

    inimigo.linhaColisaoEsquerda =
        (Rectangle){
            inimigo.posicao.x - inimigo.largura / 2 - 1,
            inimigo.posicao.y - inimigo.altura / 2 + 2,
            1, inimigo.altura - 2};

    inimigo.linhaColisaoDireita =
        (Rectangle){
            inimigo.posicao.x + inimigo.largura / 2,
            inimigo.posicao.y - inimigo.altura / 2 + 2,
            1, inimigo.altura - 2};
    return inimigo;
}
//Inimigo está contra quem?
void logicaInimigo(Personagem *inimigo, Personagem *fulano)
{
    int deltaY = fulano->posicao.y - inimigo->posicao.y;
    int deltaX = fulano->posicao.x - inimigo->posicao.x;

    float angulo = atan2(deltaY, deltaX);
    float distancia = sqrt(deltaY * deltaY + deltaX * deltaX);

    if(inimigo->vida <= 2) inimigo->acao.atual = INIMIGO_AI_PAI_PARA;
    else if(distancia >= 300) inimigo->acao.atual = INIMIGO_DE_BOA;
    else inimigo->acao.atual = INIMIGO_PISTOLA;

    switch (inimigo->acao.atual)
    {
        //==========================================================================================
        case INIMIGO_DE_BOA:

            if(distancia < 400)
            {
                inimigo->acao.atual = INIMIGO_PISTOLA;
            }

            if (GetTime() - inimigo->acao.contador > inimigo->acao.duracao)
            {
                inimigo->acao.contador = GetTime();
                inimigo->acao.duracao = GetRandomValue(5,10)/10;
                angulo = GetRandomValue(0,360);
                inimigo->acao.direcao.y = sin(angulo) * VELOCIDADE_INIMIGO;
                inimigo->acao.direcao.x = cos(angulo) * VELOCIDADE_INIMIGO;
            }
            inimigo->velocidade = inimigo->acao.direcao;
            break;
        //==========================================================================================
        case INIMIGO_PISTOLA:
        
            if (distancia < 64)
            {
                if (!fulano->invulneravel)
                {
                    Vector2 pontoDeAtaque = {inimigo->posicao.x + cos(angulo)*32, inimigo->posicao.y + sin(angulo)*32};

                    if (CheckCollisionCircles(pontoDeAtaque, 5, fulano->posicao, 16))
                    {
                        fulano->vida--;
                        fulano->invulneravel = 1;
                    }
                }
            }
            
            inimigo->velocidade.y = sin(angulo) * VELOCIDADE_INIMIGO;
            inimigo->velocidade.x = cos(angulo) * VELOCIDADE_INIMIGO;
            
            break;
        //==========================================================================================
        case INIMIGO_AI_PAI_PARA:   
            if (distancia < 150)
            {
                inimigo->velocidade.y = -sin(angulo) * VELOCIDADE_INIMIGO;
                inimigo->velocidade.x = -cos(angulo) * VELOCIDADE_INIMIGO;
            }
            break;
    }
}

// Movimentação do inimigo para seguir algo
void inimigoSegue(Personagem *inimigo, Vector2 coisa)
{
    int deltaY = coisa.y - inimigo->posicao.y;
    int deltaX = coisa.x - inimigo->posicao.x;

    float angulo = atan2(deltaY, deltaX);

    float distancia = sqrt(deltaY * deltaY + deltaX * deltaX);

    if (distancia < 14)
    {
        inimigo->velocidade.y = sin(angulo) * VELOCIDADE_XALA * 0.8;
        inimigo->velocidade.x = cos(angulo) * VELOCIDADE_XALA * 0.8;
    }
}
