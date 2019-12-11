#include <string.h>
#include <raylib.h>
#include<stdio.h>

#include "lib/define.h"
#include "lib/som.c"
#include "lib/tela.c"
#include "lib/personagem.c"
#include "lib/projetil.c"
#include "lib/movimenta.c"

#include "telas/menu/menu.c"
#include "telas/menu/configuracao.c"
#include "telas/fases/fase1.c"
#include "telas/fases/fase_2.c"
#include "telas/fases/fase_3.c"
#include "telas/fases/fase_4.c"
#include "telas/telaFracasso.c"
#include "telas/telaPausa.c"


int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(tela.width, tela.height, "Untitle Dungeon Game");
    SetWindowMinSize(800,500);
    
    telaCheia();
    
    //BACKGROUND
    setPathImageBackground("resources/images/wallpaper.png");
    updateBackground();
    
    //AUDIO
    InitAudioDevice();
    setMusic("resources/soundtrack/epic.ogg");
    setMusicBg("resources/soundtrack/cave_loop.ogg", "resources/soundtrack/winter_loop.ogg", "resources/soundtrack/forest_loop.ogg");
    setFx("resources/fx/setting click.wav", "resources/fx/you_died.wav");
    setTiroFx("resources/fx/arrow.wav", "resources/fx/arco.wav");
    setFootStep("resources/fx/footstep_dirty.wav");
    setHitFx("resources/fx/hit.wav");
    setTrapFx("resources/fx/trap.wav", "resources/fx/burn.wav" );
    initMusic();
    

    //HUD
    setTexture(&vidaTexture, "resources/images/heart pixel art 254x254.png", 30, 30);
    setTexture(&arrowTexture, "resources/images/Arrow.png", 30, 20);
    
    SetTargetFPS(60);

    telaAtual = TELA_MENU;

    while (jogo_rodando) 
    {
        
        while(telaAtual == TELA_MENU && jogo_rodando) {
            telaMenu();
            playMusic(1);
        }

        while(telaAtual == TELA_CONFIG) 
        {
            telaConfiguracao();
            playMusic(1);
        }

        if(telaAtual == TELA_FRACASSO) {
            telaFracasso();
        }
        
        if(telaAtual == TELA_FASE_1) {
            fase_1();
        }
        
        while(telaAtual == TELA_FASE_2) {
            fase_2();
        }

        while(telaAtual == TELA_FASE_3) {
            fase_3();
        }

        while(telaAtual == TELA_FASE_4) {
            fase_4();
        }
    }
    
    UnloadTexture(background);
    
    unloadAllSound();
    
    CloseAudioDevice();
    CloseWindow(); 

    return 0;
}
