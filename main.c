#include <raylib.h>
#include "headers/tela.h"
#include <stdio.h>

#define MAX_RETANGULOS 100


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width,tela.height,"Criador de fases");

    Rectangle retangulo[MAX_RETANGULOS];
    Rectangle paredeH = {0,0,32,96};
    Rectangle paredeV = {0,0,96,32};
    Rectangle temp = {0,0,0,0};
    
    int modo = 1;

    //zerando valores
    for(int i = 0; i < MAX_RETANGULOS; i++){
        retangulo[i] = (Rectangle){0,0,0,0};
    }

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){tela.width/2,tela.height/2};

    //coordenadas de cada clique
    Vector2 inicio;
    Vector2 fim = {0,0};
    
    FILE *arquivo;
    
    int atual = 0, clique = 0;
    int x=0,y=0;
    SetExitKey(NULL);

    while(!WindowShouldClose())
    {
        //update
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();
        camera.offset = (Vector2){x + tela.width/2,y + tela.height/2};

        if(IsKeyDown(KEY_UP)) camera.zoom += 0.001;
        if(IsKeyDown(KEY_DOWN)) camera.zoom -= 0.001;

        if(IsKeyPressed(KEY_ONE)) 
        {
            temp = paredeH; 
            modo = 2;
        }
        if(IsKeyPressed(KEY_TWO)) 
        {
            temp = paredeV; 
            modo = 2;
        }
        if(IsKeyPressed(KEY_M)) modo = 1;

        //movimentação da camera
        if(IsKeyDown(KEY_W)) y -= 2;
        if(IsKeyDown(KEY_S)) y += 2;
        if(IsKeyDown(KEY_A)) x -= 2;
        if(IsKeyDown(KEY_D)) x += 2;

        arquivo = fopen("retangulos_da_fase.txt","a");

        if (modo == 1){
            //Recebe coordenadas do retangulo
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                
                if(clique == 0)
                {
                    inicio = GetMousePosition();
                    inicio.x = (inicio.x -camera.offset.x + camera.target.x)/camera.zoom;
                    inicio.y = (inicio.y -camera.offset.y + camera.target.y)/camera.zoom;
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
            temp.x = GetMouseX();
            temp.y = GetMouseY();
            temp.x = (temp.x -camera.offset.x + camera.target.x)/camera.zoom;
            temp.y = (temp.y -camera.offset.y + camera.target.y)/camera.zoom;
            
            retangulo[atual] = temp;
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                fprintf(arquivo,"\n%.f, %.f, %.f, %.f,",retangulo[atual].x, retangulo[atual].y, retangulo[atual].width, retangulo[atual].height);
                atual++;
            }
        }

        
        

        if(IsKeyPressed(KEY_F)) telaCheia();

        //cancela retangulo
        if(IsKeyPressed(KEY_Q)) clique = 0;

        if(IsKeyPressed(KEY_DELETE))
        {
            fprintf(arquivo,"(DELETADO)");
            if(atual > 0)
            {
                retangulo[atual] = (Rectangle){0,0,0,0};
                atual--;
            }
        }
        fclose(arquivo);

        //---------------------Desenho da Tela-------------------
        BeginDrawing();
            ClearBackground((Color){50,50,50,255});
            BeginMode2D(camera);
                for(int i = 0; i < MAX_RETANGULOS; i++)
                {
                    if(!clique && i == atual && modo == 1)
                    {
                        i++; // pula o retangulo atual
                    }

                    DrawRectanglePro(retangulo[i],(Vector2){0,0},0,BLACK);
                    
                }
                DrawCircle(0,0,5,GREEN);
            EndMode2D();

            DrawText(FormatText("Numero de retangulos: %i",atual),10,10,20,YELLOW);
            DrawText(modo == 1 ? "Modo livre" : "Modo predefinido",10,30,20,YELLOW);
            if(IsKeyDown(KEY_F1))
            {
                DrawText("Clique para criar um retangulo.", tela.width -MeasureText("Clique para criar um retangulo.",20)-10, 10,20,YELLOW);
                DrawText("'q' = Cancela retangulo atual", tela.width -MeasureText("'x' = Cancela retangulo atual",20)-10, 30,20,YELLOW);
                DrawText("Delete = apaga ultimo retângulo", tela.width -MeasureText("Delete = apaga ultimo retângulo",20)-10, 50,20,YELLOW);
            }
        EndDrawing();
        
    }
    CloseWindow();
    
    return 0;
}