#include <raylib.h>
#include "../lib/tela.h"
#include "../lib/botoes.h"
#include "../lib/som.h"

void telaFracasso();
void drawTelaFracasso( Rectangle botoes[]);
void logicaTelaFracasso( Rectangle botoes[]);


void telaFracasso() {

    setFont("resources/font/custom_alagard.png");

    while(telaAtual == TELA_FRACASSO) {
        drawTelaFracasso(getBotoesFracasso());
        logicaTelaFracasso(getBotoesFracasso());
    }
    
    UnloadFont(font);
}

void drawTelaFracasso( Rectangle botoes[]) {

    BeginDrawing();
            
        ClearBackground(BLACK);

        DrawTextEx(font, "YOU DIED", (Vector2){tela.width/2 - 375, tela.height/2 - 50}, 150,0, RED);

        for (int i = 0; i < 2; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsFracasso[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsFracasso[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        

    EndDrawing();
}


void logicaTelaFracasso(Rectangle botoes[]) {
    //VOLTAR PARA REINICIAR O JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = telaAnterior;
        }
    }

    //IR PARA TELA DE MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_MENU;
        }
    }
}