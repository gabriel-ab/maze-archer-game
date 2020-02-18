#include "draw.h"
#include "tela.h"
#include "textura.h"

//Função responsável por desenhar a personagem principal
void drawXala(Personagem* xala) {
    static double contador = 0;
    //Se Xala está invunerável ela começa a piscar
    if(xala->invulneravel) {
        if(TEMPO -contador > 0.10){
            contador = TEMPO;
        }else{
            drawSprite(xala->sprite,xala->posicao, (Vector2){0,0},0,1,RED);
        }
    } else {
        drawSprite(xala->sprite,xala->posicao, (Vector2){0,0},0,1,WHITE);
    }
}



//Função responsável por desenhar a personagem principal
void drawFlecha(Projetil flecha[], Personagem fulano) {
    for (int i = 0; i < fulano.quantidadeFlechas; i++)
    {
        if(i >= projetil_atual){
            if(i != projetil_atual || mirando ){
            DrawTexturePro(flecha[i].textura,
                (Rectangle){0,28,64,8},
                (Rectangle){
                    flecha[i].posicao.x,
                    flecha[i].posicao.y,
                    64, 6},
                (Vector2){48,2},
                flecha[i].angulo,WHITE);
            }
        }
    }
}



//Função responsável por desenhar os inimigos da Fase
void drawInimigos(Personagem inimigos[], int quantidade) {
    for(int i = 0; i < quantidade; i++){
        
        if(inimigos[i].vida > 0) {
            drawSprite(inimigos[i].sprite, inimigos[i].posicao, (Vector2){0,0}, 0, 1, WHITE);
            // DrawCircleV(inimigos[i].posicao, 10, (Color){150,150,255,255});
        }
        
    }
}



//Função responsável por desenhar as paredes da Fase
void drawParedes(Rectangle PAREDES[], int tamanho) {
    for(int i = 0; i < tamanho; i++){
                
        DrawTexturePro(paredeTexture,
            (Rectangle){0,0,PAREDES[i].width,PAREDES[i].height},
            PAREDES[i],
            (Vector2){0,0},
            0,WHITE
        );
        
    }
}



//Função responsável por desenhar os pisos da Fase
void drawPiso(Rectangle PISO[], int tamanho) {     
    for(int i = 0; i < tamanho; i++){

        DrawTexturePro(pisoTexture,
            (Rectangle){0,0,PISO[i].width,PISO[i].height},
            PISO[i],
            (Vector2){0,0},
            0,WHITE
        );
         
    }
}



//Função responsável por desenhar as armadilhas da Fase
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho) {
    for(int i = 0; i < tamanho; i++){

        for (int x = 0; x < ARMADILHAS[i].width; x+=32)
        {
            for (int y = 0; y < ARMADILHAS[i].height; y+=32)
            {
                DrawTextureEx(armadilhaTexture, (Vector2) { ARMADILHAS[i].x + x , ARMADILHAS[i].y + y }, 0, 1,WHITE);
            }
               
        }
         
    }
}



//Função responsável por desenhar as armadilhas da Fase com animação
void drawArmadilhasRec(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec) {
    for(int i = 0; i < tamanho; i++){

        for (int x = 0; x < ARMADILHAS[i].width; x+=32)
        {
            for (int y = 0; y < ARMADILHAS[i].height; y+=32)
            {
                DrawTextureRec(armadilhaTexture, frameRec, (Vector2) { ARMADILHAS[i].x + x , ARMADILHAS[i].y + y }, WHITE);
            }
               
        }
         
    }
}

void drawSprite(Sprite sprite, Vector2 posicao, Vector2 origem, float rotacao, float escala, Color cor){
    // DrawTexturePro(sprite.textura, sprite.recorte, (Rectangle){posicao.x, posicao.y, sprite.recorte.width, sprite.recorte.width},origem,rotacao,cor);
    DrawTexturePro(
        sprite.textura, 
        sprite.recorte, 
        (Rectangle){
            posicao.x, 
            posicao.y, 
            escala*sprite.recorte.width, 
            escala*sprite.recorte.width
        },
        (Vector2){
            origem.x +sprite.recorte.width/2 ,
            origem.x +sprite.recorte.height/2
        },
        rotacao,
        cor
    );
}
