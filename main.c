#include <string.h>
#include <raylib.h>
#include "lib/personagem.h"
#include "lib/tela.h"
#include "telas/menu/menu.c"
#include "telas/menu/configuracao.c"
#include "telas/menu/resolucao.c"
#include "telas/fases/fase1.c"

bool jogo_rodando = true;

/*
VARIÁVEL QUE DETERMINA A TELA ATUAL
0 - MENU
1 - JOGO
2 - SETTINGS
3 - TELA DE RESOLUÇÃO
*/
int telaAtual = 0;

int main(){

    InitWindow(tela.width, tela.height, "TESTE");
    telaCheia();

    personagemConstructor();
    
    //BACKGROUND
    Image backgroundImage = LoadImage("resources/images/wallpaper.png");
    ImageResize(&backgroundImage, tela.width, tela.height);  
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
    
    //AUDIO
    InitAudioDevice();
    
    Sound botaofx = LoadSound("resources/sounds/test.wav");
    bool btnaction = false;
    
    
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
        "BACK"
    };

    Rectangle botoesResolucao[5];

    for (int i = 0; i < 4; i++)
    {
        botoesResolucao[i] = (Rectangle) {tela.width/2 - 100, 50*i + tela.height/2, 200, 50};
    }

    botoesResolucao[4] = (Rectangle) {tela.width/2 - 100, tela.height/8*3 + tela.height/2, 200, 50};

    SetTargetFPS(60);

    while (jogo_rodando) 
    {

        while(telaAtual == 0 && jogo_rodando) {
            logicaBotoesMenu(botoesMenu, &telaAtual, botaofx, &jogo_rodando);
            menuScreen(&backgroundTexture, botoesMenu, textButtonsMenu);
        }

        while(telaAtual == 1 && jogo_rodando) {
            fase1();
        }

        while(telaAtual == 2 && jogo_rodando) {
            logicaBotoesConfiguracao(botoesConfiguracao, &telaAtual);
            telaConfiguracao(&backgroundTexture, botoesConfiguracao, textButtonsConfiguracao);
        }

        while(telaAtual == 3 && jogo_rodando) {
            logicaBotoesResolucao(botoesResolucao, botoesConfiguracao, botoesMenu, &telaAtual, &backgroundTexture);
            telaResolucao(&backgroundTexture, botoesResolucao, textButtonsResolucao);
        }
    }
    
    
    UnloadTexture(backgroundTexture);
    UnloadSound(botaofx);
    
    CloseAudioDevice();
    CloseWindow(); 

    return 0;
}

