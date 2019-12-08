#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#define VELOCIDADE_XALA 2
#define VELOCIDADE_INIMIGO 1.5

#include <raylib.h>

typedef enum{
    INIMIGO_DE_BOA = 0,
    INIMIGO_PISTOLA,
    INIMIGO_AI_PAI_PARA
};

Vector2 c;

typedef struct IA{
    double contador;
    Vector2 direcao;
    float duracao;
    int atual;
}IA;

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
    IA acao;
}Personagem;


Personagem personagemConstructor();

void inimigoSegue(Personagem *inimigo, Vector2 coisa);

void inimigoPistola(Personagem *inimigo, Personagem *fulano);
void inimigoFoge(Personagem *inimigo, Personagem *fulano);
void inimigoStandBy(Personagem *inimigo, Personagem *fulano);

void logicaInimigo(Personagem *inimigo, Personagem *fulano);

#endif

