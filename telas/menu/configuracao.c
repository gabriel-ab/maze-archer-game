#include "../../lib/botoes.h"
#include "../../lib/som.h"
#include "../../lib/tela.h"

void telaConfiguracao();
void drawTelaConfiguracao(Rectangle botoes[], int seletor);
void logicaBotoesConfiguracao(Rectangle botoes[], int *seletor);

//TELA DE CONFIGURAÇÃO
void telaConfiguracao() {
    static int seletor = 0;
    
    while(telaAtual == TELA_CONFIG && !WindowShouldClose()) {
        verificarTamanhoTela();
        if (IsKeyPressed(KEY_UP) && seletor > 0)   seletor--;
        if (IsKeyPressed(KEY_DOWN) && seletor < 2) seletor++;

        drawTelaConfiguracao(getBotoesConfiguracao(),seletor);
        logicaBotoesConfiguracao(getBotoesConfiguracao(),&seletor);
    }
}

void drawTelaConfiguracao(Rectangle botoes[], int seletor) {
    BeginDrawing();
            
        ClearBackground(BLACK);

        if(isPaused) {
            BeginShaderMode(shader);
            DrawTexture(
                screenshot,
                tela.width/2 -screenshot.width/2,
                tela.height/2 -screenshot.height/2,
                Fade(BLACK,0.2)
            );
            EndShaderMode();
        } else {
            drawMenuBackground(WHITE);
            playMusic(1);
        }
        
        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoes[i], seletor == i ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, seletor == i ? LIGHTGRAY : (Color){128,0,0, 255});
            DrawText(textButtonsConfiguracao[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsConfiguracao[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
    EndDrawing();
}

void logicaBotoesConfiguracao(Rectangle botoes[], int *seletor) {
    
    if (IsKeyPressed(KEY_ESCAPE)) telaAtual = telaAnterior;

    // MUDAR PARA TELA CHEIA
    if(CheckCollisionPointRec(GetMousePosition(), botoes[0]) || *seletor == 0) 
    {
        *seletor = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(1);
            telaCheia();
            if(is_fullscreen){
                textButtonsConfiguracao[0] = "FULLSCREEN: ON";
            }else{
                textButtonsConfiguracao[0] = "FULLSCREEN: OFF";
            }
            
        }
    }

    // DEIXAR O JOGO SEM SOM
    if(CheckCollisionPointRec(GetMousePosition(), botoes[1]) || *seletor == 1) 
    {
        *seletor = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            static bool mute = false;
            playFx(1);
            if(!mute){
               textButtonsConfiguracao[1] = "MUTE: ON";
               SetMasterVolume(0);
               mute = true;
            }else{
                textButtonsConfiguracao[1] = "MUTE: OFF";
                SetMasterVolume(100);
                mute = false;
            }
        }
    }

    //VOLTAR PARA O MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]) || *seletor == 2)
    {
        *seletor = 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(1);
            telaAtual = telaAnterior;
        }
    }
}
