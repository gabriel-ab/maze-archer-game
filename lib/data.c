#include "data.h"

void salvar(Mapa fase){
    Texture fundo = LoadTextureFromImage(GetScreenData());
    FILE *arquivo;
    char nome_arquivo[64];
    int letra = 0;
    for (int i = 0; i < 64; i++) nome_arquivo[i] = 0;
    bool confirma = false;
    bool salvar = false;
    Rectangle retangulo;
    int fps = 0;
    while(!confirma){
        
        if(GetKeyPressed() != -1){
            nome_arquivo[letra++] = GetKeyPressed();
        }
        if(IsKeyDown(KEY_BACKSPACE) && letra > 0 && ++fps > 10){
            nome_arquivo[--letra] = 0;
            fps = 0;
        }

        retangulo = (Rectangle){tela.width/2 -MeasureText(nome_arquivo,20)/2, tela.height/3 + 30, MeasureText(nome_arquivo,20) +10, 30};
        BeginDrawing();
            ClearBackground(BLACK);
            for(int i = -5; i <= 0; i++)  DrawTexture(fundo,i,0,(Color){255,255,255,50});
            for(int i = 5; i >= 0; i--)  DrawTexture(fundo,i,0,(Color){255,255,255,50});
            DrawText("Nome do Arquivo", tela.width/2 - MeasureText("Nome do Arquivo",20)/2, tela.height/3,20,WHITE);
            DrawRectangleLinesEx(retangulo,1,WHITE);
            DrawText(nome_arquivo,retangulo.x +5, retangulo.y +2,20,YELLOW);
        EndDrawing();

        if(IsKeyPressed(KEY_ESCAPE)) confirma = true;
        
        if(IsKeyPressed(KEY_ENTER)){
            salvar = true;
            confirma = true;
        } 
    }

    if(salvar){
        arquivo = fopen(nome_arquivo, "a");
        fprintf(arquivo, "%.f %.f\n", fase.inicio.x, fase.inicio.y);
        fprintf(arquivo, "%.f %.f\n", fase.fim.x, fase.fim.y);
        
        fprintf(arquivo, "parede %i\n",fase.parede_atual);
        for (int i = 0; i < fase.parede_atual; i++)
        {
            fprintf(arquivo, "%.f %.f %.f %.f\n", fase.parede[i].x, fase.parede[i].y, fase.parede[i].width, fase.parede[i].height);
        }

        fprintf(arquivo, "piso %i\n",fase.piso_atual);
        for (int i = 0; i < fase.piso_atual; i++)
        {
            fprintf(arquivo, "\n    %.f, %.f, %.f, %.f,", fase.piso[i].x, fase.piso[i].y, fase.piso[i].width, fase.piso[i].height);
        }

        fprintf(arquivo, "inimigo %i\n",fase.inimigo_atual);
        for (int i = 0; i < fase.inimigo_atual; i++)
        {
            fprintf(arquivo, "\n%.f, %.f,", fase.inimigo[i].x, fase.inimigo[i].y);
        }

        fprintf(arquivo, "vida %i\n",fase.vida_atual);
        for (int i = 0; i < fase.vida_atual; i++)
        {
            fprintf(arquivo, "\n%.f, %.f,", fase.vida[i].x, fase.vida[i].y);
        }

        fprintf(arquivo, "flecha %i\n",fase.flecha_atual);
        for (int i = 0; i < fase.flecha_atual; i++)
        {
            fprintf(arquivo, "\n%.f, %.f,", fase.flecha[i].x, fase.flecha[i].y);
        }
    }
}
void exportar(Mapa fase){
    FILE *arquivo;

    arquivo = fopen("codigo.txt", "a");
    fprintf(arquivo, "\nInicio de Jogo = (Vector2){%.f,%.f}", fase.inicio.x, fase.inicio.y);
    fprintf(arquivo, "\nFim do Jogo = (Vector2){%.f,%.f}", fase.fim.x, fase.fim.y);

    fprintf(arquivo, "\n\n//------------PAREDES----------//");
    fprintf(arquivo, "\nRectangle parede = {");
    for (int i = 0; i < fase.parede_atual; i++)
    {
        fprintf(arquivo, "\n    %.f, %.f, %.f, %.f,", fase.parede[i].x, fase.parede[i].y, fase.parede[i].width, fase.parede[i].height);
    }
    fprintf(arquivo, "\n}");

    fprintf(arquivo, "\n\n//-------------PISOS-----------//");
    fprintf(arquivo, "\nRectangle piso = {");
    for (int i = 0; i < fase.piso_atual; i++)
    {
        fprintf(arquivo, "\n    %.f, %.f, %.f, %.f,", fase.piso[i].x, fase.piso[i].y, fase.piso[i].width, fase.piso[i].height);
    }
    fprintf(arquivo, "\n}");


    fprintf(arquivo, "\n\n//-----------INIMIGOS----------//");
    fprintf(arquivo, "\nVector2 inimigo = {");
    for (int i = 0; i < fase.inimigo_atual; i++)
    {
        fprintf(arquivo, "\n%.f, %.f,", fase.inimigo[i].x, fase.inimigo[i].y);
    }
    fprintf(arquivo, "\n}");
    
    fprintf(arquivo, "\n\n//-------------VIDAS-----------//");
    fprintf(arquivo, "\nVector2 item_vida = {");
    for (int i = 0; i < fase.vida_atual; i++)
    {
        fprintf(arquivo, "\n%.f, %.f,", fase.vida[i].x, fase.vida[i].y);
    }
    fprintf(arquivo, "\n}");

    fprintf(arquivo, "\n\n//------------FLECHAS----------//");
    fprintf(arquivo, "\nVector2 item_flecha = {");
    for (int i = 0; i < fase.flecha_atual; i++)
    {
        fprintf(arquivo, "\n%.f, %.f,", fase.flecha[i].x, fase.flecha[i].y);
    }
    fprintf(arquivo, "\n}");


    fclose(arquivo);
}