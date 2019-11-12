
#include <math.h>
#include "acao.h"

// A FAZER: PONTO DE ORIGEM PARA O TIRO NÃO CENTRALIZADO


void mira(Personagem fulano, Tiro *bala, Camera2D cam);
void atira(Tiro *bala);
void atualizaTiro(Tiro *bala);

void mira(Personagem fulano, Tiro *bala, Camera2D cam)
{
    bala->origem = fulano.position;
    int posMouseY = (GetMouseY() -cam.offset.y)/ cam.zoom;
    int posMouseX = (GetMouseX() -cam.offset.x)/ cam.zoom;
    
    int deltaY = posMouseY -fulano.position.y;
    int deltaX = posMouseX -fulano.position.x;

    bala->angulo = atan2(deltaY,deltaX)*RAD2DEG;
    
}
void atira(Tiro *bala)
{
    bala->velocidade.y = sin(bala->angulo*DEG2RAD)*VELOCIDADE_TIRO;
    bala->velocidade.x = cos(bala->angulo*DEG2RAD)*VELOCIDADE_TIRO;
}
void atualizaTiro(Tiro *bala)
{
    bala->origem.y += bala->velocidade.y;
    bala->origem.x += bala->velocidade.x;
}