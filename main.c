#include <string.h>
#include <raylib.h>
#include "lib/constants.h"
#include "lib/personagem.h"
#include "headers/tela.h"
#include "headers/movimenta.h"
#include "lib/personagem.c"

//Declaração de funcões
void gameScreen();
void menuScreen(Texture2D background, Rectangle botoesMenu[], char *textButtonsMenu[]);
void settingsScreen(Texture2D background, Rectangle botoesSettings[], char *textButtonsSettings[]);

int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(tela.width, tela.height, "TESTE");
    telaCheia();
    SetWindowMinSize(800,600);

    //BACKGROUND
    Image wallpaper = LoadImage("resources/wallpaper.png");
    //ImageResize(&wallpaper, tela.width, tela.height);  
    Texture2D texture = LoadTextureFromImage(wallpaper);
    UnloadImage(wallpaper);


    //BOTÕES DA TELA DE MENU 
    Rectangle botoesMenu[4];
    for (int i = 0; i < 4; i++)
    {
        botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
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
        botoesSettings[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
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
        if(IsWindowResized() || Is_Fullscreen){
            updateSizeTela();
            for (int i = 0; i < 4; i++)
            {
                botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
                if(i < 3) botoesSettings[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
            }
        }

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
                    telaCheia();
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
            //INICIAR
            if (CheckCollisionPointRec(GetMousePosition(), botoesMenu[0]))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    currentScreen = 1;
                    
                }
            }
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

        DrawTextureEx(background, (Vector2){0,0}, 0, tela.width/background.width,WHITE);

        
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

        DrawTextureEx(background, (Vector2){0,0}, 0, tela.width/background.width,WHITE);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoesSettings[i], CheckCollisionPointRec(GetMousePosition(), botoesSettings[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoesSettings[i].x-5, (int) botoesSettings[i].y-5, (int) botoesSettings[i].width+10, (int) botoesSettings[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoesSettings[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsSettings[i], (int)( botoesSettings[i].x + botoesSettings[i].width/2 - MeasureText(textButtonsSettings[i], 20)/2), (int) botoesSettings[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void gameScreen() {
    Rectangle mapa[6] = {
        -67, -54, 1390, 1310,
        71, -22, 194, 61,
        165, -185, 99, 164,
        263, -183, 315, 77,
        373, -110, 54, 178,
        251, 66, 177, 57,
    };
    Personagem xala = personagemConstructor();
    Vector2 posicao;
    Camera2D cam;
    cam.zoom = 4;
    cam.rotation = 0;
    xala.positionX = 0;
    xala.positionY = 0;

    while(!WindowShouldClose()){
        move(&posicao);

        cam.target = (Vector2){xala.positionX, xala.positionY};
        cam.offset = (Vector2){tela.width/2, tela.height/2};
        for( int i= 0; i < 6; i++){
            if(CheckCollisionRecs(xala.linhaColisaoCima,mapa[i])){
                if(IsKeyDown(KEY_W)) xala.positionY--;
            }
            if(CheckCollisionRecs(xala.linhaColisaoBaixo,mapa[i])){
                if(IsKeyDown(KEY_S)) xala.positionY++;
            }
            if(CheckCollisionRecs(xala.linhaColisaoEsquerda,mapa[i])){
                if(IsKeyDown(KEY_A)) xala.positionX--;
            }
            if(CheckCollisionRecs(xala.linhaColisaoDireita,mapa[i])){
                if(IsKeyDown(KEY_D)) xala.positionX += 10;
            }
        }
        if(IsKeyDown(KEY_DOWN))cam.zoom -= 0.1;
        BeginDrawing();
            ClearBackground(GRAY);
            BeginMode2D(cam);
                for( int i = 0; i < 6; i++){
                    DrawRectanglePro(mapa[i],(Vector2){0,0},0,BLACK);
                }
                DrawRectangleRec(xala.linhaColisaoCima,YELLOW);
                DrawRectangleRec(xala.linhaColisaoEsquerda,YELLOW);
                DrawRectangleRec(xala.linhaColisaoDireita,YELLOW);
                DrawRectangleRec(xala.linhaColisaoBaixo,YELLOW);

                DrawTextureEx(xala.sprite, (Vector2){xala.positionX, xala.positionY}, 0, 0.03,WHITE);
            EndMode2D();
        EndDrawing();
    }
    
    

}