#include "window.h"

void telaCheia(void){
    if(!Is_Fullscreen){
        telaAnterior.width = GetScreenWidth();
        telaAnterior.height = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
    ToggleFullscreen();

    if(Is_Fullscreen){
        SetWindowSize(telaAnterior.width, telaAnterior.height);
        SetWindowPosition(telaAnterior.x, telaAnterior.y);
    }
    Is_Fullscreen = !Is_Fullscreen; 
    
}
void atualizaCamera(Camera2D *camera){
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
    camera->offset = (Vector2){tela.width/2 -posCam.x,tela.height/2 -posCam.y};
}