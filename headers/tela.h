//********CONFIGURAÇÔES DE TELA*********
#define larguraTela 800
#define alturaTela 500

//status da tela
Rectangle tela = {larguraTela/3, alturaTela/3, larguraTela, alturaTela};

//tela anterior a troca de telacheia
Rectangle telaAnterior = {larguraTela/3, alturaTela/3, larguraTela, alturaTela};

// Para saber o estado atual
int Is_Fullscreen = 0; 

//*********FUNÇÔES DE TELA***********

//Chama a função toggleFulscreen() guardando o tamanho da tela anterior e retornando o estado atual
void telaCheia(void)
{
    if(!Is_Fullscreen){
        telaAnterior.width = GetScreenWidth();
        telaAnterior.height = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();
    }
    ToggleFullscreen();

    if(Is_Fullscreen){
        SetWindowSize(telaAnterior.width, telaAnterior.height);
        SetWindowPosition(tela.x, tela.y);
    }
    Is_Fullscreen = !Is_Fullscreen; 
}
//Atualiza o as variaveis do tamanho da tela
void updateSizeTela(){
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
}