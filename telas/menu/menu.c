#include "../../inc/botoes.h"
#include "../../inc/som.h"
#include "../../inc/tela.h"
#include "../../inc/define.h"
#include "../../inc/data.h"

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
    for (int i = 0; i < 4; i++) {
        buttons[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    buttons[4] = (Rectangle){tela.width -260, tela.height -80,  260, 40};
    // if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){tela.width -260, tela.height -80,  260, 40}) || *selected == 4)
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
        
        UpdateMusicStream(menuMusic);
        verificarTamanhoTela();
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
        menuControl(0, 4, &selected);
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
