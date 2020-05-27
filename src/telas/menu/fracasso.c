#include <raylib.h>
#include "../../include/tela.h"
#include "../../include/som.h"
#include "../../include/draw.h"


static void set_buttons_position(Rectangle buttons[]){
    for (int i = 0; i < 2; i++){
        buttons[i] = (Rectangle) {GetScreenWidth()/2 - 100, GetScreenHeight()/8*i + GetScreenHeight()/1.4, 200, 50};
    }
}

void telaFracasso() {
    int selected = 0;
    bool event = 0;
    char *textButtons[] = {
        "RESTART",
        "QUIT",
    };
    
    Rectangle buttons[2];
    set_buttons_position(buttons);
    ShowCursor();

    while(telaAtual == TELA_FRACASSO && !WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(font, "YOU DIED", (Vector2){GetScreenWidth()/2 - 375, GetScreenHeight()/2 - 50}, 150,0, RED);
            for (int i = 0; i < 2; i++){
                drawButtonD(textButtons[i], buttons[i], selected == i);
            }
        EndDrawing();
        if (IsWindowResized()) {
            set_buttons_position(buttons);
        }
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
        menuControl(0, &selected, 1);
    }
    
    UnloadFont(font);
}




