#include <raylib.h>
#include "../../lib/tela.h"
#include "../../lib/background.h"
#include "../../lib/botoes.h"
#include "../../lib/som.h"

void telaResolucao();
void drawTelaResolucao(Texture2D background, Rectangle botoes[]);
void logicaBotoesResolucao(Rectangle botoes[]);

//TELA DE RESOLUÇÃO
void telaResolucao() {
    drawTelaResolucao(background, getBotoesResolucao());
    logicaBotoesResolucao(getBotoesResolucao());
}

void drawTelaResolucao(Texture2D background, Rectangle botoes[]) {
    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 5; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsResolucao[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsResolucao[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void logicaBotoesResolucao(Rectangle botoes[]) {

    if(CheckCollisionPointRec(GetMousePosition(), botoes[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 1920;
            tela.height = 1080;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            updateBackground();
            atualizarPosicaoBotoes();
        }
    }
      

    if(CheckCollisionPointRec(GetMousePosition(), botoes[1])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 1280;
            tela.height = 720;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            updateBackground();
            atualizarPosicaoBotoes();
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botoes[2])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 800;
            tela.height = 600;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            updateBackground();
            atualizarPosicaoBotoes();
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botoes[3])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 640;
            tela.height = 480;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            updateBackground();
            atualizarPosicaoBotoes();
        }
    }

    //VOLTAR PARA O CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[4]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_CONFIG;
        }
    } 
}