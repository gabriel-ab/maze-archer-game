#include "../../include/som.h"
#include "../../include/tela.h"
#include "../../include/define.h"
#include "../../include/draw.h"
#include "../../include/data.h"
#include <string.h>



void selecao_de_mapa(){
    int n_fases = 0;

    char **arquivos = GetDirectoryFiles("resources/fases/", &n_fases); //array de strings

    int seletor = 0;
    bool confirma = false;

    Camera2D rolador = { 0 };
    rolador.zoom = 1;
    Vector2 mousePos = GetMousePosition();
    bool rolagem_automatica = true;

    while (!confirma && !WindowShouldClose())
    {
        if (mousePos.x != GetMousePosition().x) rolagem_automatica = false;

        if (rolagem_automatica){
            rolador.target.y = rolador.target.y*0.8 +seletor*12 -GetScreenHeight()*0.05;
        }
        else if (CheckCollisionPointCircle(mousePos,(Vector2){100,-50},200)){
            rolador.target.y -= 5;
        }
        else if (CheckCollisionPointCircle(mousePos,(Vector2){100,GetScreenHeight()+50},200)){
            rolador.target.y += 5;
        }
        else{
            static int fps = 0;
            fps++;
            if(fps > 180) //espera 3 segundos
            {
                rolagem_automatica = true;
                fps = 0;
            }
        }
        
        mousePos = GetMousePosition();
        BeginDrawing();
            ClearBackground(BLACK);
            drawMenuBackground(WHITE);
            DrawRectangleGradientV(0,0,GetScreenWidth(), GetScreenHeight(), (Color){150,150,150,100}, (Color){0,0,0,100});
                BeginMode2D(rolador);
                for (int i = 0; i < n_fases; i++)
                {
                    drawButtonD(
                        arquivos[i],
                        (Rectangle){GetScreenWidth()/6, 240+ (i-2)*60, 240, 30},
                        seletor == i);

                    if (CheckCollisionPointRec(
                        (Vector2){
                            mousePos.x, 
                            mousePos.y +rolador.target.y
                        },
                        (Rectangle){
                            GetScreenWidth()/6 -120, 
                            240+ (i-2)*60 -15, 
                            240, 
                            30
                        }))
                    {
                        seletor = i;
                        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) confirma = true;
                    }
                }
                EndMode2D();
                DrawFPS(10,10);
        EndDrawing();
        playMusic(1);
        
        menuControl(0, &seletor, n_fases -1);

        rolador.target.y -= GetMouseWheelMove() * 10;

        if(IsKeyPressed(KEY_ESCAPE)){
            telaAtual = TELA_MENU;
            break;
        }
        if(IsKeyPressed(KEY_ENTER)) {
            confirma = true;

            if (arquivos[seletor][0] == '.') {
                confirma = false;
                int t = 0;
                while (t++ < 90) {
                    BeginDrawing();
                    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(), Fade(BLACK,0.2));
                    DrawText("Invalid File", GetScreenWidth() * 0.45, GetScreenHeight() * 0.48, 20, WHITE);
                    EndDrawing();
                    if (IsKeyPressed(KEY_ESCAPE)) break;
                }
            }
        }
    }
    if(confirma){
        //Carrega a fase do endereço selecionado
        strcpy(diretorio, "resources/fases/");
        strcat(diretorio, arquivos[seletor]);
        telaAtual = TELA_FASE_CUSTOM;
    }
}