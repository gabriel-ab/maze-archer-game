#include <raylib.h>
#include "tela.h"
#include "define.h"

void telaCheia()
{
    if(!is_fullscreen){
        telaAnterior.width = GetScreenWidth();
        telaAnterior.height = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
    ToggleFullscreen();

    if(is_fullscreen){
        SetWindowSize(telaAnterior.width, telaAnterior.height);
        SetWindowPosition(tela.x, tela.y);
    }
    is_fullscreen = !is_fullscreen; 
    
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
}
// (Rectangle){tela.width/4, tela.height/4 ,tela.width/2, tela.height/2};

//Se o foco sair do retangulo inserido A camera seguirá o foco
//(WINDOWS) / (LINUX)
void cameraSegueFocoRec(Camera2D *cam, Vector2 foco, Rectangle rec)
{
    #ifdef __WIN32
        cam->target = foco;
        if(foco.x + cam->offset.x < rec.x) cam->offset.x    += VEL_MAX_PERSONAGEM;
        if(foco.y + cam->offset.y < rec.y) cam->offset.y    += VEL_MAX_PERSONAGEM;

        if(foco.x + cam->offset.x > rec.x + rec.width) cam->offset.x    -= VEL_MAX_PERSONAGEM;
        if(foco.y + cam->offset.y > rec.y + rec.height) cam->offset.y   -= VEL_MAX_PERSONAGEM;

    #elif __linux__
        if(foco.x + cam->target.x < rec.x) cam->target.x    -= VEL_MAX_PERSONAGEM;
        if(foco.y + cam->target.y < rec.y) cam->target.y    -= VEL_MAX_PERSONAGEM;

        if(foco.x + cam->target.x > rec.x + rec.width) cam->target.x    += VEL_MAX_PERSONAGEM;
        if(foco.y + cam->target.y > rec.y + rec.height) cam->target.y   += VEL_MAX_PERSONAGEM;
    #endif
}


//-------------- BACKGROUND ---------------//
void setImageBackground(char* imagePath) {
    pathImageBackground = imagePath;
}

void updateBackground() {
    Image backgroundImage = LoadImage(pathImageBackground);
    ImageResize(&backgroundImage, tela.width, tela.height);  
    background = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
}


//-------------- HUD ---------------//

void setVidaSprite(char* spritePath){
    Image vidaImage =  LoadImage(spritePath);
    ImageResize(&vidaImage, 30 , 30);
    vida = LoadTextureFromImage(vidaImage);
    UnloadImage(vidaImage);
}


void drawHUD(int quantidadeVida){
    for (int i = 0; i < quantidadeVida; i++)
    {
        DrawTexture(vida, 10+35*i, 10, GRAY);
    }
}
