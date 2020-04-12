#include <string.h>
#include <raylib.h>
#include <stdio.h>

#include "inc/define.h"
#include "inc/som.h"
#include "inc/tela.h"
#include "inc/personagem.h"
#include "inc/projetil.h"
#include "inc/fisica.h"
#include "inc/data.h"
#include "inc/textura.h"
#include "inc/draw.h"
#include "inc/itens.h"
#include "inc/botoes.h"

int main(){
    TEMPO = 0;
    tela = (Rectangle){100, 100, LARGURA_TELA, ALTURA_TELA};
    larguraAnterior = LARGURA_TELA;
    alturaAnterior = ALTURA_TELA;  
    telaAtual = 0;
    telaAnterior = 0;
    is_fullscreen = false;
    jogo_rodando = true;
    tempo_invunerabilidade = 2;
    vida_no_save = 3;
    flechas_no_save = 2;
    projetil_atual = 0;
    segmentos_xala[0] = (Segmento){0, 0, 3};
    segmentos_xala[1] = (Segmento){1, 0, 3};

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
    flechaTexture = LoadTexture("resources/images/flecha.png");
    xalaTexture = LoadTexture("resources/images/personagem.png");
    inimigoTexture = LoadTexture("resources/images/inimigo.png");
    //HUD
    vidaTexture = LoadTexture("resources/images/hud_vida.png");
    arrowTexture = LoadTexture("resources/images/hud_flecha.png");
    bombaTexture = LoadTexture("resources/images/bomba.png");
    portalTexture = LoadTexture("resources/images/portal.png");
    
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
            /* case TELA_FASE_1:       fase_1(); break;
            case TELA_FASE_2:       fase_2(); break;
            case TELA_FASE_3:       fase_3(); break; */
            case TELA_FASE_CUSTOM:  fase_custom(); break;
            /* case BOSS_FIGHT:        boss_fight(); break; */
        }
    }
    
    UnloadTexture(background);
    
    unloadAllSound();
    
    CloseAudioDevice();
    CloseWindow(); 

    return 0;
}
