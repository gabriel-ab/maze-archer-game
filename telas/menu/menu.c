#include "../../lib/botoes.c"
#include "../../lib/som.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/data.h"

void telaMenu();
void drawTelaMenu(Texture2D background, Rectangle botoes[]);
void logicaBotoesMenu(Rectangle botoes[]);

//TELA DE MENU
void telaMenu() {
    drawTelaMenu(background, getBotoesMenu());
    logicaBotoesMenu(getBotoesMenu());

    verificarTamanhoTela();
}

void drawTelaMenu(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
            
        ClearBackground(BLACK);

        DrawTexture(background, 0, 0, WHITE);

        
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsMenu[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsMenu[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        

    EndDrawing();
}

void logicaBotoesMenu(Rectangle botoes[]) {
    
    //IR PARA TELA DE JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_FASE_1;
            StopMusicStream(music);
            
        }
    }

    //IR PARA TELA DE JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = load();
            
        }
    }
    
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            playFx(2);
            telaAnterior = telaAtual;
            telaAtual = TELA_CONFIG;
            
        }
    }

    //SAIR DO JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[3]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            playFx(2);
            jogo_rodando = false;
            
        }
    }
   
}
