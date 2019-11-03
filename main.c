#include <string.h>
#include <raylib.h>
#include "lib/constants.h"

int main(){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TESTE");
    ToggleFullscreen();

    //BACKGROUND
    Image wallpaper = LoadImage("resources/wallpaper.png");
    ImageResize(&wallpaper, SCREEN_WIDTH, SCREEN_HEIGHT);  
    Texture2D texture = LoadTextureFromImage(wallpaper);
    UnloadImage(wallpaper);


    //BOTÕES DA TELA DE MENU 
    Rectangle botoesMenu[4];
    for (int i = 0; i < 4; i++)
    {
        botoesMenu[i] = (Rectangle) {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/8*i + SCREEN_HEIGHT/2, 200, 50};
    }
    
    const char *textButtonsMenu[] = {
        "START",
        "LOAD",
        "SETTINGS",
        "QUIT"
    };

    //BOTÕES DA TELA DE MENU 
    Rectangle botoesSettings[3];
    for (int i = 0; i < 3; i++)
    {
        botoesSettings[i] = (Rectangle) {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/8*i + SCREEN_HEIGHT/2, 200, 50};
    }
    
    const char *textButtonsSettings[] = {
        "FULLSCREEN: ON",
        "MUTE: OFF",
        "BACK",
    };

    

    /*
    VARIÁVEL QUE DETERMINA A TELA ATUAL
    0 - MENU
    1 - JOGO
    2 - SETTINGS
    */
    int currentScreen = 0;

    const char *screens[] = {
        "GAME",
        "MENU",
        "SETTINGS",
    };

    SetTargetFPS(60);

    bool *jogo_rodando = true;

    while (jogo_rodando  && !WindowShouldClose()) 
    {
        if (currentScreen == 1) 
        {
            gameScreen();
        }
        else if (currentScreen == 2)
        {
            //ALTERNAR FULLSCREEN/WINDOW
            if (CheckCollisionPointRec(GetMousePosition(), botoesSettings[0]))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    ToggleFullscreen();
                    strcpy(*textButtonsSettings[0], "FULLSCREEN: OFF");
                }
            }

            //ALTERNAR MUTE ON/OFF
            if (CheckCollisionPointRec(GetMousePosition(), botoesSettings[1]))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    currentScreen = 0;
                }
            }

            //VOLTAR PARA O MENU
            if (CheckCollisionPointRec(GetMousePosition(), botoesSettings[2]))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    currentScreen = 0;
                }
            }

            settingsScreen(texture, botoesSettings, textButtonsSettings);
        }
        else
        {
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

            menuScreen(texture, botoesMenu, textButtonsMenu);
        }
    }

   
    UnloadTexture(texture);
    CloseWindow(); 
    return 0;
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

void settingsScreen(Texture2D background, Rectangle botoesSettings[], char *textButtonsSettings[]) {
    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoesSettings[i], CheckCollisionPointRec(GetMousePosition(), botoesSettings[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoesSettings[i].x-5, (int) botoesSettings[i].y-5, (int) botoesSettings[i].width+10, (int) botoesSettings[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoesSettings[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsSettings[i], (int)( botoesSettings[i].x + botoesSettings[i].width/2 - MeasureText(textButtonsSettings[i], 20)/2), (int) botoesSettings[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void gameScreen() {}