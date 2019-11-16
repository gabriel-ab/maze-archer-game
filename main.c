#include <raylib.h>
#include "headers/tela.h"
#include <stdio.h>

#define MAX_RETANGULOS 100

#define paredeH3 (Rectangle){0,0,32,128}
#define paredeV3 (Rectangle){0,0,128,32}
#define paredeH5 (Rectangle){0,0,32,6*32}
#define paredeV5 (Rectangle){0,0,6*32,32}
#define paredeH8 (Rectangle){0,0,32,320}
#define paredeV8 (Rectangle){0,0,320,32}

#define piso2_2 (Rectangle){0,0,64,64}
#define piso4_4 (Rectangle){0,0,4*32,4*32}
#define piso6_6 (Rectangle){0,0,6*32,6*32}
#define piso8_8 (Rectangle){0,0,8*32,8*32}
#define piso16_6 (Rectangle){0,0,16*32,6*32}
#define piso6_16 (Rectangle){0,0,6*32,16*32}

typedef enum{
    SELECIONE = 0,
    PAREDE = 1,
    PISO = 2,
    // TEXTURA = 3
}Tipo;

void desenhaGrid(void);
void desenhaTelaAjuda(void);
void selecionarTipo(int *tipo);
int telaSair(void);

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width,tela.height,"Criador de fases");

    Rectangle retangulo = {0,0,0,0};

    Rectangle parede[MAX_RETANGULOS];
    Rectangle piso[MAX_RETANGULOS];
    
    int modo = 1;

    //zerando valores
    for(int i = 0; i < MAX_RETANGULOS; i++){
        parede[i] = (Rectangle){0,0,0,0};
        piso[i] = (Rectangle){0,0,0,0};
    }

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){tela.width/2,tela.height/2};

    //VARIAVEIS DO MODO LIVRE
    Vector2 inicio;
    Vector2 fim = {0,0};

    Vector2 inicioJogo = {0,0};
    
    FILE *arquivo;
    
    int clique = 0, tipo = 1, sair = 0;
    int parede_atual = 0;
    int piso_atual = 0;
    SetExitKey(0);
    
    while(!WindowShouldClose() && !sair)
    {
        //update
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();

        if(IsKeyDown(KEY_PAGE_UP))                      camera.zoom += 0.001;
        if(IsKeyDown(KEY_PAGE_DOWN) && camera.zoom > 0) camera.zoom -= 0.001;

        if(GetKeyPressed() != -1) modo = 2;
        switch(tipo)
        {
            case PAREDE:
                if(IsKeyPressed(KEY_ONE))   retangulo = paredeH3;
                if(IsKeyPressed(KEY_TWO))   retangulo = paredeV3; 
                if(IsKeyPressed(KEY_THREE)) retangulo = paredeH5;
                if(IsKeyPressed(KEY_FOUR))  retangulo = paredeV5;
                if(IsKeyPressed(KEY_FIVE))  retangulo = paredeH8;
                if(IsKeyPressed(KEY_SIX))   retangulo = paredeV8;
                break;

            case PISO:
                if(IsKeyPressed(KEY_ONE))   retangulo = piso2_2;
                if(IsKeyPressed(KEY_TWO))   retangulo = piso4_4; 
                if(IsKeyPressed(KEY_THREE)) retangulo = piso6_6;
                if(IsKeyPressed(KEY_FOUR))  retangulo = piso8_8;
                if(IsKeyPressed(KEY_FIVE))  retangulo = piso6_16;
                if(IsKeyPressed(KEY_SIX))   retangulo = piso16_6;
                break;
        }
        
        if(IsKeyPressed(KEY_TAB)) 
        {
            tipo = SELECIONE;
            modo = 1;
        }
        
        if(IsKeyPressed(KEY_ESCAPE))
        {
            if(modo != 1) modo = 1;
            else sair = 1;
        }

        //MOVIMENTAÇÃO DA CAMERA
        if(IsKeyDown(KEY_W)) camera.offset.y += 2;
        if(IsKeyDown(KEY_S)) camera.offset.y -= 2;
        if(IsKeyDown(KEY_A)) camera.offset.x += 2;
        if(IsKeyDown(KEY_D)) camera.offset.x -= 2;

        //EDIÇÃO DO TAMANHO DO OBJETO
        if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        {
            if(IsKeyPressed(KEY_UP) && retangulo.height > 32)    retangulo.height -= 32; 
            if(IsKeyPressed(KEY_DOWN))                          retangulo.height += 32; 
            if(IsKeyPressed(KEY_LEFT) && retangulo.width > 32)   retangulo.width -= 32; 
            if(IsKeyPressed(KEY_RIGHT))                         retangulo.width += 32; 
        }
        else
        {
            //MOVIMENTAÇÃO DO OBJETO
            if(IsKeyPressed(KEY_UP))    retangulo.y -= 32; 
            if(IsKeyPressed(KEY_DOWN))  retangulo.y += 32; 
            if(IsKeyPressed(KEY_LEFT))  retangulo.x -= 32; 
            if(IsKeyPressed(KEY_RIGHT)) retangulo.x += 32; 
        }

        //----------------MODO USANDO MOUSE--------------//
        if (modo == 1){
            //Recebe coordenadas do retangulo
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if(clique == 0)
                {
                    inicio = GetMousePosition();
                    inicio.x = (inicio.x -camera.offset.x)/camera.zoom;
                    inicio.y = (inicio.y -camera.offset.y)/camera.zoom;
                }
                else
                {
                    switch(tipo)
                    {
                        case PAREDE: 
                            parede[parede_atual] = retangulo;
                            parede_atual++; break;
                        case PISO: 
                            piso[piso_atual] = retangulo; 
                            piso_atual++; break;
                    }
                }
                clique = !clique;
                
            }else{
                fim = GetMousePosition();
                fim.x = (fim.x -camera.offset.x)/camera.zoom;
                fim.y = (fim.y -camera.offset.y)/camera.zoom;
            }
            retangulo = (Rectangle){inicio.x, inicio.y, fim.x -inicio.x, fim.y -inicio.y};
        }
        //---------------MODO USANDO TECLADO-------------//
        else if(modo == 2)
        {
            if(IsKeyPressed(KEY_ENTER))
            {
                switch(tipo)
                {
                    case PAREDE: parede[parede_atual++] = retangulo; break;
                    case PISO: piso[piso_atual++] = retangulo; break;
                }
            }
        }

        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            inicioJogo.x = (GetMouseX() -camera.offset.x)/ camera.zoom;
            inicioJogo.y = (GetMouseY() -camera.offset.y)/ camera.zoom;
        }
        
        

        if(IsKeyPressed(KEY_F)) telaCheia();

        //cancela retangulo atual ou apaga ultimo retangulo
        if(IsKeyPressed(KEY_DELETE))
        {
            if(clique)
            {
                clique = 0;
            }
            else
            {
                switch(tipo)
                {
                    case PAREDE: 
                        if(parede_atual > 0)
                        {
                            parede[--parede_atual] = (Rectangle){0,0,0,0}; 
                        }
                        break;
                    case PISO: 
                        if(piso_atual > 0)
                        {
                            piso[--piso_atual] = (Rectangle){0,0,0,0};
                        }
                        break;
                }
            }
        }
        
        //---------------------Desenho da Tela-------------------
        BeginDrawing();
            ClearBackground((Color){50,50,50,255});
            BeginMode2D(camera);

                desenhaGrid();

                for(int i = 0; i < MAX_RETANGULOS; i++)
                {
                    DrawRectangleRec(parede[i],BLACK);
                    DrawRectangleLinesEx(parede[i],1,(Color){100,240,100,255});
                    if(parede[i].width == 0 && parede[i].height == 0) break;
                }
                for(int i = 0; i < MAX_RETANGULOS; i++)
                {
                    DrawRectangleRec(piso[i],BLACK);
                    DrawRectangleLinesEx(piso[i],1,(Color){100,100,200,255});
                    if(piso[i].width == 0 && piso[i].height == 0) break;
                }
                
                if(modo != 1 || clique)
                {
                    DrawRectangleRec(retangulo,BLACK);
                    DrawRectangleLinesEx(retangulo,1,(Color){180,240,100,255});
                }

                DrawCircle(0,0,2,GREEN);
                DrawCircleV(inicioJogo,5,BLUE);
            EndMode2D();

            DrawText(FormatText("Numero de paredes: %i",parede_atual),10,10,20,YELLOW);
            DrawText(FormatText("Numero de pisos: %i",piso_atual),10,30,20,YELLOW);
            if(modo == 1){
                DrawText("Modo livre",10,50,20,YELLOW);
            }
            else if(modo == 2){
                DrawText("Controle por teclado",10,50,20,YELLOW);
            }
            
            DrawText((FormatText("Zoom: %.2f",camera.zoom)),10,70,20,YELLOW);

            if(IsKeyDown(KEY_F1))
            {
                desenhaTelaAjuda();
            }
            if(IsKeyUp(KEY_F1))
            {
                DrawText("Presione F1 para Ajuda",tela.width - 240, 10,20,YELLOW);
            }

        EndDrawing();
        if(tipo == SELECIONE) selecionarTipo(&tipo);
        if(sair) sair = telaSair();
    }

    //Impressão do MAPA
    arquivo = fopen("retangulos_da_fase.txt","a");
    fprintf(arquivo,"\nPosição inicial do Jogador = (Vector2){%.f,%.f}", inicioJogo.x , inicioJogo.y);
    
    fprintf(arquivo,"\n\n//------------PAREDES----------//");
    for(int i = 0; i < 100; i++)
    {
        if(parede[i].width == 0 && parede[i].height == 0) break;
        fprintf(arquivo,"\n    %.f, %.f, %.f, %.f,",parede[i].x, parede[i].y, parede[i].width, parede[i].height);
    }

    fprintf(arquivo,"\n\n//-------------PISOS-----------//");
    for(int i = 0; i < 100; i++)
    {
        if(piso[i].width == 0 && piso[i].height == 0) break;
        fprintf(arquivo,"\n    %.f, %.f, %.f, %.f,",piso[i].x, piso[i].y, piso[i].width, piso[i].height);
    }
    fclose(arquivo);
    CloseWindow();
    
    return 0;
}
void desenhaGrid(void){
    DrawLine( -2048,     0, 2048,    0, (Color){100,100,100,255});
    DrawLine(     0, -2048,    0, 2048, (Color){100,100,100,255});
    
    DrawLine(   256, -2048,  256, 2048, (Color){100,100,100,255});
    DrawLine(  -256, -2048, -256, 2048, (Color){100,100,100,255});
    DrawLine( -2048,  -256, 2048, -256, (Color){100,100,100,255});
    DrawLine( -2048,   256, 2048,  250, (Color){100,100,100,255});

    DrawLine(  1024, -2048, 1024, 2048, (Color){100,100,100,255});
    DrawLine( -1024, -2048,-1024, 2048, (Color){100,100,100,255});
    DrawLine( -2048, -1024, 2048,-1024, (Color){100,100,100,255});
    DrawLine( -2048,  1024, 2048, 1024, (Color){100,100,100,255});
}

