#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#include <raylib.h>


typedef struct Personagem
{
    Texture2D sprite;
    Vector2 position;
    Vector2 velocidade;
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

