#include "data.h"

void salvar(Mapa fase){

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
    for (int i = 0; i < fase.vida_atual; i++)
    {
        fprintf(arquivo, "\n%.f, %.f,", fase.vida[i].x, fase.vida[i].y);
    }
    fprintf(arquivo, "\n}");


    fclose(arquivo);
}