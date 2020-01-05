#include "som.h"
//ADICIONA A MUSICA DO MENU PRINCIPAL
void setMusic(char* musicPath) {
    music = LoadMusicStream(musicPath);
}
//MUSICAS DE FUNDO DOS MAPAS
void setMusicBg(char* cave, char* winter, char* lava, char* bossMusic){
    caveBG = LoadMusicStream(cave);
    winterBG = LoadMusicStream(winter);
    lavaBG = LoadMusicStream(lava);
    bossBG = LoadMusicStream(bossMusic);
}

//FUNÇÃO QUE INICIALIZA AS MUSICAS DO JOGO
void initMusic(){
    PlayMusicStream(caveBG);
    PlayMusicStream(winterBG);
    PlayMusicStream(lavaBG);
    PlayMusicStream(music);
    PlayMusicStream(bossBG);
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
void setHitFx(char* hit, char* monstro, char* chefe){
    acerto = LoadSound(hit);
    acertoMonstro = LoadSound(monstro);
    bossAttack = LoadSound(chefe);
}

//FUNÇAO PARA ADICIONAR O SOM DO PASSO
void setFootStep(char* footstepFx){
    passo = LoadSound(footstepFx);
}

//EFEITOS SONOROS
void playFx(int fxNumber){
    //AQUI O SOM E O BOTÃO É ACIONADO AO MESMO TEMPO, INDEPENDENTE SE ELE ACABOU DE TOCAR
    if(fxNumber == 1){
        //SetSoundVolume(somBotao, 0.2);
        PlaySound(somBotao);
    }
    
    //ISSO É PARA O SOM TOCAR ATÉ ACABAR, SÓ DEPOIS QUE ELE ACABAR O BOTÃO VAI ACIONADO
    if(fxNumber == 2){
        PlaySound(somBotao);
        while(IsSoundPlaying(somBotao)){}
    }
    
    //SOM DA FLECHA
    if(fxNumber == 3){
        SetSoundVolume(flecha, 0.6);
        PlaySound(flecha);
    }
    //SOM ARCO
    if(fxNumber == 4){
        //SetSoundVolume(arco, 0.8);
        PlaySound(arco);
    }
    //SOM DO HIT
    if(fxNumber == 5){
        SetSoundVolume(acerto, 0.8);
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
    //SOM AO PEGAR IDEM DE VIDA
    if(fxNumber == 9){
        PlaySound(item);
    }
    //HIT QUANDO O MONSTRO DÁ DANO
    if(fxNumber == 10){
        //SetSoundVolume(acertoMonstro, 0.8);
        PlaySound(acertoMonstro);
    }
    if(fxNumber == 11){
        //SetSoundVolume(bossAttack, 0.8);
        PlaySound(bossAttack);
    }
    
    
}
//FAZER A MUSICA DE FUNDO TOCAR
void playMusic(int musicNumber){
    //MUSICA MENU
    if(musicNumber == 1){
        
        PlayMusicStream(music);
        UpdateMusicStream(music);
    }
    //SOM DE FUNDO FASE1
    if(musicNumber == 2){
        SetMusicVolume(caveBG, 0.1);
        UpdateMusicStream(caveBG);
    }
    //SOM DE FUNDO FASE2
    if(musicNumber == 3){
        SetMusicVolume(winterBG, 0.1);
        UpdateMusicStream(winterBG);
    }
    //SOM DE FUNDO FASE3
    if(musicNumber == 4){
        SetMusicVolume(lavaBG, 0.1);
        UpdateMusicStream(lavaBG);
    }
    //SOM DA BOSSFIGHT
    if(musicNumber == 5){
        SetMusicVolume(bossBG, 0.1);
        UpdateMusicStream(bossBG);
    }
    
}

//FUNÇÃO PARA OS PASSOS DA PERSONAGEM... TALVEZ AINDA FALTA UNS AJUSTES VOU ALMOÇAR
void footStep(){
    SetSoundVolume(passo, 0.5);
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

void stopMusic(int musicNumber){
    //SOM DE FUNDO FASE1
    if(musicNumber == 1){
       StopMusicStream(caveBG);
       PlayMusicStream(caveBG);
    }
    //SOM DE FUNDO FASE2
    if(musicNumber == 2){
        StopMusicStream(winterBG);
        PlayMusicStream(winterBG);
    }
    //SOM DE FUNDO FASE3
    if(musicNumber == 3){
        StopMusicStream(lavaBG);
        PlayMusicStream(lavaBG);
    }
    //SOM DA BOSSFIGHT
    if(musicNumber == 4){
        StopMusicStream(bossBG);
        PlayMusicStream(bossBG);
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
    UnloadSound(item);
    UnloadSound(acertoMonstro);
    UnloadSound(bossAttack);
    
    //DESCARREGAR MUSICAS
    UnloadMusicStream(music);
    UnloadMusicStream(caveBG);
    UnloadMusicStream(winterBG);
    UnloadMusicStream(lavaBG);
    UnloadMusicStream(bossBG);
    
}
