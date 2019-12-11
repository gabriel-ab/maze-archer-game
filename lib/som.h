#ifndef SOM_H_INCLUDED
#define SOM_H_INCLUDED

#include <raylib.h>

Music music;
Music caveBG;
Music winterBG;
Music forestBG;
Sound queima;
Sound gameover;
Sound acerto;
Sound passo;
Sound somBotao;
Sound flecha;
Sound arco;
Sound lanca;

void setMusic(char* musicPath);
void setMusicBg(char* cave, char* winter, char* forest);
void initMusic();
void setFx(char* somBotaoPath, char* gameOver);
void playFx(int fxNumber);
void playMusic(int musicNumber);
void setTiroFx(char* flechaPath, char* arcoPath);
void checkClickBow(int projetil_atual);
void setFootStep(char* footstepFx);
void footStep();
void setHitFx();
void setTrapFx(char* armadilha, char* queima);
void unloadAllSound();

#endif