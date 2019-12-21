#ifndef SOM_H_INCLUDED
#define SOM_H_INCLUDED

#include <raylib.h>

Music music;
Music caveBG;
Music winterBG;
Music lavaBG;
Sound queima;
Sound gameover;
Sound acerto;
Sound passo;
Sound somBotao;
Sound flecha;
Sound arco;
Sound lanca;
Sound item;

void setMusic(char* musicPath);
void setMusicBg(char* cave, char* winter, char* lava);
void initMusic();
void setFx(char* somBotaoPath, char* gameOver, char* pickup);
void playFx(int fxNumber);
void playMusic(int musicNumber);
void setTiroFx(char* flechaPath, char* arcoPath);
void checkClickBow();
void setFootStep(char* footstepFx);
void footStep();
void setHitFx();
void setTrapFx(char* armadilha, char* queima);
void unloadAllSound();

#endif
