#include <math.h>
#include "acao.h"
#include "define.h"

// A FAZER: PONTO DE posicao PARA O Projetil NÃO CENTRALIZADO

void mira(Personagem fulano, Projetil *bala, Camera2D cam)
{
    bala->posicao = fulano.position;

    int posMouseX = (GetMouseX() -cam.offset.x);
    int posMouseY = (GetMouseY() -cam.offset.y);
    
    int deltaY = posMouseY -fulano.position.y;
    int deltaX = posMouseX -fulano.position.x;

    bala->angulo = atan2(deltaY,deltaX);
    
}
void atira(Personagem fulano ,Projetil *bala)
{
    bala->velocidade.y = sin(bala->angulo)*VELOCIDADE_Projetil;
    bala->velocidade.x = cos(bala->angulo)*VELOCIDADE_Projetil;
}
void atualizaProjetil(Projetil *bala)
{
    bala->posicao.y += bala->velocidade.y;
    bala->posicao.x += bala->velocidade.x;
}

//Reduz a velocidade fornecida conforme a taxa de atrito 
//Taxa positiva somente
void aplicarAtritoProjetil(Projetil *bala, float taxa)
{
    if(bala->velocidade.y > 1){
        bala->velocidade.y -= taxa*sin(bala->angulo);
    }
    else if(bala->velocidade.y < -1){
        bala->velocidade.y -= taxa*sin(bala->angulo);
    }
    else{
        bala->velocidade.y = 0;
    }

    if(bala->velocidade.x > 1){
        bala->velocidade.x -= taxa*cos(bala->angulo);
    }
    else if(bala->velocidade.x < -1){
        bala->velocidade.x -= taxa*cos(bala->angulo);
    }
    else{
        bala->velocidade.x = 0;
    }
}

int colisaoProjetil(Projetil *bala, Rectangle *MAPA)
{
    for( int i = 0; i < TAM_MAPA1; i++)
    {
       if( CheckCollisionCircleRec(bala->posicao,10,MAPA[i]))
       {
           bala->velocidade = (Vector2){0,0};
           return 1;
       }
    }
}