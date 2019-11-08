#include <raylib.h>
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
        -103, -74, 269, 241,
        -16, 164, 98, 189,
        80, 232, 446, 122,
        521, -181, 96, 956,
        615, -178, 430, 52,
        697, -117, 170, 91,
        878, -116, 171, 88,
        622, -118, 68, 90,
        622, -19, 99, 183,
        623, 169, 98, 156,
        615, 53, 8, 42,
        616, 223, 9, 43,
        614, -95, 11, 36,
        708, -129, 42, 13,
        891, -129, 46, 13,
        616, 537, 124, 43,
        589, 772, 78, 72,
        665, 809, 179, 61,
        733, 486, 206, 82,
        902, 557, 210, 112,
        841, 812, 509, 41,
        1076, 667, 38, 146,
        1010, -32, 32, 141,
        875, 104, 318, 122,
        1009, 224, 40, 182,
        1048, 363, 229, 42,
        1237, 402, 40, 225,
        1110, 588, 126, 38,
    };
    Personagem xala;
    xala = personagemConstructor();

    Camera2D cam;
    cam.zoom = 3;
    cam.target = xala.position;
    cam.offset = (Vector2){GetScreenWidth()/2 , GetScreenHeight()/2};
    
    while(!WindowShouldClose()){

        movimentar(&xala);
        if(IsKeyPressed(KEY_F)) telaCheia();
        
        cam.target = xala.position;
        cam.offset.x = tela.width/2  -cam.target.x;
        cam.offset.y = tela.height/2 -cam.target.y;
        

        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode2D(cam);

                for(int i = 0; i < 28; i++){
                    DrawRectangleRec(MAPA[i],BLACK);
                }
                DrawCircleV(xala.position,10,BLUE);
                DrawRectangleRec(xala.linhaColisaoBaixo,BLACK);
                DrawRectangleRec(xala.linhaColisaoCima,BLACK);
                DrawRectangleRec(xala.linhaColisaoDireita,BLACK);
                DrawRectangleRec(xala.linhaColisaoEsquerda,BLACK);
                
            EndMode2D();

            DrawText(FormatText("%.2f %.2f",cam.target.x, cam.target.y),10,10,20,YELLOW);
            DrawText(FormatText("%.2f %.2f",xala.inercia.x, xala.inercia.y),10,40,20,YELLOW);
            
        EndDrawing();
    }
    CloseWindow(); //temporario
}
