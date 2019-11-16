#include <string.h>
#include <raylib.h>

#include "lib/jogo.h"
#include "lib/define.h"
#include "lib/som.h"
#include "lib/background.h"
#include "lib/tela.h"
#include "lib/personagem.h"
#include "lib/acao.h"
#include "lib/movimenta.h"
#include "telas/menu/menu.c"

#include "telas/menu/configuracao.c"
#include "telas/menu/resolucao.c"
#include "telas/fases/fase1.c"
#include "telas/fases/fase_3.c"

int main(){

    InitWindow(tela.width, tela.height, "TESTE");
    telaCheia();

    //BACKGROUND
    setImageBackground("resources/images/wallpaper.png");
    updateBackground();
    
    //AUDIO
    InitAudioDevice();
    setMusic("resources/soundtrack/epic.ogg");
    setSomBotao("resources/fx/setting click.wav");
    PlayMusicStream(music);
    
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

        while(telaAtual == TELA_RESOLUCAO) {
            telaResolucao();
        }

        if(telaAtual == TELA_FASE1) {
            fase1();
        }

        while(telaAtual == TELA_FASE_3) {
            fase_3();
        }
    }
    
    UnloadTexture(background);
    
    UnloadSound(somBotao);
    UnloadMusicStream(music);
    
    CloseAudioDevice();
    CloseWindow(); 

    return 0;
}