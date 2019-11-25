#include "movimenta.h"
#include "define.h"
#include "projetil.h"

void movimentarV(Vector2 *coisa){
    if(IsKeyDown(KEY_W)) coisa->y -= 2;
    if(IsKeyDown(KEY_S)) coisa->y += 2;
    if(IsKeyDown(KEY_A)) coisa->x -= 2;
    if(IsKeyDown(KEY_D)) coisa->x += 2;
}

//Faz a movimentação do personagem com inercia e atrito, verificando colisão com o mapa fornecido
void movimentar(Personagem *fulano){

    aplicarInercia(fulano);
    atualizarLinhasColisao(fulano);
    
    if(fulano->velocidade.y > -VEL_MAX_PERSONAGEM)
    {
        if(IsKeyDown(KEY_W)) fulano->velocidade.y += -ACELERACAO;
    }

    if(fulano->velocidade.y < VEL_MAX_PERSONAGEM)
    {
        if(IsKeyDown(KEY_S)) fulano->velocidade.y += ACELERACAO;
    }

    if(fulano->velocidade.x > -VEL_MAX_PERSONAGEM)
    {
        if(IsKeyDown(KEY_A)) fulano->velocidade.x += -ACELERACAO;
    }

    if(fulano->velocidade.x < VEL_MAX_PERSONAGEM)
    {
        if(IsKeyDown(KEY_D)) fulano->velocidade.x += ACELERACAO;
    }

    aplicarAtrito(fulano,TAXA_ATRITO);

}
//atualiza caixas de colisao
void atualizarLinhasColisao(Personagem *fulano){
    fulano->linhaColisaoCima =                          //  X========
        (Rectangle){                                    //  |       |
            fulano->posicao.x - fulano->largura/2 +2,   //  |   .   |
            fulano->posicao.y - fulano->altura/2 -1,    //  |       |
            fulano->largura -4, 1                       //  ---------
        };

    fulano->linhaColisaoBaixo =                         //  ---------
        (Rectangle){                                    //  |       |
            fulano->posicao.x - fulano->largura/2 +2,   //  |   .   |
            fulano->posicao.y + fulano->altura/2,       //  |       |
            fulano->largura -4, 1                       //  X========
        };

    fulano->linhaColisaoEsquerda  =                     //  --------X
        (Rectangle){                                    //  |       H
            fulano->posicao.x -fulano->largura/2 -1,    //  |   .   H
            fulano->posicao.y -fulano->altura/2 +2,     //  |       H
            1, fulano->altura -4                        //  --------H
        };

    fulano->linhaColisaoDireita =                       //  X--------
        (Rectangle){                                    //  H       |
            fulano->posicao.x + fulano->largura/2,      //  H   .   |
            fulano->posicao.y - fulano->altura/2 +2,    //  H       |
            1, fulano->altura -4                        //  H--------
        };
}

//aplica a velocidade a posicao do personagem
void aplicarInercia(Personagem *fulano)
{
    fulano->posicao.x += fulano->velocidade.x;
    fulano->posicao.y += fulano->velocidade.y;
}

//aplica a velocidade a posicao de Qualquer objeto
void aplicarInerciaV(Vector2 *posicao, Vector2 velocidade)
{
    posicao->x += velocidade.x;
    posicao->y += velocidade.y;
}

//Reduz a velocidade do personagem conforme a taxa de atrito
void aplicarAtrito(Personagem *fulano, float taxa)
{
    if(fulano->velocidade.x > 0.1) fulano->velocidade.x -= taxa;
    else if(fulano->velocidade.x < -0.1) fulano->velocidade.x += taxa;
    else fulano->velocidade.x = 0;

    if(fulano->velocidade.y > 0.1) fulano->velocidade.y -= taxa;
    else if(fulano->velocidade.y < -0.1) fulano->velocidade.y += taxa;
    else fulano->velocidade.y = 0;
}

void atualizarPersonagem(Personagem *inimigo)
{
    aplicarInercia(inimigo);
    atualizarLinhasColisao(inimigo);
    aplicarAtrito(inimigo,TAXA_ATRITO);
}

//Verifica as Colisões laterais
//COM retorno -> vetor com 4 elementos p/ ser enviadas as info. de colisao.
//SEM retorno -> 0
void colisaoPersonagem(Personagem *fulano, Rectangle *MAPA, int tamMapa, int *retorno)
{
    //variaveis de retorno
    int cima = 0,baixo = 0,esq = 0,dir = 0;

    //COLISAO CIMA
    for(int i = 0;i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoCima, MAPA[i]) )
        {
            if(fulano->velocidade.y < 0)
            {
                fulano->velocidade.y = 0;
            }
            cima = 1;
            break;
        }
    }

    //COLISAO BAIXO
    for(int i = 0;i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoBaixo, MAPA[i]) )
        {
            if(fulano->velocidade.y > 0)
            {
                fulano->velocidade.y = 0;
            }
            baixo = 1;
            break;
        }
    }


    //COLISAO ESQUERDA
    for(int i = 0;i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoEsquerda, MAPA[i]) )
        {
            if(fulano->velocidade.x < 0)
            {
                fulano->velocidade.x = 0;
            }
            esq = 1;
            break;
        }
    }

    //COLISAO DIREITA
    for(int i = 0;i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoDireita, MAPA[i]) )
        {
            if(fulano->velocidade.x > 0)
            {
                fulano->velocidade.x = 0;
            }
            dir = 1;
            break;
        }
    }
    if(retorno != 0){
        retorno[0] = cima;
        retorno[1] = baixo;
        retorno[2] = esq;
        retorno[3] = dir;
    }
}