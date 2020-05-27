#include "../include/som.h"

//FUNÇÃO QUE INICIALIZA AS MUSICAS DO JOGO
void loadGame_musics(){
    menuMusic = LoadMusicStream("resources/soundtrack/epic.ogg");
    caveMusic = LoadMusicStream("resources/soundtrack/cave_loop.ogg");
    winterBG = LoadMusicStream("resources/soundtrack/winter_loop.ogg");
    lavaBG = LoadMusicStream("resources/soundtrack/lava_loop.ogg");

    
    // PlayMusicStream(winterBG);
    // PlayMusicStream(lavaBG);
    
}

void loadGame_sounds(){
    somBotao = LoadSound("resources/fx/setting click.wav");
    SetSoundVolume(somBotao, 0.2);
    gameover = LoadSound("resources/fx/you_died.wav");
    item = LoadSound("resources/fx/pickup.wav");
    flecha = LoadSound("resources/fx/arrow.wav");
    arco = LoadSound("resources/fx/arco.wav");
    lanca = LoadSound("resources/fx/trap.wav");
    queima = LoadSound("resources/fx/burn.wav");
    passo = LoadSound("resources/fx/footstep_dirty.wav");
    acerto = LoadSound("resources/fx/hit.wav");
}

//EFEITOS SONOROS
void playFx(int fxNumber){
    //AQUI O SOM E O BOTÃO É ACIONADO AO MESMO TEMPO, INDEPENDENTE SE ELE ACABOU DE TOCAR
    if(fxNumber == 1){
        SetSoundVolume(somBotao, 0.2);
        PlaySound(somBotao);
    }
    
    //ISSO É PARA O SOM TOCAR ATÉ ACABAR, SÓ DEPOIS QUE ELE ACABAR O BOTÃO VAI ACIONADO
    if(fxNumber == 2){
        PlaySound(somBotao);
        while(IsSoundPlaying(somBotao)){}
    }
    
    //SOM DA FLECHA
    if(fxNumber == 3){
        SetSoundVolume(flecha, 0.8);
        PlaySound(flecha);
    }
    //SOM ARCO
    if(fxNumber == 4){
        SetSoundVolume(arco, 0.8);
        PlaySound(arco);
    }
    //SOM DO HIT
    if(fxNumber == 5){
        SetSoundVolume(acerto, 0.5);
        PlaySound(acerto);
    }
    
    //SOM DA ARMADILHA LANÇA
    if(fxNumber == 6){
        PlaySound(lanca);
    }
    
    //SOM FIM DE JOGO
    if(fxNumber == 7){
        PlaySound(gameover);
    }
    
    //SOM DA ARMADILHA DE LAVA
    if(fxNumber == 8){
        PlaySound(queima);
    }
    
    if(fxNumber == 9){
        PlaySound(item);
    }
    
    
}
//FAZER A MUSICA DE FUNDO TOCAR
void playMusic(int musicNumber){
    //MUSICA MENU
    if(musicNumber == 1){
        PlayMusicStream(menuMusic);
        UpdateMusicStream(menuMusic);
    }
    //SOM DE FUNDO CAVERNA
    if(musicNumber == 2){
        SetMusicVolume(caveMusic, 0.4);
        UpdateMusicStream(caveMusic);
    }
    //SOM DE FUNDO NEVE
    if(musicNumber == 3){
        SetMusicVolume(winterBG, 0.5);
        UpdateMusicStream(winterBG);
    }
    //SOM DE FUNDO LAVA
    if(musicNumber == 4){
        SetMusicVolume(lavaBG, 0.7);
        UpdateMusicStream(lavaBG);
    }
}

//FUNÇÃO PARA OS PASSOS DA PERSONAGEM... TALVEZ AINDA FALTA UNS AJUSTES VOU ALMOÇAR
void footStep(){
    SetSoundVolume(passo, 0.3);
    if(!IsSoundPlaying(passo)){
        PlaySound(passo);
    }
}

//FUNÇÃO QUE CHECA SE TEM FLECHAS AINDA PARA SEREM ATIRADAS, SE SIM ELE ATIVA O SOM AO CLIQUE DO MOUSE
void checkClickBow(){
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            playFx(4);
        }
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && projetil_atual > -1){
            StopSound(arco);
            playFx(3);
        } 
}

void unloadAllSound(){
    //DESCARREGAR SFX
    UnloadSound(somBotao);
    UnloadSound(flecha);
    UnloadSound(arco);
    UnloadSound(passo);
    UnloadSound(acerto);
    UnloadSound(lanca);
    UnloadSound(gameover);
    UnloadSound(queima);
    
    //DESCARREGAR MUSICAS
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(caveMusic);
    UnloadMusicStream(winterBG);
    UnloadMusicStream(lavaBG);
    
}
