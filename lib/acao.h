#ifndef ACAO_H_INCLUDED
    #define ACAO_H_INCLUDED

    #include <raylib.h>
    #include "personagem.h"

    #define VELOCIDADE_TIRO 20;

    typedef struct tiro
    {
        Vector2 origem;
        Vector2 velocidade;
        float angulo;
        int ativa;
    }Tiro;

    void mira(Personagem fulano, Tiro *bala, Camera2D cam);
    void atira(Tiro *bala);
    void atualizaTiro(Tiro *bala);

#endif