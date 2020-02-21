#include "../../lib/botoes.c"
#include "../../lib/som.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/data.h"

void telaMenu();
void drawTelaMenu(Texture2D background, Rectangle botoes[], int seletorMapa);
void logicaBotoesMenu(Rectangle botoes[], int *seletorMapa);

//TELA DE MENU
void telaMenu() {
    static int seletorMapa = 0;
    setFont("resources/font/custom_alagard.png");
    
    while(telaAtual == TELA_MENU && jogo_rodando && !WindowShouldClose()) {
        playMusic(1);
        verificarTamanhoTela();
        drawTelaMenu(background, getBotoesMenu(), seletorMapa);
        logicaBotoesMenu(getBotoesMenu(),&seletorMapa);

        if (IsKeyPressed(KEY_UP) && seletorMapa > 0)   seletorMapa--;
        if (IsKeyPressed(KEY_DOWN) && seletorMapa < 4) seletorMapa++;
        if (IsKeyPressed(KEY_LEFT)) seletorMapa = 0;
        if (IsKeyPressed(KEY_RIGHT)) seletorMapa = 4;
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4)) jogo_rodando = false;
        
    }
}

void drawTelaMenu(Texture2D background, Rectangle botoes[], int seletorMapa) {
    
    char titulo[50] = "UNTITLED\n\t\t\tDUNGEON\n\t\t\t\t\t\t\t\t\tGAME";
    
    static int framescounter = 0;
    
    framescounter++;
    
    BeginDrawing();
            
        ClearBackground(BLACK);

        drawMenuBackground(WHITE);
        
        DrawTextEx(font, TextSubtext(titulo, 0, framescounter/6), (Vector2){101,108}, 60, 0, GOLD);
        DrawTextEx(font, TextSubtext(titulo, 0, framescounter/6), (Vector2){100,100}, 60, 0, RED);
        
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], seletorMapa == i ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, seletorMapa == i ? LIGHTGRAY : (Color){128,0,0, 255});
            DrawText( textButtonsMenu[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtonsMenu[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        DrawRectangle(tela.width -260, tela.height -80,  260, 40, seletorMapa == 4 ? RED : DARKPURPLE);
        DrawText("FASE CUSTOMIZADA",tela.width -240,tela.height -70, 20, seletorMapa == 4 ? LIGHTGRAY : GRAY);

    EndDrawing();
}

void logicaBotoesMenu(Rectangle botoes[], int *seletorMapa) {
    
    //IR PARA TELA DE JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]) || *seletorMapa == 0)
    {
        *seletorMapa = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_FASE_1;
                        
        }
    }

    //IR PARA TELA DE JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]) || *seletorMapa == 1)
    {
        *seletorMapa = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            telaAtual = load();
            
        }
    }
    
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]) || *seletorMapa == 2)
    {
        *seletorMapa = 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(2);
            telaAnterior = telaAtual;
            telaAtual = TELA_CONFIG;
            
        }
    }

    //SAIR DO JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[3]) || *seletorMapa == 3)
    {
        *seletorMapa = 3;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(2);
            jogo_rodando = false;
        }
    }
    //Temporario
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){tela.width -260, tela.height -80,  260, 40}) || *seletorMapa == 4)
    {
        *seletorMapa = 4;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(2);
            telaAtual = TELA_SEL_MAPA;
        }
    }
}
