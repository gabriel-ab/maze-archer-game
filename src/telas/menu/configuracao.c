#include "../../include/som.h"
#include "../../include/tela.h"

//TELA DE CONFIGURAÇÃO
void telaConfiguracao() {
    static int selected = 0;
    static bool mute = false;
    int event = 0; // click or enter press
    char *textButtons[] = {
        "FULLSCREEN: OFF",
        "MUTE: OFF",
        "BACK",
    };
    Rectangle buttons[3];
    for (int i = 0; i < 3; i++){
        buttons[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    
    while(telaAtual == TELA_CONFIG && !WindowShouldClose()) {
        verificarTamanhoTela();

        BeginDrawing();
                
            ClearBackground(BLACK);

            if(telaAnterior == TELA_FASE_CUSTOM) {
                BeginShaderMode(shader);
                DrawTexture(
                    screenshot,
                    tela.width/2 -screenshot.width/2,
                    tela.height/2 -screenshot.height/2,
                    Fade(WHITE,0.2)
                );
                EndShaderMode();
            } else {
                drawMenuBackground(WHITE);
                playMusic(1);
            }
            
            for (int i = 0; i < 3; i++)
            {
                drawButtonD(textButtons[i], buttons[i], selected == i);
            }
        EndDrawing();

        menuControl(0, &selected, 2);

        if (verificarTamanhoTela()) {
            for (int i = 0; i < 3; i++) {
                buttons[i] = (Rectangle) {
                    tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50
                };
            }
        }

        if (IsKeyPressed(KEY_ESCAPE)) telaAtual = telaAnterior;

        for (int i = 0; i < 3; i++){
            if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){
                selected = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    event = 1;
                }
            }
        }
        if (IsKeyPressed(KEY_ENTER)) event = 1;

        if(event){
            switch(selected){
            case 0: 
                playFx(1);
                telaCheia();
                if(is_fullscreen){
                    textButtons[0] = "FULLSCREEN: ON";
                }else{
                    textButtons[0] = "FULLSCREEN: OFF";
                }
                event = 0;
                break;
            case 1: //MUTE
                playFx(1);
                if(mute){
                    textButtons[1] = "MUTE: OFF";
                    SetMasterVolume(100);
                }else{
                    textButtons[1] = "MUTE: ON";
                    SetMasterVolume(0);
                }
                mute = !mute;
                event = 0;
                break;
            case 2: // SAIR
                playFx(1);
                telaAtual = telaAnterior;
                break;
            }
        }
    }
}