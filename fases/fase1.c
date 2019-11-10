#define TAM_MAPA 4

#include <raylib.h>
Color colideCima = GREEN;
Color colideBaixo = GREEN;
Color colideEsq = GREEN;
Color colideDir = GREEN;

#include "../lib/tela.h"
#include "../lib/personagem.c"
#include "../lib/movimenta.c"


int main(){
    fase1();
}

void fase1()
{
    InitWindow(800,600,"JOGO"); //temporario
    Rectangle MAPA[] = {
        -278, -166, 18, 332,
        -264, -164, 481, 13,
        -261, 146, 466, 14,
        204, -156, 19, 256
    };

    Personagem xala;
    xala = personagemConstructor();
    xala.altura = 20;
    xala.largura = 20;

    Camera2D cam;
    cam.zoom = 3;
    cam.rotation = 0;
    cam.target = xala.position;
    cam.offset = (Vector2){GetScreenWidth()/2 , GetScreenHeight()/2};
    
    while(!WindowShouldClose()){

        movimentar(&xala, MAPA);
        
        if(IsKeyPressed(KEY_F)) telaCheia();
        
        cam.target = xala.position;
        cam.offset.x = tela.width/2  -cam.target.x;
        cam.offset.y = tela.height/2 -cam.target.y;
        

        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode2D(cam);

                for(int i = 0; i < TAM_MAPA; i++){
                    DrawRectangleRec(MAPA[i],BLACK);
                }
                DrawCircleV(xala.position,10,BLUE);
                DrawRectangleRec(xala.linhaColisaoCima,colideCima);
                DrawRectangleRec(xala.linhaColisaoBaixo,colideBaixo);
                DrawRectangleRec(xala.linhaColisaoEsquerda,colideEsq);
                DrawRectangleRec(xala.linhaColisaoDireita,colideDir);
                
                
            EndMode2D();

            DrawText(FormatText("%.2f %.2f",cam.target.x, cam.target.y),10,10,20,YELLOW);
            DrawText(FormatText("%.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,40,20,YELLOW);
            DrawText(FormatText("%lu",sizeof(MAPA)),10,70,20,YELLOW);

        EndDrawing();
    }
    CloseWindow(); //temporario
}
