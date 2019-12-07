#include "som.h"

void setMusic(char* musicPath) {
    music = LoadMusicStream(musicPath);
}

void setSomBotao(char* somBotaoPath) {
    somBotao = LoadSound(somBotaoPath);
}


void setTiroFx(char* flechaPath){
    flecha = LoadSound(flechaPath);
}

//sons de efeitos
void playFx(int fxNumber){
    if(fxNumber == 1){
        PlaySound(somBotao);
    }
    
    if(fxNumber == 2){
        PlaySound(somBotao);
        while(IsSoundPlaying(somBotao)){}
    }
    
    if(fxNumber == 3){
        PlaySound(flecha);
    }
    
}
//Musica de fundo
void playMusic(int musicNumber){
    if(musicNumber == 1){
        UpdateMusicStream(music);
    }
}