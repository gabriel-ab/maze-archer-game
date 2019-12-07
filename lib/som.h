#ifndef SOM_H_INCLUDED
#define SOM_H_INCLUDED

#include <raylib.h>

Music music;
Sound somBotao;
Sound flecha;

void setMusic(char* musicPath);
void setSomBotao(char* somBotaoPath);
void playFx(int fxNumber);
void playMusic(int musicNumber);
void setTiroFx(char* flechaPath);

#endif