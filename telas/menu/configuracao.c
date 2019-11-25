#include "../../lib/botoes.h"
#include "../../lib/som.h"
#include "../../lib/tela.h"

void telaConfiguracao();
void drawTelaConfiguracao(Texture2D background, Rectangle botoes[]);
void logicaBotoesConfiguracao(Rectangle botoes[]);

//TELA DE CONFIGURAÇÃO
void telaConfiguracao() {
    drawTelaConfiguracao(background, getBotoesConfiguracao());
    logicaBotoesConfiguracao(getBotoesConfiguracao());

    verificarTamanhoTela();
}

void drawTelaConfiguracao(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
            
        ClearBackground(BLACK);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText(textButtonsConfiguracao[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsConfiguracao[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void logicaBotoesConfiguracao(Rectangle botoes[]) {

    // MUDAR PARA TELA CHEIA
    if(CheckCollisionPointRec(GetMousePosition(), botoes[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaCheia();
            updateBackground();
        }
    }

    //VOLTAR PARA O MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_MENU;
        }
    }
}
