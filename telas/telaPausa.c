#include "../lib/tela.h"
#include "../lib/botoes.h"
#include "../lib/som.h"

void telaPausa();
void drawtelaPausa(Texture2D background, Rectangle botoes[]);
void logicatelaPausa(Rectangle botoes[]);

Shader shader;

void telaPausa() {
    
    //pathImageBackgroundAnterior = pathImageBackground;
    Image image = GetScreenData();
    ImageColorContrast(&image, -40);
    ImageColorBrightness(&image, -80);
    setImageBackground(image);
    setShader("resources/shaders/blur.fs");
    
    while(isPaused) {
        
        drawtelaPausa(background, getBotoesPausa());
        logicatelaPausa(getBotoesPausa());

        while (telaAtual == TELA_CONFIG)
        {
            if(IsKeyPressed(KEY_P)) {
                telaAtual = telaAnterior;
                isPaused = false;
            }
            telaConfiguracao();
        }
        
    }
}

void drawtelaPausa(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
            DrawTexture(background, 0, 0, WHITE);
        EndShaderMode();

        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsPausa[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsPausa[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        
    EndDrawing();
}

void logicatelaPausa(Rectangle botoes[]){

    ShowCursor();

    //VOLTAR PARA O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            setPathImageBackground("resources/images/wallpaper.png");
            updateBackground();
            isPaused = !isPaused;
            
        }
    }

    //VOLTAR PARA REINICIAR O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            setPathImageBackground("resources/images/wallpaper.png");
            updateBackground();
            isRestarting = true;
            isPaused = !isPaused;
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
            setPathImageBackground("resources/images/wallpaper.png");
            updateBackground();
            PlaySound(somBotao);
            telaAtual = TELA_MENU;
            isPaused = !isPaused;   
        }
    }

    if(IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }
}