#include <raylib.h>
#include <stdio.h>

#include "include/define.h"
#include "include/som.h"
#include "include/tela.h"
#include "include/personagem.h"
#include "include/projetil.h"
#include "include/fisica.h"
#include "include/data.h"
#include "include/textura.h"
#include "include/draw.h"
#include "include/itens.h"

int main(){
    TEMPO = 0;
    larguraAnterior = GetScreenWidth();
    alturaAnterior = GetScreenHeight();
    telaAtual = 0;
    telaAnterior = 0;
    jogo_rodando = true;
    tempo_invunerabilidade = 2;
    vida_no_save = 3;
    flechas_no_save = 2;
    projetil_atual = 0;
    segmentos_xala[0] = (Segmento){0, 0, 3};
    segmentos_xala[1] = (Segmento){1, 0, 3};

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1000, 600, "Untitle Dungeon Game");
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
