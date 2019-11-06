#include <stdlib.h>
#include <raylib.h>

#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED


typedef struct
{
    Texture2D sprite;
    Vector2 position;
    int largura;
    int altura;
    Rectangle linhaColisaoCima;
    Rectangle linhaColisaoEsquerda;
    Rectangle linhaColisaoBaixo;
    Rectangle linhaColisaoDireita;
}Personagem;


Personagem personagemConstructor();
Personagem inimigoContructor();


#endif

