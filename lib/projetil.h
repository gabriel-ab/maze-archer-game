#ifndef ACAO_H_INCLUDED
    #define ACAO_H_INCLUDED

    #include <raylib.h>
    #include "personagem.h"

    #define VELOCIDADE_Projetil 20;

    typedef struct projetil
    {
        Vector2 posicao;
        Vector2 velocidade;
        float angulo;
        int ativa;
    }Projetil;

    void mira(Personagem fulano, Projetil *bala, Camera2D cam);
    void atira(Personagem fulano ,Projetil *bala);
    void atualizaProjetil(Projetil *bala);

#endif