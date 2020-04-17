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
    InitAudioDevice();
    
    // LOADING FILES
    loadGame_musics();
    loadGame_sounds();    
    loadGame_textures();
    shader = LoadShader(0,"resources/shaders/blur.fs");
    font = LoadFont("resources/font/custom_alagard.png");

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
