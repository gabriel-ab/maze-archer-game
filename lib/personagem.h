#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#define VELOCIDADE_XALA 2
#define VELOCIDADE_INIMIGO 1.5

#include <raylib.h>
#include "textura.h"

typedef enum AtitudesInimigas{
    INIMIGO_DE_BOA = 0,
    INIMIGO_PISTOLA,
    INIMIGO_AI_PAI_PARA,
    INIMIGO_ATORDOADO
}AtitudesInimigas;

Vector2 c;

typedef struct IA{
    double contador;
    Vector2 direcao;
    float duracao;
    int atual;
}IA;

typedef struct Personagem
{
    Sprite sprite;
    Vector2 posicao;
    Vector2 velocidade;
    int largura;
    int altura;
    Rectangle linhaColisaoCima;
    Rectangle linhaColisaoEsquerda;
    Rectangle linhaColisaoBaixo;
    Rectangle linhaColisaoDireita;
    bool invulneravel;
    double tempoInvulneravel;
    int vida;
    int quantidadeFlechas;
    IA acao;
}Personagem;


Personagem personagemConstructor();

void inimigoSegue(Personagem *inimigo, Vector2 coisa);

void inimigoPistola(Personagem *inimigo, Personagem *fulano);
void inimigoFoge(Personagem *inimigo, Personagem *fulano);
void inimigoStandBy(Personagem *inimigo, Personagem *fulano);

void logicaInimigo(Personagem *inimigo, Personagem *fulano);

#endif

