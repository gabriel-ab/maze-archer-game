#include <raylib.h>
#include "../telaPausa.c"

bool isPaused = false;

void fase_3();
void draw_fase_3();
void logica_fase_3();

void fase_3() {
    logica_fase_3();
    draw_fase_3();
}

void draw_fase_3() {
    BeginDrawing();
        ClearBackground(GRAY);

        DrawRectangle(10,10,50,50, GREEN);

        if(isPaused) telaPausa(&isPaused);

    EndDrawing();
}

void logica_fase_3() {
    if(IsKeyDown(KEY_ESCAPE)) isPaused = true;
}