#include <raylib.h>
#include "tela.h"
#include "textura.h"

Sprite spriteConstructor(const char *endereco, int largura_frame, int altura_frame, int fps){
    Sprite sprite;
    sprite.textura = LoadTexture(endereco);
    sprite.fps = fps;

    sprite.colunas = sprite.textura.width/altura_frame;
    sprite.linhas = sprite.textura.height/largura_frame;
    sprite.frameAtual = 0;
    sprite.recorte = (Rectangle){ 0,  0,  largura_frame,  altura_frame};

    return sprite;
}
//anima continuamente um sprite linhas
void animaSpriteLinha(Sprite *sprite){
    if(!sprite->fps) sprite->fps = 1;
    
    if(GetTime() - sprite->timer > 1/sprite->fps){
        sprite->timer = GetTime();
        sprite->frameAtual++;
        sprite->recorte = (Rectangle){
            sprite->frameAtual * sprite->textura.width/sprite->colunas , 
            0, 
            sprite->textura.width / sprite->colunas, 
            sprite->textura.height / sprite->linhas
        };
    }
    if(sprite->frameAtual >= sprite->colunas) sprite->frameAtual = 0;
}


