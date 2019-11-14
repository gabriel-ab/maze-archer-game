#include <math.h>
#include "acao.h"

// A FAZER: PONTO DE ORIGEM PARA O TIRO NÃO CENTRALIZADO

void mira(Personagem fulano, Tiro *bala, Camera2D cam)
{
    bala->origem = fulano.position;

    int posMouseX = (GetMouseX() -cam.offset.x);
    int posMouseY = (GetMouseY() -cam.offset.y);
    
    int deltaY = posMouseY -fulano.position.y;
    int deltaX = posMouseX -fulano.position.x;

    bala->angulo = atan2(deltaY,deltaX);
    
}
void atira(Tiro *bala)
{
    bala->velocidade.y = sin(bala->angulo)*VELOCIDADE_TIRO;
    bala->velocidade.x = cos(bala->angulo)*VELOCIDADE_TIRO;
}
void atualizaTiro(Tiro *bala)
{
    bala->origem.y += bala->velocidade.y;
    bala->origem.x += bala->velocidade.x;
}