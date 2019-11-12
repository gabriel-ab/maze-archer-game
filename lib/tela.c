#include <raylib.h>
#include "tela.h"

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

void atualizaCamera(Camera2D *camera){
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
    camera->offset = (Vector2){tela.width/2,tela.height/2};
}