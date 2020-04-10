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
    Rectangle recorte;
    int n_segmento; // qual segmento será usado (qual animação)
    float fps;

    //NÃO ALTERE
    int colunas;
    int linhas;
    double timer;
    int frameAtual;
}Sprite;

//-------------- TEXTURE ---------------//

Texture vidaTexture;     //HUD 
Texture arrowTexture;    //HUD

Texture flechaTexture;  
Texture paredeTexture;
Texture pisoTexture;
Texture armadilhaTexture;
Texture xalaTexture;
Texture inimigoTexture;
Texture portalTexture;
Texture bombaTexture;


Sprite spriteConstructor(Texture textura, int largura_frame, int altura_frame, int fps);
void animaSpriteLinha(Sprite *sprite);
void animaSprite(Sprite *sprite, Segmento segmento[]);
void setTexture(Texture* texture, char* spritePath, int altura, int largura);
void setTextureCropped(Texture* texture, char* spritePath, Rectangle crop);

#endif 