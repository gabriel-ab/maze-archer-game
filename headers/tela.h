//********CONFIGURAÇÔES DE TELA*********
#define larguraTela 800
#define alturaTela 500

Rectangle tela = {larguraTela/3, alturaTela/3, larguraTela, alturaTela};
Rectangle telaAnterior = {larguraTela/3, alturaTela/3, larguraTela, alturaTela};

// Para saber o estado atual
int Is_Fullscreen = 0; 

//*********FUNÇÔES DE TELA***********

//chama a função toggleFulscreen() guardando o tamanho da tela anterior
void telaCheia(void)
{
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
    camera->offset = (Vector2){camera->target.x + tela.width/2,camera->target.y + tela.height/2};
}