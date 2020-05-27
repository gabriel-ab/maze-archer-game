#include "../../include/som.h"
#include "../../include/tela.h"
#include "../../include/define.h"
#include "../../include/data.h"
#include "../../include/draw.h"

static void set_buttons_position(Rectangle buttons[]){
    for (int i = 0; i < 4; i++) {
        buttons[i] = (Rectangle) {GetScreenWidth()/2 - 100, GetScreenHeight()/8*i + GetScreenHeight()/2, 200, 50};
    }
    buttons[4] = (Rectangle){GetScreenWidth() -260, GetScreenHeight() -80,  260, 40};
}

//TELA DE MENU
void telaMenu() {
    static int selected = 0;
    bool event = 0;
    char titulo[50] = "UNTITLED\n\t\t\tDUNGEON\n\t\t\t\t\t\t\t\t\tGAME";
    int framescounter = 0;

    PlayMusicStream(menuMusic);
    
    char *textButtons[] = {
        "START",
        "LOAD",
        "SETTINGS",
        "QUIT",
        "FASE CUSTOMIZADA"
    };

    Rectangle buttons[5];
    set_buttons_position(buttons);

    // if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){GetScreenWidth() -260, GetScreenHeight() -80,  260, 40}) || *selected == 4)
    while(telaAtual == TELA_MENU && jogo_rodando && !WindowShouldClose()) {
        
        BeginDrawing();            
            ClearBackground(BLACK);
            drawMenuBackground(WHITE);

            DrawTextEx(font, TextSubtext(titulo, 0, framescounter/6), (Vector2){101,108}, 60, 0, GOLD);
            DrawTextEx(font, TextSubtext(titulo, 0, framescounter/6), (Vector2){100,100}, 60, 0, RED);
            
            for (int i = 0; i < 5; i++){
                drawButtonD(textButtons[i], buttons[i], selected == i);
            }
        EndDrawing();

        if (IsWindowResized())
            set_buttons_position(buttons);

        UpdateMusicStream(menuMusic);
        framescounter++;

        // Mouse Control
        for (int i = 0; i < 5; i++){
            if(CheckCollisionPointRec(GetMousePosition(), buttons[i])){
                selected = i;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    event = 1;
                }
            }
        }
        // Keyboard Control
        menuControl(0, &selected, 4);
        if (IsKeyPressed(KEY_RIGHT)) selected = 4;
        if (IsKeyPressed(KEY_LEFT) && selected == 4) selected = 3;
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4)) jogo_rodando = false;
        if (IsKeyPressed(KEY_ENTER)) event = 1;

        if (event) {
            PlaySound(somBotao);
            switch (selected) {
            case 0:
                telaAtual = TELA_FASE_1;
                break;
            case 1:
                telaAtual = load();
                break;
            case 2:
                telaAnterior = telaAtual;
                telaAtual = TELA_CONFIG;
                telaConfiguracao();
                set_buttons_position(buttons);
                break;
            case 3:
                jogo_rodando = false;
                break;
            case 4:
                telaAtual = TELA_SEL_MAPA;
                break;
            }
            event = 0;
        }
    }
    StopMusicStream(menuMusic);
}
