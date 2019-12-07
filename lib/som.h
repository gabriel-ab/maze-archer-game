#ifndef SOM_H_INCLUDED
#define SOM_H_INCLUDED

#include <raylib.h>

Music music;
Music caveBG;
Sound somBotao;
Sound flecha;
Sound arco;

void setMusic(char* musicPath, char* cave);
void setSomBotao(char* somBotaoPath);
void playFx(int fxNumber);
void playMusic(int musicNumber);
void setTiroFx(char* flechaPath, char* arcoPath);
void checkClickBow(int projetil_atual);

#endif