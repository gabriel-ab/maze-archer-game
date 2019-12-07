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
#include "telas/telaFracasso.c"


int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width, tela.height, "TESTE");
    telaCheia();
    

    //BACKGROUND
    setImageBackground("resources/images/wallpaper.png");
    updateBackground();
    
    //AUDIO
    InitAudioDevice();
    setMusic("resources/soundtrack/epic.ogg");
    setSomBotao("resources/fx/setting click.wav");
    setTiroFx("resources/fx/arrow.wav", "resources/fx/arco.wav");
    PlayMusicStream(music);
    
    SetTargetFPS(60);

    telaAtual = TELA_MENU;

    while (jogo_rodando) 
    {
        
        while(telaAtual == TELA_MENU && jogo_rodando) {
            telaMenu();
            playMusic(1);
          
        }

        while(telaAtual == TELA_CONFIG) {
            telaConfiguracao();
            playMusic(1);
            
        }

        if(telaAtual == TELA_FRACASSO) {
            telaFracasso();
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
