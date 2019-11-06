#include <string.h>
#include <raylib.h>
#include "lib/constants.h"
#include "headers/tela.h"
#include "util.h"

bool *jogo_rodando = true;

/*
VARIÁVEL QUE DETERMINA A TELA ATUAL
0 - MENU
1 - JOGO
2 - SETTINGS
*/
int currentScreen = 0;

char *resolucao = {"1280x720"};

int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width, tela.height, "TESTE");
    telaCheia();

    //BACKGROUND
    Image backgroundImage = LoadImage("resources/wallpaper.png");
    ImageResize(&backgroundImage, tela.width, tela.height);  
    Texture2D texture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);

    //BOTÕES DA TELA DE MENU
    
    const char *textButtonsMenu[] = {
        "START",
        "LOAD",
        "SETTINGS",
        "QUIT"
    };

    Rectangle botoesMenu[getLengthOf(textButtonsMenu)];

    for (int i = 0; i < getLengthOf(textButtonsMenu); i++)
    {
        botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }


    //BOTÕES DA TELA DE CONFIGURAÇÃO

    char *textButtonsConfiguracao[] = {
        "RESOLUÇÃO",
        "MUTE: OFF",
        "BACK",
    };

    Rectangle botoesConfiguracao[getLengthOf(textButtonsConfiguracao)];

    for (int i = 0; i < getLengthOf(textButtonsConfiguracao); i++)
    {
        botoesConfiguracao[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }

    //BOTÕES DE RESOLUÇÃO DE TELA

    char *textButtonsResolucao[] = {
        "1280x720",
        "800x600",
        "640x480",
    };

    Rectangle botoesResolucao[getLengthOf(textButtonsConfiguracao)];

    for (int i = 0; i < getLengthOf(textButtonsConfiguracao); i++)
    {
        botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }
    

    SetTargetFPS(60);

    while (jogo_rodando  && !WindowShouldClose()) 
    {
        if (currentScreen == 1) 
        {
            gameScreen();
        }
        else if (currentScreen == 2)
        {
            logicaBotoesConfiguracao(botoesConfiguracao);
            telaConfiguracao(texture, botoesConfiguracao, textButtonsConfiguracao);
        }
        else
        {
            logicaBotoesMenu(botoesMenu);
            menuScreen(texture, botoesMenu, textButtonsMenu);
        }
    }
    
    UnloadTexture(texture);
    CloseWindow(); 
    return 0;
}

//TELA DE MENU
void logicaBotoesMenu(Rectangle botoesMenu[]) {
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoesMenu[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            currentScreen = 2;
        }
    }

    //SAIR DO JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoesMenu[3]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            jogo_rodando = false;
        }
    }
}
void menuScreen(Texture2D background, Rectangle botoesMenu[], char *textButtonsMenu[]) {

    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoesMenu[i], CheckCollisionPointRec(GetMousePosition(), botoesMenu[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoesMenu[i].x-5, (int) botoesMenu[i].y-5, (int) botoesMenu[i].width+10, (int) botoesMenu[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoesMenu[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsMenu[i], (int)( botoesMenu[i].x + botoesMenu[i].width/2 - MeasureText(textButtonsMenu[i], 20)/2), (int) botoesMenu[i].y + 16, 20, WHITE);
        }
        

    EndDrawing();
}

//TELA DE CONFIGURAÇÃO
void logicaBotoesConfiguracao(Rectangle botoesConfiguracao[]) {
    //VOLTAR PARA O MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoesConfiguracao[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            currentScreen = 0;
        }
    }
}
void telaConfiguracao(Texture2D background, Rectangle botoesConfiguracao[], char *textButtonsConfiguracao[]) {
    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoesConfiguracao[i], CheckCollisionPointRec(GetMousePosition(), botoesConfiguracao[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoesConfiguracao[i].x-5, (int) botoesConfiguracao[i].y-5, (int) botoesConfiguracao[i].width+10, (int) botoesConfiguracao[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoesConfiguracao[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsConfiguracao[i], (int)( botoesConfiguracao[i].x + botoesConfiguracao[i].width/2 - MeasureText(textButtonsConfiguracao[i], 20)/2), (int) botoesConfiguracao[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void gameScreen() {}

