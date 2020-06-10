#include "../include/projetil.h"
#include "../include/som.h"
#include <raymath.h> 

void mira(Personagem fulano, Projetil *bala, Camera2D cam)
{
    bala->posicao = fulano.posicao;
    Vector2 mousePos = {
        (GetMouseX() + cam.target.x - cam.offset.x),
        (GetMouseY() + cam.target.y - cam.offset.y)
    };

    bala->angulo = Vector2Angle(bala->posicao, mousePos); 
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
       if( CheckCollisionCircleRec(bala->posicao,2,MAPA[i]))
       {
           bala->velocidade = (Vector2){0,0};
           bala->ativa = false;
           return true;
       }
    }
    return false;
}

//Retorna o numero do inimigo
int colisaoProjetil_inimigo(Projetil *bala, Personagem *inimigo, int n_inimigos)
{
    for( int i = 0; i < n_inimigos; i++)
    {
        if(inimigo[i].vida > 0 && CheckCollisionCircles(inimigo[i].posicao, 5, bala->posicao, 10))
        {
            //Empurra o inimigo para tras
            inimigo[i].acao.atual = INIMIGO_ATORDOADO;
            inimigo[i].velocidade.x = bala->velocidade.x / 5;
            inimigo[i].velocidade.y = bala->velocidade.y / 5;
            inimigo[i].acao.contador = TEMPO;
            inimigo[i].acao.duracao = GetRandomValue(50,100) / 50; // Tempo entre 1 e 2 segundos de recuperação da flechada
            inimigo[i].vida--;
            bala->ativa = false;
            playFx(5);
            return i;
        }
    }
    return 0;
}