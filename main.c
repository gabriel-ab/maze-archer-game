#include <raylib.h>
#include <stdio.h>

// CONFIGURAÇÕES DO PROGRAMA
#define MAX_RETANGULOS 100
#define MAX_ITENS 50
#define MAX_INIMIGOS 100

#include "lib/mapa.h"
#include "lib/tela.h"
#include "lib/data.c"
#include "lib/functions.c"



int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width, tela.height, "Criador de fases");

    Rectangle retangulo = {0, 0, 32, 32};

    Mapa fase;

    //================ZERANDO VALORES====================
        for (int i = 0; i < MAX_RETANGULOS; i++)
        {
            fase.parede[i] = (Rectangle){0, 0, 0, 0};
            fase.piso[i] = (Rectangle){0, 0, 0, 0};
        }
        for (int i = 0; i < MAX_ITENS; i++){
            fase.flecha[i] = (Vector2){0,0};
            fase.vida[i] = (Vector2){0,0};
        }
        for (int i = 0; i < MAX_INIMIGOS; i++) fase.inimigo[i] = (Vector2){0,0};

        fase.parede_atual = 0;
        fase.piso_atual = 0; 
        fase.vida_atual = 0;
        fase.inimigo_atual = 0;
        fase.flecha_atual = 0; 
        fase.inicio = (Vector2){0,0};
        fase.fim = (Vector2){0,0};
    //======================================================

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){tela.width / 2, tela.height / 2};

    // VARIAVEIS DE SUPORTE
    int tipo = 1, sair = 0;
    Vector2 bufferPosicao;
    int opcaoPonto;
    double tempoAnt = 0;
    SetTargetFPS(120);

    SetExitKey(0);

    while (!WindowShouldClose())
    {
        //update
        atualizaCamera(&camera);
        
        //AJUSTE DE ZOOM
        if (GetMouseWheelMove() > 0 ) camera.zoom += 0.1; 
        if (GetMouseWheelMove() < 0 && camera.zoom > 0.1 ) camera.zoom -= 0.1; 

        if (IsKeyDown(KEY_PAGE_UP)) camera.zoom += 0.01;
        if (IsKeyDown(KEY_PAGE_DOWN) && camera.zoom > 0)camera.zoom -= 0.01;

        if(GetKeyPressed() != -1)
        {
            bufferPosicao.x = retangulo.x;
            bufferPosicao.y = retangulo.y;

            //---==--------RETANGULOS PREDEFINIDOS--------------
            switch (tipo)
            {
                case PAREDE:
                    if (IsKeyPressed(KEY_ONE)) retangulo = paredeH3;
                    if (IsKeyPressed(KEY_TWO)) retangulo = paredeV3;
                    if (IsKeyPressed(KEY_THREE)) retangulo = paredeH5;
                    if (IsKeyPressed(KEY_FOUR)) retangulo = paredeV5;
                    if (IsKeyPressed(KEY_FIVE)) retangulo = paredeH8;
                    if (IsKeyPressed(KEY_SIX)) retangulo = paredeV8;
                    break;

                case PISO:
                    if (IsKeyPressed(KEY_ONE)) retangulo = piso2_2;
                    if (IsKeyPressed(KEY_TWO)) retangulo = piso4_4;
                    if (IsKeyPressed(KEY_THREE)) retangulo = piso6_6;
                    if (IsKeyPressed(KEY_FOUR)) retangulo = piso8_8;
                    if (IsKeyPressed(KEY_FIVE)) retangulo = piso6_16;
                    if (IsKeyPressed(KEY_SIX)) retangulo = piso16_6;
                    break;
            }
            retangulo.x = bufferPosicao.x;
            retangulo.y = bufferPosicao.y;
        }

        //MOVIMENTAÇÃO DA CAMERA
            if (IsKeyDown(KEY_W)) camera.target.y -= 10;
            if (IsKeyDown(KEY_S)) camera.target.y += 10;
            if (IsKeyDown(KEY_A)) camera.target.x -= 10;
            if (IsKeyDown(KEY_D)) camera.target.x += 10;
        //

        //EDIÇÃO DO TAMANHO E MOVIMENTAÇÃO DO OBJETO
        if (GetTime() - tempoAnt >= 0.05)
        {
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            {
                if (IsKeyDown(KEY_UP) && retangulo.height > 32) retangulo.height -= 32;
                if (IsKeyDown(KEY_DOWN)) retangulo.height += 32;
                if (IsKeyDown(KEY_LEFT) && retangulo.width > 32) retangulo.width -= 32;
                if (IsKeyDown(KEY_RIGHT)) retangulo.width += 32;
            }
            else
            {
                //MOVIMENTAÇÃO DO OBJETO
                if (IsKeyDown(KEY_UP)) retangulo.y -= 32;
                if (IsKeyDown(KEY_DOWN)) retangulo.y += 32;
                if (IsKeyDown(KEY_LEFT)) retangulo.x -= 32;
                if (IsKeyDown(KEY_RIGHT)) retangulo.x += 32;
            }
            tempoAnt = GetTime();
        }
        //

        if (IsKeyPressed(KEY_ENTER))
        {
            switch (tipo)
            {
            case PAREDE:
                fase.parede[fase.parede_atual++] = retangulo;
                break;
            case PISO:
                fase.piso[fase.piso_atual++] = retangulo;
                break;
            case INIMIGO:
                fase.inimigo[fase.inimigo_atual].x = (GetMouseX() - camera.offset.x) / camera.zoom;
                fase.inimigo[fase.inimigo_atual].y = (GetMouseY() - camera.offset.y) / camera.zoom;
                fase.inimigo_atual++;
                break;
                
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            fase.inimigo[fase.inimigo_atual].x = (GetMouseX() - camera.offset.x) / camera.zoom;
            fase.inimigo[fase.inimigo_atual].y = (GetMouseY() - camera.offset.y) / camera.zoom;
            fase.inimigo_atual++;
        }

        //-----------------TELA DE OPÇÕES----------------//
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            mousePos = (Vector2){(mousePos.x - camera.offset.x) / camera.zoom, (mousePos.y - camera.offset.y) / camera.zoom};

            telaBotaoDireito(&opcaoPonto);
            switch (opcaoPonto)
            {
                case OPCAO_INICIO:
                    fase.inicio = mousePos;
                    break;

                case OPCAO_FIM:
                    fase.fim = mousePos;
                    break;

                case OPCAO_VIDA:
                    fase.vida[fase.vida_atual++] = mousePos;
                    break;
            }
        }

        if (IsKeyPressed(KEY_F)) telaCheia();

        //CANCELA RETANGULO ATUAL OU APAGA ULTIMO RETANGULO
        if (IsKeyPressed(KEY_DELETE))
        {
            switch (tipo)
            {
            case PAREDE:
                if (fase.parede_atual > 0)
                {
                    fase.parede[--fase.parede_atual] = (Rectangle){0, 0, 0, 0};
                }
                break;
            case PISO:
                if (fase.piso_atual > 0)
                {
                    fase.piso[--fase.piso_atual] = (Rectangle){0, 0, 0, 0};
                }
                break;
            case INIMIGO:
                if (fase.inimigo_atual > 0)
                {
                    fase.inimigo[--fase.inimigo_atual] = (Vector2){0, 0};
                }
                break;
            }
        }

        //-------------TROCAR TIPO DE RETANGULO--------------
        if (IsKeyPressed(KEY_ESCAPE))
        {
            sair = telaSair(fase);
            if (sair) break;
        }
        if (IsKeyPressed(KEY_TAB))
        {
            telaOpcoes(&tipo, &fase);
        }

        

        //---------------------Desenho da Tela-------------------
        BeginDrawing();
            ClearBackground((Color){50, 50, 50, 255});
            BeginMode2D(camera);

                desenhaGrid();

                for (int i = 0; i < fase.parede_atual; i++)
                {
                    DrawRectangleRec(fase.parede[i], BLACK);
                    DrawRectangleLinesEx(fase.parede[i], 1, (Color){100, 240, 100, 255});
                    if (fase.parede[i].width == 0 && fase.parede[i].height == 0)
                        break;
                }
                for (int i = 0; i < fase.piso_atual; i++)
                {
                    DrawRectangleRec(fase.piso[i], BLACK);
                    DrawRectangleLinesEx(fase.piso[i], 1, (Color){100, 100, 200, 255});
                }
                for (int i = 0; i < fase.inimigo_atual; i++)
                {
                    DrawCircleV(fase.inimigo[i], 8, RED);
                    DrawCircleV(fase.inimigo[i], 4, PURPLE);
                }

                DrawRectangleRec(retangulo, BLACK);
                DrawRectangleLinesEx(retangulo, 1, (Color){180, 240, 100, 255});

                DrawCircle(0, 0, 2, GREEN);

                DrawRectangleRec((Rectangle){fase.inicio.x - 8, fase.inicio.y - 8, 16, 16}, DARKBLUE);
                DrawCircleV(fase.inicio, 5, BLUE);
                DrawText("INICIO", fase.inicio.x - 16, fase.inicio.y + 10, 12, WHITE);

                DrawRectangleRec((Rectangle){fase.fim.x - 8, fase.fim.y - 8, 16, 16}, DARKBLUE);
                DrawCircleV(fase.fim, 5, BLUE);
                DrawText("FINAL", fase.fim.x - 15, fase.fim.y + 10, 12, WHITE);

            EndMode2D();

            DrawText(FormatText("Numero de paredes: %i", fase.parede_atual), 10, 10, 20, tipo == PAREDE ? GREEN :DARKGREEN);
            DrawText(FormatText("Numero de pisos: %i", fase.piso_atual), 10, 30, 20, tipo == PISO ? GREEN :DARKGREEN);
            DrawText(FormatText("Numero de inimigos: %i", fase.inimigo_atual), 10, 50, 20, tipo == INIMIGO ? GREEN :DARKGREEN);

            DrawText((FormatText("Zoom: %.2f", camera.zoom)), 10, 70, 20, YELLOW);

            if (IsKeyDown(KEY_F1))
            {
                desenhaTelaAjuda();
            }
            if (IsKeyUp(KEY_F1))
            {
                DrawText("Presione F1 para Ajuda", tela.width - 240, 10, 20, YELLOW);
            }
            DrawFPS(10,tela.height - 40);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}