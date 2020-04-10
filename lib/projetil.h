#ifndef ACAO_H_INCLUDED
    #define ACAO_H_INCLUDED

    #include <raylib.h>
    #include "personagem.h"

    #define VELOCIDADE_Projetil 20;

    typedef enum Projetil_status{
        MIRANDO = 0,
        ATIVO,
        RESGATAVEL,
        INATIVA
    }Projetil_status;

    typedef struct projetil{
        Sprite sprite;
        Vector2 posicao;
        Vector2 velocidade;
        float angulo;
        int ativa;
        double tempoParaResgatar;
    }Projetil;

    void mira(Personagem fulano, Projetil *bala, Camera2D cam);
    void atira(Personagem fulano ,Projetil *bala);

    int colisaoProjetil_inimigo(Projetil *bala, Personagem *inimigo, int n_inimigos);
    int colisaoProjetil_mapa(Projetil *bala, Rectangle *MAPA, int n_mapa);

#endif