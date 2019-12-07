#include "som.h"

void setMusic(char* musicPath) {
    music = LoadMusicStream(musicPath);
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
    
    if(fxNumber == 4){
        PlaySound(arco);
    }
    
}
//Musica de fundo
void playMusic(int musicNumber){
    if(musicNumber == 1){
        UpdateMusicStream(music);
    }
}