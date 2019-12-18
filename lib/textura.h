#ifndef TEXTURA_INCLUDED
#define TEXTURA_INCLUDED
#include <raylib.h>

typedef struct Sprite{
    //Definidos
    Texture2D textura;
    float fps;

    //Calculados
    Rectangle recorte;
    int colunas;
    int linhas;
    double timer;
    int frameAtual;

}Sprite;


#endif 