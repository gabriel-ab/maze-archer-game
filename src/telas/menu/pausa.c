#include "../../include/tela.h"
#include "../../include/botoes.h"
#include "../../include/som.h"

void telaPausa() {
    screenshot = LoadTextureFromImage(GetScreenData());

    const char *textButtons[] = {
        "CONTINUE",
        "RESTART",
        "SETTINGS",
        "QUIT"
    };

    Rectangle buttons[4];
    for (int i = 0; i < 4; i++) {
        buttons[i] = (Rectangle) { tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    
    static int seletor = 0;
    bool event = 0, exit = 0;
    ShowCursor();
    while(!exit) {
        
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawTexture(
                    screenshot,
                    tela.width/2 -screenshot.width/2,
                    tela.height/2 -screenshot.height/2,
                    Fade(WHITE,0.2)
                );
            EndShaderMode();

            for (int i = 0; i < 4; i++){
                drawButtonD(textButtons[i], buttons[i], seletor == i);
            }
        EndDrawing();
        if (verificarTamanhoTela()) {
            for (int i = 0; i < 4; i++) {
                buttons[i] = (Rectangle) {
                    tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50
                };
            }
        }
        menuControl(0,3, &seletor);

        for (int i = 0; i < 4; i++){
            if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){
                seletor = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    event = 1;
                }
            }
        }
        if (IsKeyPressed(KEY_ENTER)) event = 1;
        if (IsKeyPressed(KEY_ESCAPE)) exit = 1;

        if (event) {
            PlaySound(somBotao);
            switch (seletor) {
            case 0:
                exit = true;
                break;
            case 1:
                isRestarting = true;
                exit = true;
                break;
            case 2:
                telaAnterior = telaAtual;
                telaAtual = TELA_CONFIG;
                telaConfiguracao();
                break;
            case 3:
                telaAtual = TELA_MENU;
                exit = true;
                break;
            }
            event = 0;
        }
    }
}
