#include <raylib.h>
#include "../../inc/tela.h"
#include "../../inc/botoes.h"
#include "../../inc/som.h"


void telaFracasso() {
    setFont("resources/font/custom_alagard.png");

    int selected = 0;
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
                drawButtonD(textButtons[i], buttons[i], selected);
            }
        EndDrawing();
        playFx(7);

        //VOLTAR PARA REINICIAR O JOGO
        if (CheckCollisionPointRec(GetMousePosition(), buttons[0]))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                PlaySound(somBotao);
                telaAtual = telaAnterior;
            }
        }

        //IR PARA TELA DE MENU
        if (CheckCollisionPointRec(GetMousePosition(), buttons[1]))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
            {
                PlaySound(somBotao);
                telaAtual = TELA_MENU;
            }
        }
        menuControl(0, 1, &selected);
    }
    
    UnloadFont(font);
}




