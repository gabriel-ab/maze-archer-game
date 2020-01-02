#ifndef INCLUDED_SAVE_H
#define INCLUDED_SAVE_H

typedef struct Item{
    Sprite sprite;
    Vector2 posicao;
    bool ativo;
}Item;
typedef struct Mapa
{
    Rectangle parede[MAX_RETANGULOS];
    int n_paredes;

    Rectangle piso[MAX_RETANGULOS];
    int n_pisos;
    
    Personagem inimigo[MAX_INIMIGOS];
    int n_inimigos;    
    
    Item vida[MAX_ITENS];
    int n_vidas;    
    
    Item flecha[MAX_ITENS];
    int n_flechas;

    Vector2 inicio;
    Vector2 fim;
} Mapa;

void save();
int load();

#endif