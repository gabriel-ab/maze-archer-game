#include "data.h"

void carregar(const char *endereco, Mapa *fase){

    //================ZERANDO VALORES====================
    for (int i = 0; i < MAX_RETANGULOS; i++)
    {
        fase->parede[i] = (Rectangle){0, 0, 0, 0};
        fase->piso[i] = (Rectangle){0, 0, 0, 0};
    }
    for (int i = 0; i < MAX_ITENS; i++){
        fase->flecha[i] = (Vector2){0,0};
        fase->vida[i] = (Vector2){0,0};
    }
    for (int i = 0; i < MAX_INIMIGOS; i++) fase->inimigo[i] = (Vector2){0,0};

        fase->parede_atual = 0;
        fase->piso_atual = 0; 
        fase->vida_atual = 0;
        fase->inimigo_atual = 0;
        fase->flecha_atual = 0; 
        fase->inicio = (Vector2){0,0};
        fase->fim = (Vector2){0,0};
    //======================================================
    
    FILE *arquivo = fopen(endereco,"r");

    fscanf(arquivo,"inicio %f %f\n", &fase->inicio.x, &fase->inicio.y);
    fscanf(arquivo,"fim %f %f\n", &fase->fim.x, &fase->fim.y);

    fscanf(arquivo,"paredes %i\n", &fase->parede_atual);
    for( int i = 0; i < fase->parede_atual; i++){
        fscanf(arquivo,"%f %f %f %f\n", &fase->parede[i].x, &fase->parede[i].y, &fase->parede[i].width, &fase->parede[i].height);
    }
    fscanf(arquivo,"pisos %i\n", &fase->piso_atual);
    for( int i = 0; i < fase->piso_atual; i++){
        fscanf(arquivo,"%f %f %f %f\n", &fase->piso[i].x, &fase->piso[i].y, &fase->piso[i].width, &fase->piso[i].height);
    }
    fscanf(arquivo,"inimigos %i\n", &fase->inimigo_atual);
    for( int i = 0; i < fase->inimigo_atual; i++){
        fscanf(arquivo,"%f %f\n", &fase->inimigo[i].x, &fase->inimigo[i].y);
    }
    fscanf(arquivo,"vidas %i\n", &fase->vida_atual);
    for( int i = 0; i < fase->vida_atual; i++){
        fscanf(arquivo,"%f %f\n", &fase->vida[i].x, &fase->vida[i].y);
    }
    fscanf(arquivo,"flechas %i\n", &fase->flecha_atual);
    for( int i = 0; i < fase->flecha_atual; i++){
        fscanf(arquivo,"%f %f\n", &fase->flecha[i].x, &fase->flecha[i].y);
    }
    fscanf(arquivo,"portais %i\n", &fase->portal_atual);
    for( int i = 0; i < fase->portal_atual; i++){
        fscanf(arquivo,"%f %f\n", &fase->portal[i].x, &fase->portal[i].y);
    }
    fclose(arquivo);
}
void salvar(Mapa fase){

    Texture fundo = LoadTextureFromImage(GetScreenData());
    FILE *arquivo;
    char nome_arquivo[64];
    int letra_atual = 0;
    for (int i = 0; i < 64; i++) nome_arquivo[i] = 0;
    bool salvar = false;
    Rectangle retangulo;
    int fps = 0;
    char letra = ' ';
    while(!salvar){
        BeginDrawing();
            ClearBackground(BLACK);
            for(int i = -10; i <= 10; i += 2)  DrawTexture(fundo, i, 0, Fade(WHITE, 0.5));
            for(int i = 10; i >= -10; i -= 2)  DrawTexture(fundo, 0, i, Fade(WHITE, 0.5));
            DrawText("Nome do Arquivo", tela.width/2 - MeasureText("Nome do Arquivo",20)/2, tela.height/3,20,WHITE);
            DrawRectangleLinesEx(retangulo,1,WHITE);
            DrawText(nome_arquivo,retangulo.x +5, retangulo.y +2,20,YELLOW);
        EndDrawing();

        if(letra = GetKeyPressed()){
            nome_arquivo[letra_atual++] = letra;
        }

        if(++fps > 4 && letra_atual > 0 && IsKeyDown(KEY_BACKSPACE)){
            nome_arquivo[--letra_atual] = 0;
            fps = 0;
        }
        retangulo = (Rectangle){tela.width/2 -MeasureText(nome_arquivo,20)/2, tela.height/3 + 30, MeasureText(nome_arquivo,20) +10, 30};

        if(IsKeyPressed(KEY_ESCAPE)) break;
        
        if(IsKeyPressed(KEY_ENTER)){
            salvar = true;
        } 
    }

    if(salvar){
        arquivo = fopen(nome_arquivo, "w");
        fprintf(arquivo, "inicio %.f %.f\n", fase.inicio.x, fase.inicio.y);
        fprintf(arquivo, "fim %.f %.f\n", fase.fim.x, fase.fim.y);
        
        fprintf(arquivo, "paredes %i\n",fase.parede_atual);
        for (int i = 0; i < fase.parede_atual; i++)
        {
            fprintf(arquivo, "%.f %.f %.f %.f\n", fase.parede[i].x, fase.parede[i].y, fase.parede[i].width, fase.parede[i].height);
        }

        fprintf(arquivo, "pisos %i\n",fase.piso_atual);
        for (int i = 0; i < fase.piso_atual; i++)
        {
            fprintf(arquivo, "%.f %.f %.f %.f\n", fase.piso[i].x, fase.piso[i].y, fase.piso[i].width, fase.piso[i].height);
        }

        fprintf(arquivo, "inimigos %i\n",fase.inimigo_atual);
        for (int i = 0; i < fase.inimigo_atual; i++)
        {
            fprintf(arquivo, "%.f %.f\n", fase.inimigo[i].x, fase.inimigo[i].y);
        }

        fprintf(arquivo, "vidas %i\n",fase.vida_atual);
        for (int i = 0; i < fase.vida_atual; i++)
        {
            fprintf(arquivo, "%.f %.f\n", fase.vida[i].x, fase.vida[i].y);
        }

        fprintf(arquivo, "flechas %i\n",fase.flecha_atual);
        for (int i = 0; i < fase.flecha_atual; i++)
        {
            fprintf(arquivo, "%.f %.f\n", fase.flecha[i].x, fase.flecha[i].y);
        }
        fprintf(arquivo, "portais %i\n",fase.portal_atual);
        for (int i = 0; i < fase.portal_atual; i++)
        {
            fprintf(arquivo, "%.f %.f\n", fase.portal[i].x, fase.portal[i].y);
        }
        fclose(arquivo);
    }
}
// Antigo, não mais usado
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