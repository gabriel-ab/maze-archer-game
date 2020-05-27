#include "../../include/tela.h"
#include "../../include/draw.h"
#include "../../include/som.h"

static void set_buttons_position(Rectangle buttons[]) {
    for (int i = 0; i < 4; i++) {
        buttons[i] = (Rectangle) { GetScreenWidth()/2 - 100, GetScreenHeight()/8*i + GetScreenHeight()/2, 200, 50};
    }
}
void telaPausa() {
    screenshot = LoadTextureFromImage(GetScreenData());

    const char *textButtons[] = {
        "CONTINUE",
        "RESTART",
        "SETTINGS",
        "QUIT"
    };

    Rectangle buttons[4];
    set_buttons_position(buttons);
    
    static int seletor = 0;
    bool event = 0, exit = 0;
    ShowCursor();
    while(!exit) {
        
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawTexture(
                    screenshot,
                    GetScreenWidth()/2 -screenshot.width/2,
                    GetScreenHeight()/2 -screenshot.height/2,
                    WHITE
                );
            EndShaderMode();
            DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),Fade(BLACK,0.5));

            for (int i = 0; i < 4; i++){
                drawButtonD(textButtons[i], buttons[i], seletor == i);
            }
        EndDrawing();
        if (IsWindowResized())
            set_buttons_position(buttons);

        menuControl(0, &seletor, 3);

        for (int i = 0; i < 4; i++){
            if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){
                seletor = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    event = 1;
                }
            }
        }
        if (IsKeyPressed(KEY_ENTER)) event = true;
        if (IsKeyPressed(KEY_ESCAPE)) exit = true;

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
                set_buttons_position(buttons);
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
