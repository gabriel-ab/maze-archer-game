//********CONFIGURAÇÔES DE TELA*********
#define larguraTela 800
#define alturaTela 500

Rectangle tela = {larguraTela/3, alturaTela/3, larguraTela, alturaTela};

// Para saber o estado atual
int Is_Fullscreen = 0; 

//*********FUNÇÔES DE TELA***********
//chama a função toggleFulscreen() guardando a tela anterior
void telaCheia(void)
{
    if(!Is_Fullscreen){
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
    ToggleFullscreen();

    if(Is_Fullscreen){
        SetWindowSize(tela.width, tela.height);
        SetWindowPosition(tela.x, tela.y);
    }
    Is_Fullscreen = !Is_Fullscreen; 
    
}