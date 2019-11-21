#include "../lib/tela.h"
#include "../lib/botoes.h"

void telaPausa(bool* isPaused);
void drawtelaPausa(Texture2D background, Rectangle botoes[]);
void logicatelaPausa();

void telaPausa(bool* isPaused) {
    
    //pathImageBackgroundAnterior = pathImageBackground;
    setImageBackground("resources/images/wallpaper.png");
    updateBackground();

    while(isPaused){
        drawtelaPausa(background, getBotoesPausa());
        logicatelaPausa();
    }
}

void drawtelaPausa(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
        ClearBackground(GRAY);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsPausa[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsPausa[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        
    EndDrawing();
}

void logicatelaPausa(){}