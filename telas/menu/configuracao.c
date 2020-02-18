#include "../../lib/botoes.h"
#include "../../lib/som.h"
#include "../../lib/tela.h"

void telaConfiguracao();
void drawTelaConfiguracao(Texture2D background, Rectangle botoes[]);
void logicaBotoesConfiguracao(Rectangle botoes[]);

//TELA DE CONFIGURAÇÃO
void telaConfiguracao() {
    
    playMusic(1);
    drawTelaConfiguracao(background, getBotoesConfiguracao());
    logicaBotoesConfiguracao(getBotoesConfiguracao());

    verificarTamanhoTela();
}

void drawTelaConfiguracao(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
            
        ClearBackground(BLACK);

        if(isPaused) {
            BeginShaderMode(shader);
                DrawTexture(background, 0, 0, WHITE);
            EndShaderMode();
        } else {
            DrawTexture(background, 0, 0, WHITE);
        }

        

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsConfiguracao[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsConfiguracao[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void logicaBotoesConfiguracao(Rectangle botoes[]) {

    // MUDAR PARA TELA CHEIA
    if(CheckCollisionPointRec(GetMousePosition(), botoes[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            playFx(1);
            telaCheia();
            updateBackground();
            if(is_fullscreen){
                textButtonsConfiguracao[0] = "FULLSCREEN: ON";
            }else{
                textButtonsConfiguracao[0] = "FULLSCREEN: OFF";
            }
            
        }
    }

    // DEIXAR O JOGO SEM SOM
    if(CheckCollisionPointRec(GetMousePosition(), botoes[1])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
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
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            playFx(1);
            telaAtual = telaAnterior;
        }
    }
}
