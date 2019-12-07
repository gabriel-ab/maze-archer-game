#include <string.h>
#include <raylib.h>

#include "lib/define.h"
#include "lib/som.c"
#include "lib/tela.c"
#include "lib/personagem.c"
#include "lib/projetil.c"
#include "lib/movimenta.c"

#include "telas/menu/menu.c"
#include "telas/menu/configuracao.c"
#include "telas/fases/fase1.c"
#include "telas/fases/fase_3.c"
#include "telas/fases/fase_4.c"
#include "telas/telaFracasso.c"
#include "telas/telaPausa.c"


int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(tela.width, tela.height, "TESTE");
    SetWindowMinSize(800,500);
    
    telaCheia();
    
    //Apagando tela no carregamento do jogo (A FAZER)
    // BeginDrawing();
        // ClearBackground(BLACK);
    // EndDrawing();
    
    //BACKGROUND
    setPathImageBackground("resources/images/wallpaper.png");
    updateBackground();
    
    //AUDIO
    InitAudioDevice();
    setMusic("resources/soundtrack/epic.ogg");
    setSomBotao("resources/fx/setting click.wav");
    PlayMusicStream(music);

    //HUD
    setTexture(&vida, "resources/images/heart pixel art 254x254.png", 30, 30);
    setTexture(&arrow, "resources/images/Arrow.png", 30, 20);
    
    SetTargetFPS(60);

    telaAtual = TELA_MENU;

    while (jogo_rodando) 
    {

        while(telaAtual == TELA_MENU && jogo_rodando) {
            telaMenu();
        }

        while(telaAtual == TELA_CONFIG) {
            telaConfiguracao();
        }

        if(telaAtual == TELA_FRACASSO) {
            telaFracasso();
        }

        if(telaAtual == TELA_FASE_1) {
            fase1();
        }

        while(telaAtual == TELA_FASE_3) {
            fase_3();
        }

        while(telaAtual == TELA_FASE_4) {
            fase_4();
        }
    }
    
    UnloadTexture(background);
    
    UnloadSound(somBotao);
    UnloadMusicStream(music);
    
    CloseAudioDevice();
    CloseWindow(); 

    return 0;
}
