#include <math.h>
#include "projetil.h"
#include "define.h"

void mira(Personagem fulano, Projetil *bala, Camera2D cam)
{
    bala->posicao = fulano.posicao;

    int posMouseX = (GetMouseX() -cam.offset.x);
    int posMouseY = (GetMouseY() -cam.offset.y);
    
    int deltaY = posMouseY -fulano.posicao.y;
    int deltaX = posMouseX -fulano.posicao.x;

    bala->angulo = atan2(deltaY,deltaX)*RAD2DEG;
    
}
void atira(Personagem fulano, Projetil *bala)
{
    bala->velocidade.y = sin(bala->angulo*DEG2RAD)*VELOCIDADE_Projetil;
    bala->velocidade.x = cos(bala->angulo*DEG2RAD)*VELOCIDADE_Projetil;
}

//Reduz a velocidade fornecida conforme a taxa de atrito 
//Taxa positiva somente
void aplicarAtritoProjetil(Projetil *bala, float taxa)
{
    if(bala->velocidade.y > 0.1 || bala->velocidade.y < -0.1){
        bala->velocidade.y -= sin(bala->angulo*DEG2RAD)*taxa;
    }
    else{
        bala->velocidade.y = 0;
    }

    if(bala->velocidade.x > 0.1 || bala->velocidade.x < -0.1){
        bala->velocidade.x -= cos(bala->angulo*DEG2RAD)*taxa;
    }
    else{
        bala->velocidade.x = 0;
    }
}

int colisaoProjetil_mapa(Projetil *bala, Rectangle *MAPA, int tamMapa)
{
    for( int i = 0; i < tamMapa; i++)
    {
       if( CheckCollisionCircleRec(bala->posicao,10,MAPA[i]))
       {
           bala->velocidade = (Vector2){0,0};
           bala->ativa = false;
           return 1;
       }
    }
    return 0;
}

//Retorna o numero do inimigo
int colisaoProjetil_inimigo(Projetil *bala, Personagem *inimigo, int n_inimigos)
{
    for( int i = 0; i < n_inimigos; i++)
    {
        if( CheckCollisionCircles(inimigo[i].posicao, 5, bala->posicao, 10))
        {
            bala->velocidade = inimigo->velocidade;
            inimigo[i].vida--;
            bala->ativa = false;
            return i;
        }
    }
    return 0;
}
