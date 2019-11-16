#include "som.h"

void setMusic(char* musicPath) {
    music = LoadMusicStream(musicPath);
}

void setSomBotao(char* somBotaoPath) {
    somBotao = LoadSound(somBotaoPath);
}