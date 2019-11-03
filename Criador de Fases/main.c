#include <raylib.h>
#include "headers/tela.h"
#include <stdio.h>

#define MAX_RETANGULOS 100


int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    
    InitWindow(tela.width,tela.height,"Criador de fases");

    Rectangle retangulo[MAX_RETANGULOS];

    //zerando valores
    for(int i = 0; i < MAX_RETANGULOS; i++){
        retangulo[i] = (Rectangle){0,0,0,0};
    }
    //coordenadas
    Vector2 inicio;
    Vector2 fim = {0,0};
    
    FILE *arquivo;
    
    int atual = 0, clique = 0;

    while(!WindowShouldClose())
    {
        arquivo = fopen("retangulos_da_fase.txt","a");

        //Inicia o desenho do retangulo
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(clique == 0)
            {
                inicio = GetMousePosition();
            }
            else
            {
                fprintf(arquivo,"%.f, %.f, %.f, %.f,\n",retangulo[atual].x, retangulo[atual].y, retangulo[atual].width, retangulo[atual].height);
                atual++;
            }
            clique = !clique;
            
        }else{
            fim = GetMousePosition();

        }
        retangulo[atual] = (Rectangle){inicio.x, inicio.y, fim.x -inicio.x, fim.y -inicio.y};
        
        
        fclose(arquivo);

        if(IsKeyPressed(KEY_F)) telaCheia();

        //cancela retangulo
        if(IsKeyPressed(KEY_Q)) clique = 0;

        BeginDrawing();
            ClearBackground((Color){50,50,50,255});

            for(int i = 0; i < MAX_RETANGULOS; i++)
            {
                if(!clique && i == atual)
                {
                    i++; // pula o retangulo atual
                }

                DrawRectanglePro(retangulo[i], (Vector2){0,0},0,BLACK);
                DrawText(FormatText("Numero de retangulos: %i",atual),10,10,20,YELLOW);
                DrawText("Clique para criar um retangulo.", tela.width -MeasureText("Clique para criar um retangulo." -10 ,14),10,14,YELLOW);
                /*
                DrawText
                (
                    FormatText("%.f %.f %.f %.f",retangulo[i].x, retangulo[i].y, retangulo[i].width, retangulo[i].height),
                    12,i*10,10,BLACK
                );
                */
            }

        EndDrawing();
        
    }
    CloseWindow();
    
    return 0;
}