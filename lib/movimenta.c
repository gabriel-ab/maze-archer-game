#include "movimenta.h"

void movimentarV(Vector2 *coisa){
    if(IsKeyDown(KEY_W)) coisa->y -= 2;
    if(IsKeyDown(KEY_S)) coisa->y += 2;
    if(IsKeyDown(KEY_A)) coisa->x -= 2;
    if(IsKeyDown(KEY_D)) coisa->x += 2;
}
void movimentar(Personagem *fulano){
    
    if(fulano->inercia.y > -VELOCIDADE_MAX){
        if(IsKeyDown(KEY_W)) fulano->inercia.y += -ACELERACAO;
    }

    if(fulano->inercia.y < VELOCIDADE_MAX){
        if(IsKeyDown(KEY_S)) fulano->inercia.y += ACELERACAO;
    }

    if(fulano->inercia.x > -VELOCIDADE_MAX){
        if(IsKeyDown(KEY_A)) fulano->inercia.x += -ACELERACAO;
    }

    if(fulano->inercia.x < VELOCIDADE_MAX){
        if(IsKeyDown(KEY_D)) fulano->inercia.x += ACELERACAO;
    }
    
    updateHitBoxes(fulano);
    
    aplicaInercia(fulano);
    
    aplicaAtrito(fulano,TAXA_ATRITO);

}
//atualiza caixas de colisao
void updateHitBoxes(Personagem *fulano){
    fulano->linhaColisaoCima =                          //  X========
        (Rectangle){                                    //  |       |
            fulano->position.x - fulano->largura/2,     //  |   .   |
            fulano->position.y - fulano->altura/2 -1,   //  |       |
            fulano->largura, 1                          //  ---------
        };

    fulano->linhaColisaoBaixo =                         //  ---------
        (Rectangle){                                    //  |       |
            fulano->position.x - fulano->largura/2,     //  |   .   |
            fulano->position.y + fulano->altura/2,      //  |       |
            fulano->largura, 1                          //  X========
        };

    fulano->linhaColisaoEsquerda  =                     //  --------X
        (Rectangle){                                    //  |       H
            fulano->position.x -fulano->largura/2 -1,   //  |   .   H
            fulano->position.y -fulano->altura/2,       //  |       H
            1, fulano->altura                           //  --------H
        };

    fulano->linhaColisaoDireita =                       //  X--------
        (Rectangle){                                    //  H       |
            fulano->position.x + fulano->largura/2,     //  H   .   |
            fulano->position.y - fulano->altura/2,      //  H       |
            1, fulano->altura                           //  H--------
        };
}
//verifica se o personagem colidiu em alguma parede
void checkHitBoxes(Personagem *fulano,Rectangle **MAPA){

    int bytesMapa = sizeof(**MAPA);
    int bytesRectamgle = sizeof(Rectangle);
    int tamMapa = bytesMapa/bytesRectamgle;
    
    //VERIFICAÇÃO DE COLISAO SUPERIOR
    for(int i = 0; i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoCima, *MAPA[i]) )
        {
            if(fulano->inercia.y < 0)
            {
                fulano->inercia.y = 0;
                break;
            }
        }
    }
    //VERIFICAÇÃO DE COLISAO INFERIOR
    for(int i = 0; i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoBaixo, *MAPA[i]) )
        {
            if(fulano->inercia.y > 0)
            {
                fulano->inercia.y = 0;
                break;
            }
        }
    }
    //VERIFICAÇÃO DE COLISAO ESQUERDA
    for(int i = 0; i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoEsquerda, *MAPA[i]) )
        {
            if(fulano->inercia.x < 0)
            {
                fulano->inercia.x = 0;
                break;
            }
        }
    }
    //VERIFICAÇÃO DE COLISAO DIREITA
    for(int i = 0; i < tamMapa; i++)
    {
        if ( CheckCollisionRecs(fulano->linhaColisaoDireita, *MAPA[i]) )
        {
            if(fulano->inercia.x > 0)
            {
                fulano->inercia.x = 0;
                break;
            }
        }
    }
    
}
//aplica a inercia a posicao do personagem
void aplicaInercia(Personagem *fulano){
    fulano->position.x += fulano->inercia.x;
    fulano->position.y += fulano->inercia.y;
}

//Reduz a inercia do personagem conforme a taxa de atrito
void aplicaAtrito(Personagem *fulano, float taxa){

    if(fulano->inercia.x > 0.3) fulano->inercia.x -= taxa;
    else if(fulano->inercia.x < -0.3) fulano->inercia.x += taxa;
    else fulano->inercia.x = 0;

    if(fulano->inercia.y > 0.3) fulano->inercia.y -= taxa;
    else if(fulano->inercia.y < -0.3) fulano->inercia.y += taxa;
    else fulano->inercia.y = 0;
}