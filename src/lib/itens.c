#include "../include/itens.h"


void explosionCollision(Trap bomba, Personagem *fulano){
    bool hitted = true;
    int push = 0;
    if(CheckCollisionCircles(bomba.posicao, BOMB_RANGE1, fulano->posicao, 16))
    {
        fulano->vida -= BOM_DAMAGE1;
        push = 10;
    }
    else if(CheckCollisionCircles(bomba.posicao, BOMB_RANGE2, fulano->posicao, 16))
    {
        fulano->vida -= BOM_DAMAGE2;
        push = 8;
    }
    else if(CheckCollisionCircles(bomba.posicao, BOMB_RANGE3, fulano->posicao, 16))
    {
        fulano->vida -= BOM_DAMAGE3;
        push = 5;
    }
    else
    {
        hitted = false;
    }
    
    if(hitted){
        int deltaY = bomba.posicao.y - fulano->posicao.y;
        int deltaX = bomba.posicao.x - fulano->posicao.x;

        float angulo = atan2(deltaY, deltaX);
        fulano->acao.atual = INIMIGO_ATORDOADO;
        fulano->acao.duracao = 2;
        fulano->velocidade.y -= sin(angulo) * push;
        fulano->velocidade.x -= cos(angulo) * push;
    }
}
void animarBomba(Trap *bomba){
    if(bomba->status == TRAP_ON){
        animaSpriteLinha(&bomba->sprite);
        if(bomba->sprite.frameAtual == bomba->sprite.colunas -1)
        {
            bomba->status = TRAP_OFF;
            bomba->sprite.recorte = 
                (Rectangle){
                    bomba->sprite.frameAtual * bomba->sprite.textura.width/bomba->sprite.colunas , 
                    0, 
                    bomba->sprite.textura.width / bomba->sprite.colunas, 
                    bomba->sprite.textura.height / bomba->sprite.linhas
                };
        }
    }
}