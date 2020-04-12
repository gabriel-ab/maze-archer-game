#include "../../inc/tela.h"
#include "../../inc/botoes.h"
#include "../../inc/som.h"

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

    Rectangle buttons[4];
    for (int i = 0; i < 4; i++) {
        buttons[i] = (Rectangle) {
            tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    
    static int seletor = 0;
    
    while(isPaused) {
        menuControl(0,3, &seletor);
        
        drawtelaPausa(buttons, seletor);
        logicatelaPausa(buttons, &seletor);

        if (telaAtual == TELA_CONFIG) telaConfiguracao();
    }
}

void drawtelaPausa(Rectangle botoes[], int seletor) {
    static const char *textButtons[] = {
        "CONTINUE",
        "RESTART",
        "SETTINGS",
        "QUIT"
    };
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

        for (int i = 0; i < 4; i++){
            drawButtonD(textButtons[i], botoes[i], seletor == i);
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