#include "../../lib/som.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/data.h"
#include <string.h>

void selecao_de_fase(){
    int n_fases = 0;
    char temp[256] = {'\0'};
    strcat(temp,GetWorkingDirectory());
    strcat(temp,"\\resources\\fases\\");
    char **arquivos = GetDirectoryFiles(temp, &n_fases);
    bool confirma = false;
    int seletor = 0;


    while (!confirma)
    {
        if(IsKeyPressed(KEY_UP))    seletor--;
        if(IsKeyPressed(KEY_DOWN))  seletor++;

        if(IsKeyPressed(KEY_ESCAPE)) break;
        if(IsKeyPressed(KEY_ENTER)) confirma = true;
        
        playMusic(1);
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleGradientV(0,0,tela.width, tela.height, GRAY, BLACK);
            for (int i = 0; i < n_fases; i++) DrawText(arquivos[i],30,50 + i*30, seletor == i ? 30 : 20, YELLOW);
            DrawText(temp,10,10,20,BLACK);
        EndDrawing();
    }
    if(confirma){
        //Carrega a fase do endereço selecionado
        strcat(temp,arquivos[seletor]);
        strcpy(diretorio, "resources/fases/");
        strcat(diretorio, GetFileName(temp));
        telaAtual = TELA_FASE_CUSTOM;
    }
    
}