void selecionarTipo(int *tipo)
{
    int confirma = 0;
    int opcao = 1;
    while(!confirma)
    {
        BeginDrawing();
            DrawRectangle(0,0,tela.width,tela.height,(Color){10,10,10,255});
            DrawText("SELECIONE O TIPO DE RETANGULO:",tela.width/2 -MeasureText("SELECIONE O TIPO DE RETANGULO:",20)/2, tela.height/2, 20, RED);
            DrawText(opcao == 1 ? "PAREDE": "parede",tela.width/2 -MeasureText("PAREDE",20)/2, tela.height/2 +30, 20, RED);
            DrawText(opcao == 2 ? "PISO": "piso",tela.width/2 -MeasureText("PISO",20)/2, tela.height/2 +50, 20, RED);
        EndDrawing();

        if(IsKeyPressed(KEY_UP)) opcao = 1;
        if(IsKeyPressed(KEY_DOWN)) opcao = 2;
        if(IsKeyPressed(KEY_ENTER)) confirma = 1;

        if(confirma && opcao == 1) *tipo = PAREDE;
        if(confirma && opcao == 2) *tipo = PISO;
    }
}

void desenhaTelaAjuda(void)
{
    #ifndef TEXTO_AJUDA
        #define TEXTO_AJUDA
        #define AJUDA_0 "1,2,3,4,5,6 = Retangulos Predefinidos de Paredes e Pisos"
        #define AJUDA_1 "TAB = Parede / Pisos"
        #define AJUDA_2 "Setas = Movimenta Os Objetos"
        #define AJUDA_3 "Shift + Setas = Edição de tamanho do Objeto"
        #define AJUDA_4 "Clique Esquerdo = Retangulo Personalizado"
        #define AJUDA_5 "Clique Direito = Posição Do Inicio De Jogo"
        #define AJUDA_6 "Del = Cancela Retangulo Atual / Apaga Anteriores"
        #define AJUDA_7 "Page Up/Down = Zoom"
        #define AJUDA_8 "Enter = Fixa Retangulo"
        
        #define ESPACAMENTO 40
    #endif
    DrawRectangle(0,0,tela.width,tela.height,(Color){30,30,30,200});

    DrawText( AJUDA_0 , tela.width/2 -MeasureText( AJUDA_0 ,20)/2, tela.width/5 - 3*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_1 , tela.width/2 -MeasureText( AJUDA_1 ,20)/2, tela.width/5 - 1*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_2 , tela.width/2 -MeasureText( AJUDA_2 ,20)/2, tela.width/5 + 0*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_3 , tela.width/2 -MeasureText( AJUDA_3 ,20)/2, tela.width/5 + 1*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_4 , tela.width/2 -MeasureText( AJUDA_4 ,20)/2, tela.width/5 + 2*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_5 , tela.width/2 -MeasureText( AJUDA_5 ,20)/2, tela.width/5 + 3*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_6 , tela.width/2 -MeasureText( AJUDA_6 ,20)/2, tela.width/5 + 4*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_7 , tela.width/2 -MeasureText( AJUDA_7 ,20)/2, tela.width/5 + 6*ESPACAMENTO, 20, (Color){200,200,200,255});
    DrawText( AJUDA_8 , tela.width/2 -MeasureText( AJUDA_8 ,20)/2, tela.width/5 + 7*ESPACAMENTO, 20, (Color){200,200,200,255});
}

int telaSair(void)
{
    int confirma = 0;
    int opcao = 1;
    while(!confirma)
    {
        BeginDrawing();
            DrawRectangle(0,0,tela.width,tela.height,(Color){10,10,10,255});
            DrawText("DESEJA SAIR?",tela.width/2 -MeasureText("DESEJA SAIR?",20)/2, tela.height/2, 20, RED);
            DrawText(opcao == 1 ? "SIM": "sim",tela.width/2 -MeasureText("SIM",20)/2, tela.height/2 +30, 20, RED);
            DrawText(opcao == 2 ? "NÃO": "não",tela.width/2 -MeasureText("NAO",20)/2, tela.height/2 +50, 20, RED);
        EndDrawing();

        if(IsKeyPressed(KEY_UP)) opcao = 1;
        if(IsKeyPressed(KEY_DOWN)) opcao = 2;
        if(IsKeyPressed(KEY_ENTER)) confirma = 1;

        if(confirma && opcao == 1) return 1;
        if(confirma && opcao == 2) return 0;
    }
}