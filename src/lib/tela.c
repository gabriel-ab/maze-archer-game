#include "../include/tela.h"

void telaCheia()
{
    if (IsWindowFullscreen()) {
        ToggleFullscreen();
        SetWindowSize(larguraAnterior, alturaAnterior);
        SetWindowPosition(larguraAnterior / 3, alturaAnterior / 3);
    }
    else {
        larguraAnterior = GetScreenWidth();
        alturaAnterior = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
        ToggleFullscreen();
    }
}

void atualizarCamera(Camera2D *cam, Vector2 posicao)
{
    cam->target.x = 0.9*cam->target.x + 0.1*posicao.x;
    cam->target.y = 0.9*cam->target.y + 0.1*posicao.y;

    #ifdef __WIN32
        cam->offset.x = GetScreenWidth()/2  -cam->target.x;
        cam->offset.y = GetScreenHeight()/2 -cam->target.y;
    #endif
}



// ------------- CÂMERA ----------- //

void setTargetCamera(Personagem *target)
{
    cam.zoom = 3;
    cam.rotation = 0;
    cam.target = target->posicao;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){GetScreenWidth()/2 , GetScreenHeight()/2};
}


// Controls the selection between min and max, both included
void menuControl(int min, int *selector, int max){
    if (IsKeyPressed(KEY_UP)){
        if (*selector > min) (*selector)--;
        else *selector = max;
    }
    if (IsKeyPressed(KEY_DOWN)){
        if (*selector < max) (*selector)++;
        else *selector = min;
    }
}