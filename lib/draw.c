#include "draw.h"
#include "tela.h"

void drawXala(Personagem* xala, int contador) {
    if(xala->invulneravel) {
        if(contador%10 == 0) {
            DrawCircleV(xala->posicao,10,BLUE);
        } 
    } else {
        DrawCircleV(xala->posicao,10,BLUE);
    }
}

//Função responsável por desenhar as paredes da Fase
void drawParedes(Rectangle PAREDES[], int tamanho) {
    for(int i = 0; i < tamanho; i++){
                
        DrawTexturePro(parede,
            (Rectangle){0,0,PAREDES[i].width,PAREDES[i].height},
            PAREDES[i],
            (Vector2){0,0},
            0,BROWN
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
                DrawTextureEx(piso, (Vector2){ PISO[i].x + x, PISO[i].y + y }, 0, 1,WHITE);
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
                DrawTextureEx(armadilha, (Vector2) { ARMADILHAS[i].x + x , ARMADILHAS[i].y + y }, 0, 1,WHITE);
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
                DrawTextureRec(armadilha, frameRec, (Vector2) { ARMADILHAS[i].x + x , ARMADILHAS[i].y + y }, WHITE);
            }
               
        }
         
    }
}
