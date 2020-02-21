#include "../lib/tela.h"
#include "../lib/botoes.h"
#include "../lib/som.h"

void telaPausa();
void drawtelaPausa(Rectangle botoes[], int seletor);
void logicatelaPausa(Rectangle botoes[], int *seletor);

Shader shader;

void telaPausa() {
    
    Image image = GetScreenData();
    ImageColorContrast(&image, -40);
    ImageColorBrightness(&image, -80);
    screenshot = LoadTextureFromImage(image);
    UnloadImage(image);
    setShader("resources/shaders/blur.fs");

    static int seletor = 0;
    
    while(isPaused) {
        if (IsKeyPressed(KEY_UP) && seletor > 0)   seletor--;
        if (IsKeyPressed(KEY_DOWN) && seletor < 3) seletor++;
        
        drawtelaPausa(getBotoesPausa(), seletor);
        logicatelaPausa(getBotoesPausa(), &seletor);

        while (telaAtual == TELA_CONFIG)
        {
            if(IsKeyPressed(KEY_ESCAPE)) {
                telaAtual = telaAnterior;
                isPaused = false;
            }
            telaConfiguracao();
        }
    }
}

void drawtelaPausa(Rectangle botoes[], int seletor) {
    BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
            DrawTexture(
                screenshot,
                tela.width/2 -screenshot.width/2,
                tela.height/2 -screenshot.height/2,
                Fade(BLACK,0.2)
            );
        EndShaderMode();

        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], seletor == i ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, seletor == i ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsPausa[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsPausa[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        
    EndDrawing();
}

void logicatelaPausa(Rectangle botoes[], int *seletor){

    ShowCursor();

    //VOLTAR PARA O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]) || *seletor == 0)
    {
        *seletor = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            isPaused = !isPaused;
            
        }
    }

    //VOLTAR PARA REINICIAR O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]) || *seletor == 1)
    {
        *seletor = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            isRestarting = true;
            isPaused = !isPaused;
        }
    }

    //VOLTAR PARA A TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]) || *seletor == 2)
    {
        *seletor = 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            telaAnterior = telaAtual;
            telaAtual = TELA_CONFIG;
        }
    }
    
    //IR PARA TELA DE MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoes[3]) || *seletor == 3)
    {
        *seletor = 3;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_MENU;
            isPaused = !isPaused;
        }
    }

    if(IsKeyPressed(KEY_ESCAPE)) {
        isPaused = false;
    }
}