#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <raylib.h>

Texture2D background;
char* pathImageBackground;
char* pathImageBackgroundAnterior;

void setImageBackground(char* imagePath);

void updateBackground();

#endif