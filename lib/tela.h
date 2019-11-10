//********CONFIGURAÇÔES DE TELA*********
#define LARGURA_TELA 800
#define ALTURA_TELA 600

Rectangle tela = {LARGURA_TELA/3, ALTURA_TELA/3, LARGURA_TELA, ALTURA_TELA};
Rectangle telaAnterior = {LARGURA_TELA/3, ALTURA_TELA/3, LARGURA_TELA, ALTURA_TELA};

// Para saber o estado atual
bool is_fullscreen = false; 

//*********FUNÇÔES DE TELA***********

//chama a função toggleFulscreen() guardando o tamanho da tela anterior
bool telaCheia(void)
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

    return is_fullscreen;
}

void atualizaCamera(Camera2D *camera){
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
    camera->offset = (Vector2){tela.width/2,tela.height/2};
}
