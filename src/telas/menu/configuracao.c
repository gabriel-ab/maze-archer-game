#include "../../include/som.h"
#include "../../include/tela.h"
#include "../../include/draw.h"

static void set_buttons_position(Rectangle buttons[]) {
    for (int i = 0; i < 3; i++){
        buttons[i] = (Rectangle) {GetScreenWidth()/2 - 100, GetScreenHeight()/8*i + GetScreenHeight()/2, 200, 50};
    }
}
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
    set_buttons_position(buttons);
    
    while(telaAtual == TELA_CONFIG && !WindowShouldClose()) {
        BeginDrawing();
                
            ClearBackground(BLACK);

            if(telaAnterior == TELA_FASE_CUSTOM) {
                BeginShaderMode(shader);
                DrawTexture(
                    screenshot,
                    GetScreenWidth()/2 -screenshot.width/2,
                    GetScreenHeight()/2 -screenshot.height/2,
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

        if (IsWindowResized()) {
            set_buttons_position(buttons);
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
                if(IsWindowFullscreen()){
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