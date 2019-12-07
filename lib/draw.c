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

//Função responsável por incluir as paredes da Fase 3
void drawParedes(Rectangle PAREDES[], int tamanho) {
    for(int i = 0; i < tamanho; i++){
                
        DrawRectangleRec(PAREDES[i],RED);
        
        DrawTexturePro(parede,
            (Rectangle){0,0,PAREDES[i].width,PAREDES[i].height},
            PAREDES[i],
            (Vector2){0,0},
            0,BROWN
        );
        
    }
}

//Função responsável por incluir os pisos da Fase 3
void drawPiso(Rectangle PISO[], int tamanho, Rectangle frameRec) {     
    for(int i = 0; i < tamanho; i++){

        for (int x = 0; x < PISO[i].width; x+=32)
        {
            for (int y = 0; y < PISO[i].height; y+=32)
            {
                DrawTextureRec(piso, frameRec, (Vector2) { PISO[i].x + x , PISO[i].y + y }, WHITE);
            }
               
        }
         
    }
}

//Função responsável por incluir as armadilhas da Fase 3
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec) {
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