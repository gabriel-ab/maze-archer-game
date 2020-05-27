#ifndef SOM_H_INCLUDED
#define SOM_H_INCLUDED

#include <raylib.h>
#include "projetil.h"

Music menuMusic;
Music caveMusic;
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


void loadGame_musics();
void loadGame_sounds();
void playFx(int fxNumber);
void playMusic(int musicNumber);
void footStep();
void checkClickBow();
void unloadAllSound();

#endif
