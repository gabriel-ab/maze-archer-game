#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED

#include <raylib.h>

typedef struct Circle
{
    int centerX;
    int centerY;
    int radius;
}Circle;

typedef struct Inimigo
{
    Texture2D sprite;
    Vector2 position;
    Vector2 velocidade;
    Circle range;
    int largura;
    int altura;
    Rectangle linhaColisaoCima;
    Rectangle linhaColisaoEsquerda;
    Rectangle linhaColisaoBaixo;
    Rectangle linhaColisaoDireita;
    int vida;
}Inimigo;

Inimigo inimigoContructor();


#endif
