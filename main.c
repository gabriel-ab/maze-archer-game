#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "lib/define.h"
#include "lib/som.c"
#include "lib/tela.c"
#include "lib/personagem.c"
#include "lib/projetil.c"
#include "lib/movimenta.c"
#include "lib/data.c"
#include "lib/textura.c"
#include "lib/draw.c"
#include "lib/itens.c"

#include "telas/fases/fase_custom.c"
#include "telas/menu/selecao_mapa.c"
#include "telas/menu/menu.c"
#include "telas/menu/configuracao.c"
#include "telas/fases/fase_1.c"
#include "telas/fases/fase_2.c"
#include "telas/fases/fase_3.c"
#include "telas/fases/boss_fight.c"
#include "telas/telaFracasso.c"
#include "telas/telaPausa.c"

int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(tela.width, tela.height, "Untitle Dungeon Game");
    
    //BACKGROUND
    background = LoadTexture("resources/images/wallpaper.png");
    
    //AUDIO
    InitAudioDevice();
    setMusic("resources/soundtrack/epic.ogg");
    setMusicBg("resources/soundtrack/cave_loop.ogg", "resources/soundtrack/winter_loop.ogg", "resources/soundtrack/lava_loop.ogg");
    setFx("resources/fx/setting click.wav", "resources/fx/you_died.wav", "resources/fx/pickup.wav");
    setTiroFx("resources/fx/arrow.wav", "resources/fx/arco.wav");
    setFootStep("resources/fx/footstep_dirty.wav");
    setHitFx("resources/fx/hit.wav");
    setTrapFx("resources/fx/trap.wav", "resources/fx/burn.wav" );
    initMusic();
    
    //TEXTURE
    setTextureCropped(&flechasTexture, "resources/images/flechas.png", (Rectangle){0,0,64,64});
    xalaTexture = LoadTexture("resources/images/personagem.png");
    inimigoTexture = LoadTexture("resources/images/inimigo.png");
    //HUD
    vidaTexture = LoadTexture("resources/images/hud_vida.png");
    setTexture(&arrowTexture, "resources/images/hud_flecha.png", 50, 50);
    bombaTexture = LoadTexture("resources/images/bomba.png");
    
    SetTargetFPS(60);
    SetExitKey(0);

    telaAtual = TELA_MENU;

    while (jogo_rodando & !WindowShouldClose()) 
    {
        switch (telaAtual)
        {
            case TELA_MENU:         telaMenu(); break;
            case TELA_CONFIG:       telaConfiguracao(); break;
            case TELA_FRACASSO:     telaFracasso(); break;
            case TELA_SEL_MAPA:     selecao_de_mapa(); break;
            case TELA_FASE_1:       fase_1(); break;
            case TELA_FASE_2:       fase_2(); break;
            case TELA_FASE_3:       fase_3(); break;
            case TELA_FASE_CUSTOM:  fase_custom(); break;
            case BOSS_FIGHT:        boss_fight(); break;
        }
    }
    
    UnloadTexture(background);
    
    unloadAllSound();
    
    CloseAudioDevice();
    CloseWindow(); 

    return 0;
}
