#include "draw.h"
#include "tela.h"

//Função responsável por desenhar a personagem principal
void drawXala(Personagem* xala, int contador) {

    //Se Xala está invunerável ela começa a piscar
    if(xala->invulneravel) {
        if(contador%10 == 0) {
            DrawCircleV(xala->posicao,10,BLUE);
        } 
    } else {
        DrawCircleV(xala->posicao,10,BLUE);
    }
}



//Função responsável por desenhar a personagem principal
void drawFlecha(Projetil flecha[], int quantidade) {
    for (int i = 0; i < quantidade; i++)
    {
        DrawCircleV(flecha[i].posicao,5,GREEN);

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



//Função responsável por desenhar os inimigos da Fase
void drawInimigos(Personagem inimigos[], int quantidade) {
    for(int i = 0; i < quantidade; i++){
        
        if(inimigos[i].vida > 0) {
            DrawCircleV(inimigos[i].posicao, 10, (Color){150,150,255,120});
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

        for (int x = 0; x < PISO[i].width; x+=32)
        {
            for (int y = 0; y < PISO[i].height; y+=32)
            {
                DrawTextureEx(pisoTexture, (Vector2){ PISO[i].x + x, PISO[i].y + y }, 0, 1,WHITE);
            }
               
        }
         
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
