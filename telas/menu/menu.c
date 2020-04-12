#include "../../inc/botoes.h"
#include "../../inc/som.h"
#include "../../inc/tela.h"
#include "../../inc/define.h"
#include "../../inc/data.h"

void telaMenu();
void drawTelaMenu(Texture2D background, Rectangle botoes[], int selected);
void logicaBotoesMenu(Rectangle botoes[], int *selected);

//TELA DE MENU
void telaMenu() {
    static int selected = 0;
    setFont("resources/font/custom_alagard.png");
    
    Rectangle buttons[4];
    for (int i = 0; i < 4; i++) {
        buttons[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    
    while(telaAtual == TELA_MENU && jogo_rodando && !WindowShouldClose()) {
        playMusic(1);
        verificarTamanhoTela();

        drawTelaMenu(background, buttons, selected);
        logicaBotoesMenu(buttons, &selected);

        menuControl(0, 4, &selected);
        if (IsKeyPressed(KEY_RIGHT)) selected = 4;
        if (IsKeyPressed(KEY_LEFT) && selected == 4) selected = 3;
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4)) jogo_rodando = false;
    }
}

void drawTelaMenu(Texture2D background, Rectangle botoes[], int selected) {
    
    char titulo[50] = "UNTITLED\n\t\t\tDUNGEON\n\t\t\t\t\t\t\t\t\tGAME";
    
    static int framescounter = 0;
    
    framescounter++;
    static char *textButtons[] = {
        "START",
        "LOAD",
        "SETTINGS",
        "QUIT"
    };
    
    BeginDrawing();            
        ClearBackground(BLACK);

        drawMenuBackground(WHITE);
        DrawTextEx(font, TextSubtext(titulo, 0, framescounter/6), (Vector2){101,108}, 60, 0, GOLD);
        DrawTextEx(font, TextSubtext(titulo, 0, framescounter/6), (Vector2){100,100}, 60, 0, RED);
        
        for (int i = 0; i < 4; i++)
        {
            drawButtonD(textButtons[i], botoes[i], selected == i);
        }
        drawButtonD("FASE CUSTOMIZADA", (Rectangle){tela.width -260, tela.height -80,  240, 50}, selected == 4);
    EndDrawing();
}

void logicaBotoesMenu(Rectangle botoes[], int *selected) {
    
    //IR PARA TELA DE JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]) || *selected == 0)
    {
        *selected = 0;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            telaAtual = TELA_FASE_1;
                        
        }
    }

    //IR PARA TELA DE JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[1]) || *selected == 1)
    {
        *selected = 1;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            PlaySound(somBotao);
            telaAtual = load();
            
        }
    }
    
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]) || *selected == 2)
    {
        *selected = 2;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(2);
            telaAnterior = telaAtual;
            telaAtual = TELA_CONFIG;
            
        }
    }

    //SAIR DO JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[3]) || *selected == 3)
    {
        *selected = 3;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(2);
            jogo_rodando = false;
        }
    }
    //Temporario
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){tela.width -260, tela.height -80,  260, 40}) || *selected == 4)
    {
        *selected = 4;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ENTER)) 
        {
            playFx(2);
            telaAtual = TELA_SEL_MAPA;
        }
    }
}
