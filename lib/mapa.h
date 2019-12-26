#ifndef MAPA_H
#define MAPA_H

typedef struct Mapa
{
    Rectangle parede[MAX_RETANGULOS];
    int parede_atual;

    Rectangle piso[MAX_RETANGULOS];
    int piso_atual;
    
    Vector2 inimigo[MAX_INIMIGOS];
    int inimigo_atual;    
    
    Vector2 vida[MAX_ITENS];
    int vida_atual;    
    
    Vector2 flecha[MAX_ITENS];
    int flecha_atual;

    Vector2 inicio;
    Vector2 fim;
}Mapa;

#endif