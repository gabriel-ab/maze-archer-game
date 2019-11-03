#include <raylib.h>
#include <math.h>
#include "headers/tela.h"
#include "headers/movimenta.h"


typedef struct Personagem{
    Vector2 posicao;
    int rotacao; //Em Graus
    int vida;

}Personagem;

int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(tela.width, tela.height, "dungeon ni deai wo motomeru no wa machigatteiru darou ka");


    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){tela.width/2,tela.height/2};


    while (!WindowShouldClose())
    {
        //update
        atualizaCamera(&camera);

        if(IsKeyPressed(KEY_F)) telaCheia();
        
        //input 

        //draw
        BeginDrawing();
            ClearBackground((Color){50,50,50,255});
            BeginMode2D(camera);

            EndMode2D();
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}
