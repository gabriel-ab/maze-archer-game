#include <raylib.h>
#include "../../lib/tela.h"

void telaResolucao(Texture2D *background, Rectangle botoes[], char *textButtons[]);
void logicaBotoesResolucao(Rectangle botoesResolucao[], Rectangle botoesConfiguracao[], Rectangle botoesMenu[], Sound somBotao, int *telaAtual, Texture2D *background);
void setBackground(Texture2D *background);
void atualizarPosicaoBotoes(Rectangle botoesResolucao[], Rectangle botoesConfiguracao[], Rectangle botoesMenu[]);

//TELA DE RESOLUÇÃO
void telaResolucao(Texture2D *background, Rectangle botoes[], char *textButtons[]) {
    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(*background, 0, 0, WHITE);

        for (int i = 0; i < 5; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtons[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtons[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void logicaBotoesResolucao(Rectangle botoesResolucao[], Rectangle botoesConfiguracao[], Rectangle botoesMenu[], Sound somBotao, int *telaAtual, Texture2D *background) {

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 1920;
            tela.height = 1080;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            setBackground(background);
            atualizarPosicaoBotoes(botoesResolucao, botoesConfiguracao, botoesMenu);
        }
    }
      

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[1])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 1280;
            tela.height = 720;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            setBackground(background);
            atualizarPosicaoBotoes(botoesResolucao, botoesConfiguracao, botoesMenu);
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[2])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 800;
            tela.height = 600;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            setBackground(background);
            atualizarPosicaoBotoes(botoesResolucao, botoesConfiguracao, botoesMenu);
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[3])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            tela.width = 640;
            tela.height = 480;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            setBackground(background);
            for (int i = 0; i < 4; i++)
            {
                botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/4, 200, 50};
            }
            botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};
        }
    }

    //VOLTAR PARA O CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoesResolucao[4]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            *(telaAtual) = TELA_CONFIG;
        }
    } 
}

void setBackground(Texture2D *background) {
    Image backgroundImage = LoadImage("resources/images/wallpaper.png");
    ImageResize(&backgroundImage, tela.width, tela.height);  
    *background = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
}

void atualizarPosicaoBotoes(Rectangle botoesResolucao[], Rectangle botoesConfiguracao[], Rectangle botoesMenu[]) {
    for (int i = 0; i < 4; i++)
    {
        botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
    }
    botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};

    for (int i = 0; i < 3; i++)
    {
        botoesConfiguracao[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }

    for (int i = 0; i < 4; i++)
    {
        botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
}

