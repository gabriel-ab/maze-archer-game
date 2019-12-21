#include "som.h"
//ADICIONA A MUSICA DO MENU PRINCIPAL
void setMusic(char* musicPath) {
    music = LoadMusicStream(musicPath);
}
//MUSICAS DE FUNDO DOS MAPAS
void setMusicBg(char* cave, char* winter, char* lava){
    caveBG = LoadMusicStream(cave);
    winterBG = LoadMusicStream(winter);
    lavaBG = LoadMusicStream(lava);
}

//FUNÇÃO QUE INICIALIZA AS MUSICAS DO JOGO
void initMusic(){
    PlayMusicStream(caveBG);
    PlayMusicStream(winterBG);
    PlayMusicStream(lavaBG);
    PlayMusicStream(music);
}

//FUNÇAO PRA ADICIONAR SFX DIVERSOS
void setFx(char* somBotaoPath, char* gameOver, char* pickup) {
    somBotao = LoadSound(somBotaoPath);
    gameover = LoadSound(gameOver);
    item = LoadSound(pickup);
}

// FUNÇAO PRA ADICIONAR O SOM DO ARCO E FLECHA
void setTiroFx(char* flechaPath, char* arcoPath){
    flecha = LoadSound(flechaPath);
    arco = LoadSound(arcoPath);
}

//FUNÇAO PARA ADICIONAR SOM DE ARMADILHAS
void setTrapFx(char* armadilha, char* fogo){
    lanca = LoadSound(armadilha);
    queima = LoadSound(fogo);
    
}

//FUNÇAO PARA ADICIONAR SOM DO HIT
void setHitFx(char* hit){
    acerto = LoadSound(hit);
}

//FUNÇAO PARA ADICIONAR O SOM DO PASSO
void setFootStep(char* footstepFx){
    passo = LoadSound(footstepFx);
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
        PlayMusicStream(music);
        UpdateMusicStream(music);
    }
    //SOM DE FUNDO CAVERNA
    if(musicNumber == 2){
        SetMusicVolume(caveBG, 0.4);
        UpdateMusicStream(caveBG);
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
    UnloadMusicStream(music);
    UnloadMusicStream(caveBG);
    UnloadMusicStream(winterBG);
    UnloadMusicStream(lavaBG);
    
}
