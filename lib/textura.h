#ifndef TEXTURA_INCLUDED
#define TEXTURA_INCLUDED
#include <raylib.h>

/************Funcionamento**************
    A textura contem o spritesheet
    dentro do spritesheet existem os 
    segmentos de animação do sprite.
    |===============|
    |               |
    |_______        |
    |_______|       | <- segmento
    |               |
    |               |
    |===============|

    Cada segmento possui uma linha, inicio e fim
***************************************/

typedef struct Segmento{
    int linha; //iniciando no 0
    int inicio; 
    int fim;
}Segmento;

typedef struct Sprite{
    //ALTERAVEIS
    Texture2D textura;
    int n_segmento; // qual segmento será usado (qual animação)
    float fps;

    //NÃO ALTERE
    Rectangle recorte;
    int colunas;
    int linhas;
    double timer;
    int frameAtual;
}Sprite;

Sprite spriteConstructor(const char *endereco, int largura_frame, int altura_frame, int fps);
void animaSpriteLinha(Sprite *sprite);
void animaSprite(Sprite *sprite, Segmento segmento[]);
#endif 