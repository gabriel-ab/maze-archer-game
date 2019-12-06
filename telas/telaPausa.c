#include "../lib/tela.h"
#include "../lib/botoes.h"
#include "../lib/som.h"

void telaPausa(bool* isPaused, bool* isRestarting);
void drawtelaPausa(Texture2D background, Rectangle botoes[]);
void logicatelaPausa(bool* isPaused, bool* isRestarting, Rectangle botoes[]);

void telaPausa(bool* isPaused, bool* isRestarting) {
    
    //pathImageBackgroundAnterior = pathImageBackground;
    setImageBackground("resources/images/wallpaper.png");
    updateBackground();
    
    while(*isPaused) {

        drawtelaPausa(background, getBotoesPausa());
        logicatelaPausa(isPaused, isRestarting, getBotoesPausa());

        while (telaAtual == TELA_CONFIG)
        {
            if(IsKeyPressed(KEY_P)) {
                telaAtual = telaAnterior;
                *isPaused = !(*isPaused);
            }
            telaConfiguracao();
        }
        
    }
}

void drawtelaPausa(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsPausa[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsPausa[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        
    EndDrawing();
}

void logicatelaPausa(bool *isPaused, bool* isRestarting, Rectangle botoes[]){
    //VOLTAR PARA O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            *isPaused = !(*isPaused);
        }
    }

    //VOLTAR PARA REINICIAR O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            *isRestarting = true;
            *isPaused = !(*isPaused);
        }
    }

    //VOLTAR PARA A TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAnterior = telaAtual;
            telaAtual = TELA_CONFIG;
        }
    }
    
    //IR PARA TELA DE MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoes[3]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_MENU;
            *isPaused = !*isPaused;   
        }
    }

    if(IsKeyPressed(KEY_P)) {
        *isPaused = !(*isPaused);
    }
}