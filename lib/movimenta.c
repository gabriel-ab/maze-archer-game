#include "movimenta.h"

void movimentarV(Vector2 *coisa){
    if(IsKeyDown(KEY_W)) coisa->y -= 2;
    if(IsKeyDown(KEY_S)) coisa->y += 2;
    if(IsKeyDown(KEY_A)) coisa->x -= 2;
    if(IsKeyDown(KEY_D)) coisa->x += 2;
}
void movimentar(Personagem *fulano){
    
    if(IsKeyDown(KEY_W)) fulano->inercia.y = -VELOCIDADE;
    if(IsKeyDown(KEY_S)) fulano->inercia.y = VELOCIDADE;
    if(IsKeyDown(KEY_A)) fulano->inercia.x = -VELOCIDADE;
    if(IsKeyDown(KEY_D)) fulano->inercia.x = VELOCIDADE;
    
    updateHitBoxes(fulano);
    
    aplicaInercia(fulano);
    
    aplicaAtrito(fulano,0.01);

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
            fulano->position.y + fulano->altura,        //  |       |
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