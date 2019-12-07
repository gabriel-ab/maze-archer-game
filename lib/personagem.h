#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#define VELOCIDADE_XALA 2
#define VELOCIDADE_INIMIGO 2

#include <raylib.h>
Vector2 c;

typedef struct Personagem
{
    Texture2D sprite;
    Vector2 posicao;
    Vector2 velocidade;
    int largura;
    int altura;
    Rectangle linhaColisaoCima;
    Rectangle linhaColisaoEsquerda;
    Rectangle linhaColisaoBaixo;
    Rectangle linhaColisaoDireita;
    bool invulneravel;
    int vida;
    int flechas;
}Personagem;


Personagem personagemConstructor();
void inimigoAproximaV(Personagem *inimigo, Vector2 coisa);
void inimigoAproxima(Personagem *inimigo, Personagem *fulano);
void inimigoFoge(Personagem *inimigo, Personagem *fulano);
void inimigoAtaca(Personagem *inimigo, Personagem *fulano);


#endif

