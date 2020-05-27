#include <raylib.h>
#include "../../include/tela.h"
#include "../../include/botoes.h"
#include "../../include/som.h"


void telaFracasso() {
    int selected = 0;
    bool event = 0;
    char *textButtons[] = {
        "RESTART",
        "QUIT",
    };
    
    Rectangle buttons[2];
    for (int i = 0; i < 2; i++){
        buttons[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/1.4, 200, 50};
    }
    ShowCursor();

    while(telaAtual == TELA_FRACASSO && !WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(font, "YOU DIED", (Vector2){tela.width/2 - 375, tela.height/2 - 50}, 150,0, RED);
            for (int i = 0; i < 2; i++){
                drawButtonD(textButtons[i], buttons[i], selected == i);
            }
        EndDrawing();
        playFx(7);

        // Mouse Control
        for (int i = 0; i < 2; i++){
            if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){
                selected = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    event = 1;
                }
            }
        }
        if (IsKeyPressed(KEY_ENTER)) event = 1;

        if (event) {
            PlaySound(somBotao);
            switch (selected) {
            case 0:
                telaAtual = telaAnterior;
                break;
            case 1:
                telaAtual = TELA_MENU;
                break;
            }
            event = 0;
        }
        menuControl(0, 1, &selected);
    }
    
    UnloadFont(font);
}




