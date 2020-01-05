#ifndef SOM_H_INCLUDED
#define SOM_H_INCLUDED

#include <raylib.h>

Music music;
Music caveBG;
Music winterBG;
Music lavaBG;
Music bossBG;
Sound queima;
Sound gameover;
Sound acerto;
Sound acertoMonstro;
Sound bossAttack;
Sound passo;
Sound somBotao;
Sound flecha;
Sound arco;
Sound lanca;
Sound item;

void setMusic(char* musicPath);
void setMusicBg(char* cave, char* winter, char* lava, char* bossMusic);
void initMusic();
void setFx(char* somBotaoPath, char* gameOver, char* pickup);
void playFx(int fxNumber);
void playMusic(int musicNumber);
void stopMusic(int musicNumber);
void setTiroFx(char* flechaPath, char* arcoPath);
void checkClickBow();
void setFootStep(char* footstepFx);
void footStep();
void setHitFx(char* hit, char* monstro, char* chefe);
void setTrapFx(char* armadilha, char* queima);
void unloadAllSound();

#endif
