#include <raylib.h>
#include "headers/tela.h"
#include "headers/movimenta.h"

int main(){

    InitWindow(tela.width, tela.height, "dungeon ni deai wo motomeru no wa machigatteiru darou ka");

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){tela.width/2,tela.height/2};

    while (!WindowShouldClose())
    {
        //update
        camera.offset = (Vector2){tela.width/2,tela.height/2};
        
        //input 

        //draw
        BeginDrawing();
            ClearBackground((Color){100,100,100,255});
            BeginMode2D(camera);
            EndMode2D();
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}
