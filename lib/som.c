#include "som.h"

void setMusic(char* musicPath, char* cave) {
    music = LoadMusicStream(musicPath);
    caveBG = LoadMusicStream(cave);
}

void setSomBotao(char* somBotaoPath) {
    somBotao = LoadSound(somBotaoPath);
}


void setTiroFx(char* flechaPath, char* arcoPath){
    flecha = LoadSound(flechaPath);
    arco = LoadSound(arcoPath);
}

//sons de efeitos
void playFx(int fxNumber){
    //AQUI O SOM E O BOTÃO É ACIONADO AO MESMO TEMPO, INDEPENDENTE SE ELE ACABOU DE TOCAR
    if(fxNumber == 1){
        PlaySound(somBotao);
    }
    
    //ISSO É PARA O SOM TOCAR ATÉ ACABAR, SÓ DEPOIS QUE ELE ACABAR O BOTÃO VAI ACIONADO
    if(fxNumber == 2){
        PlaySound(somBotao);
        while(IsSoundPlaying(somBotao)){}
    }
    
    //SOM DA FLECHA
    if(fxNumber == 3){
        PlaySound(flecha);
    }
    //SOM ARCO
    if(fxNumber == 4){
        PlaySound(arco);
    }
    
}
//Musica de fundo
void playMusic(int musicNumber){
    //MUSICA MENU
    if(musicNumber == 1){
        PlayMusicStream(music);
        UpdateMusicStream(music);
    }
    //SOM DE FUNDO CAVERNA
    if(musicNumber == 2){
        SetMusicVolume(caveBG, 0.3);
        UpdateMusicStream(caveBG);
    }
}

void checkClickBow(int quantidadeFlechas){
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && quantidadeFlechas > 0){
            playFx(4);
        }
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && quantidadeFlechas > 0){
            StopSound(arco);
            playFx(3);
            
        }
        
    
}