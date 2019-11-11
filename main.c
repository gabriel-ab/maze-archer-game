#include <string.h>
#include <raylib.h>
#include "lib/constants.h"
#include "lib/tela.h"

bool *jogo_rodando = true;

/*
VARIÁVEL QUE DETERMINA A TELA ATUAL
0 - MENU
1 - JOGO
2 - SETTINGS
3 - TELA DE RESOLUÇÃO
*/
int currentScreen = 0;


Image backgroundImage;
Texture2D backgroundTexture;

int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width, tela.height, "TESTE");
    telaCheia();
    

    //BACKGROUND
    backgroundImage = LoadImage("resources/wallpaper.png");
    ImageResize(&backgroundImage, tela.width, tela.height);  
    backgroundTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
    
   
    //AUDIO
    InitAudioDevice();
    
    Music menuIntro = LoadMusicStream("resources/soundtrack/epic.ogg");
    
    Sound setting_btnfx = LoadSound("resources/fx/setting click.wav");
    //Sound play_btnfx = LoadSound("resources/fx/start click.wav");
    
    PlayMusicStream(menuIntro);
    
    //BOTÕES DA TELA DE MENU
    
    const char *textButtonsMenu[] = {
        "START",
        "LOAD",
        "SETTINGS",
        "QUIT"
    };

    Rectangle botoesMenu[4];

    for (int i = 0; i < 4; i++)
    {
        botoesMenu[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }


    //BOTÕES DA TELA DE CONFIGURAÇÃO

    char *textButtonsConfiguracao[] = {
        "RESOLUÇÃO",
        "MUTE: OFF",
        "BACK",
    };

    Rectangle botoesConfiguracao[3];

    for (int i = 0; i < 3; i++)
    {
        botoesConfiguracao[i] = (Rectangle) {tela.width/2 - 100, tela.height/8*i + tela.height/2, 200, 50};
    }

    //BOTÕES DE RESOLUÇÃO DE TELA

    char *textButtonsResolucao[] = {
        "1920x1080",
        "1280x720",
        "800x600",
        "640x480",
        "VOLTAR"
    };

    Rectangle botoesResolucao[5];

    for (int i = 0; i < 4; i++)
    {
        botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
    }

    botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};

    SetTargetFPS(60);
    
    
    while (jogo_rodando  && !WindowShouldClose()) 
    {
        UpdateMusicStream(menuIntro);
        
        if (currentScreen == 1) 
        {
            gameScreen();
        }
        else if (currentScreen == 2)
        {
            
            logicaBotoesConfiguracao(botoesConfiguracao, setting_btnfx);
            telaConfiguracao(backgroundTexture, botoesConfiguracao, textButtonsConfiguracao);
            

        } else if(currentScreen == 3) 
        {
            
            logicaBotoesResolucao(botoesResolucao, setting_btnfx);
            telaResolucao(backgroundTexture, botoesResolucao, textButtonsResolucao);

        }else if(currentScreen == -1)
        {
            if(!IsSoundPlaying(setting_btnfx)){
                jogo_rodando = false;
            }
            
            
        } else
        {
            
            logicaBotoesMenu(botoesMenu, setting_btnfx);
            menuScreen(backgroundTexture, botoesMenu, textButtonsMenu);
        }
    }
    
    
    UnloadTexture(backgroundTexture);
    
    UnloadSound(setting_btnfx);
    UnloadMusicStream(menuIntro);
    //UnloadSound(play_btnfx);
    
    
    CloseAudioDevice();
    CloseWindow(); 
    return 0;
}

//TELA DE MENU
void logicaBotoesMenu(Rectangle botoesMenu[], Sound setting_btnfx) {
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoesMenu[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            currentScreen = 2;
            
        }
    }

    //SAIR DO JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoesMenu[3]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            currentScreen = -1;
            
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
void logicaBotoesConfiguracao(Rectangle botoesConfiguracao[], Sound setting_btnfx) {

    // IR PARA TELA DE RESOLUÇÃO
    if(CheckCollisionPointRec(GetMousePosition(), botoesConfiguracao[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            currentScreen = 3;
        }
    }

    //VOLTAR PARA O MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoesConfiguracao[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
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

void logicaBotoesResolucao(Rectangle botoesResolucao[], Sound setting_btnfx) {

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            tela.width = 1920;
            tela.height = 1080;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            for (int i = 0; i < 4; i++)
            {
                botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
            }
            botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};
        }
    }
      

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[1])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            tela.width = 1280;
            tela.height = 720;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            for (int i = 0; i < 4; i++)
            {
                botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
            }
            botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[2])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            tela.width = 800;
            tela.height = 600;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
            for (int i = 0; i < 4; i++)
            {
                botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
            }
            botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botoesResolucao[3])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(setting_btnfx);
            tela.width = 640;
            tela.height = 480;
            SetWindowSize(tela.width, tela.height);
            SetWindowPosition(tela.x, tela.y);
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
            PlaySound(setting_btnfx);
            currentScreen = 2;
        }
    } 
}
void telaResolucao(Texture2D background, Rectangle botoesResolucao[], char *textButtonsResolucao[]) {
    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        for (int i = 0; i < 5; i++)
        {
            DrawRectangleRec(botoesResolucao[i], CheckCollisionPointRec(GetMousePosition(), botoesResolucao[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoesResolucao[i].x-5, (int) botoesResolucao[i].y-5, (int) botoesResolucao[i].width+10, (int) botoesResolucao[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoesResolucao[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtonsResolucao[i], (int)( botoesResolucao[i].x + botoesResolucao[i].width/2 - MeasureText(textButtonsResolucao[i], 20)/2), (int) botoesResolucao[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

/*void temporizador(int tempo){
   static int timer = 0;
   
   if(timer == tempo){

   }else{
       timer += 1;
   }

}*/

void gameScreen() {}

