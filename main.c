#include <raylib.h>
#include "headers/tela.h"
#include <stdio.h>

#define MAX_RETANGULOS 100

void desenhaGrid(){
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
int telaSair();


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width,tela.height,"Criador de fases");

    Rectangle retangulo[MAX_RETANGULOS];
    Rectangle paredeH = {0,0,32,96};
    Rectangle paredeV = {0,0,96,32};
    // Rectangle temp = {0,0,0,0};
    
    int modo = 1;

    //zerando valores
    for(int i = 0; i < MAX_RETANGULOS; i++){
        retangulo[i] = (Rectangle){0,0,0,0};
    }

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){tela.width/2,tela.height/2};

    //VARIAVEIS DO MODO LIVRE
    Vector2 inicio;
    Vector2 fim = {0,0};

    Vector2 inicioJogo = {0,0};
    
    Vector2 posicao_retangulo;
    
    FILE *arquivo;
    
    int atual = 0, clique = 0, sair = 0;
    SetExitKey(NULL);

    while(!WindowShouldClose() && !sair)
    {
        //update
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();
        //camera.offset = (Vector2){x + tela.width/2,y + tela.height/2};

        if(IsKeyDown(KEY_PAGE_UP)) camera.zoom += 0.001;

        if(IsKeyDown(KEY_PAGE_DOWN) && camera.zoom > 0) camera.zoom -= 0.001;


        if(IsKeyPressed(KEY_ONE)) 
        {
            retangulo[atual] = paredeH; 
            modo = 2;
        }
        if(IsKeyPressed(KEY_TWO)) 
        {
            retangulo[atual] = paredeV; 
            modo = 2;
        }
        if(IsKeyPressed(KEY_THREE))
        {
            
        }
        if(IsKeyPressed(KEY_ESCAPE))
        {
            if(modo != 1) modo = 1;
            else sair = 1;
        }

        //movimentação da camera
        if(IsKeyDown(KEY_W)) camera.offset.y += 2;
        if(IsKeyDown(KEY_S)) camera.offset.y -= 2;
        if(IsKeyDown(KEY_A)) camera.offset.x += 2;
        if(IsKeyDown(KEY_D)) camera.offset.x -= 2;

        //MOVIMENTAÇÃO DE OBJETOS
        if(IsKeyPressed(KEY_UP)) {
            posicao_retangulo.y -= 32; 
            modo = 3;
        }
        if(IsKeyPressed(KEY_DOWN)) {
            posicao_retangulo.y += 32; 
            modo = 3;
        }
        if(IsKeyPressed(KEY_LEFT)) {
            posicao_retangulo.x -= 32; 
            modo = 3;
        }
        if(IsKeyPressed(KEY_RIGHT)) {
            posicao_retangulo.x += 32; 
            modo = 3;
        }


        arquivo = fopen("retangulos_da_fase.txt","a");

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
                    fprintf(arquivo,"\n%.f, %.f, %.f, %.f,",retangulo[atual].x, retangulo[atual].y, retangulo[atual].width, retangulo[atual].height);
                    atual++;
                }
                clique = !clique;
                
            }else{
                fim = GetMousePosition();
                fim.x = (fim.x -camera.offset.x)/camera.zoom;
                fim.y = (fim.y -camera.offset.y)/camera.zoom;
            }
            retangulo[atual] = (Rectangle){inicio.x, inicio.y, fim.x -inicio.x, fim.y -inicio.y};
        }
        else if(modo == 2)
        {
            retangulo[atual].x = GetMouseX();
            retangulo[atual].y = GetMouseY();
            retangulo[atual].x = (retangulo[atual].x -camera.offset.x + camera.target.x)/camera.zoom;
            retangulo[atual].y = (retangulo[atual].y -camera.offset.y + camera.target.y)/camera.zoom;
            
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                fprintf(arquivo,"\n%.f, %.f, %.f, %.f,",retangulo[atual].x, retangulo[atual].y, retangulo[atual].width, retangulo[atual].height);
                atual++;
            }
        }
        else if(modo == 3)
        {
            retangulo[atual].x = posicao_retangulo.x;
            retangulo[atual].y = posicao_retangulo.y;
            if(IsKeyPressed(KEY_ENTER))
            {
                fprintf(arquivo,"\n%.f, %.f, %.f, %.f,",retangulo[atual].x, retangulo[atual].y, retangulo[atual].width, retangulo[atual].height);
                retangulo[atual +1] = retangulo[atual];
                atual++;
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
                fprintf(arquivo,"(DELETADO)");
                if(atual > 0)
                {
                    retangulo[atual] = (Rectangle){0,0,0,0};
                    atual--;
                }   
            }
        }
        fclose(arquivo);

        //---------------------Desenho da Tela-------------------
        BeginDrawing();
            ClearBackground((Color){50,50,50,255});
            BeginMode2D(camera);

                desenhaGrid();

                for(int i = 0; i < MAX_RETANGULOS; i++)
                {
                    if(!clique && i == atual && modo == 1)
                    {
                        i++; // pula o retangulo atual
                    }

                    DrawRectanglePro(retangulo[i],(Vector2){0,0},0,BLACK);
                    
                }
                DrawCircle(0,0,5,GREEN);
                DrawCircleV(inicioJogo,5,BLUE);
            EndMode2D();

            DrawText(FormatText("Numero de retangulos: %i",atual),10,10,20,YELLOW);
            if(modo == 1){
                DrawText("Modo livre",10,30,20,YELLOW);
            }
            else if (modo == 2){
                DrawText("Modo predefinido",10,30,20,YELLOW);
            }
            else if(modo == 3){
                DrawText("Controle por teclado",10,30,20,YELLOW);
            }
            
            DrawText((FormatText("Zoom: %.2f",camera.zoom)),10,50,20,YELLOW);

            if(IsKeyDown(KEY_F1))
            {
                DrawText("Clique esquerdo = criar um retangulo", tela.width -MeasureText("Clique esquerdo = criar um retangulo",20)-10, 10,20,YELLOW);
                DrawText("Clique direito = posição inicial do jogador", tela.width -MeasureText("Clique direito = posição inicial do jogador",20)-10, 40,20,YELLOW);
                DrawText("Del = Cancela retangulo atual / apaga anteriores", tela.width -MeasureText("Del = Cancela retangulo atual / apaga anteriores",20)-10, 70,20,YELLOW);
                DrawText("PAGE UP/DOWN = alterar zoom", tela.width -MeasureText("PAGE UP/DOWN = alterar zoom",20)-10, 100,20,YELLOW);
            }
            if(IsKeyUp(KEY_F1))
            {
                DrawText("Presione F1 para Ajuda",tela.width - 240, 10,20,YELLOW);
            }
        EndDrawing();
        if(sair) sair = telaSair();
    }
    arquivo = fopen("retangulos_da_fase.txt","a");
    fprintf(arquivo,"\nPosição inicial do Jogador = (Vector2){%.f,%.f}", inicioJogo.x , inicioJogo.y);
    fclose(arquivo);
    CloseWindow();
    
    return 0;
}

int telaSair()
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