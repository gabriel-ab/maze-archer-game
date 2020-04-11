#include <raylib.h>
#include <stdio.h>

#include "lib/object.h"
#include "lib/screens.h"
#include "lib/draw.h"
#include "lib/window.h"
#include "lib/data.h"

int main()
{
    tela = (Rectangle){larguraTela/3, alturaTela/3, larguraTela, alturaTela};
    telaAnterior = (Rectangle){larguraTela/3, alturaTela/3, larguraTela, alturaTela};
    Is_Fullscreen = 0;
    posCam = (Vector2){0,0};
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
            fase.portal[i] = (Vector2){0,0};
        }
        for (int i = 0; i < MAX_INIMIGOS; i++) fase.inimigo[i] = (Vector2){0,0};

        fase.parede_atual = 0;
        fase.piso_atual = 0; 
        fase.vida_atual = 0;
        fase.inimigo_atual = 0;
        fase.flecha_atual = 0; 
        fase.portal_atual = 0; 
        fase.inicio = (Vector2){0,0};
        fase.fim = (Vector2){0,0};
    //======================================================

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){tela.width / 2, tela.height / 2};

    // VARIAVEIS DE SUPORTE
    int tipo = 0, sair = 0;
    Vector2 bufferPosicao;
    int opcaoPonto;
    double tempoAnt = 0;

    // VARIAVEL DE SELEÇÃO
    //{OBJETO, indice}
    //ex: {PAREDE, 7}
    Objeto selecionado = {-1,0};
    // TO DO se o selecionado for deletado toda a sequencia move seu indice em -1

    SetTargetFPS(60);

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
            if (IsKeyDown(KEY_W)) posCam.y -= 10;
            if (IsKeyDown(KEY_S)) posCam.y += 10;
            if (IsKeyDown(KEY_A)) posCam.x -= 10;
            if (IsKeyDown(KEY_D)) posCam.x += 10;
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
            Vector2 mousePos = GetMousePosition();
            mousePos = (Vector2){(mousePos.x - camera.offset.x) / camera.zoom, (mousePos.y - camera.offset.y) / camera.zoom};
            switch (tipo)
            {
            case PAREDE:
                fase.parede[fase.parede_atual++] = retangulo;
                break;
            case PISO:
                fase.piso[fase.piso_atual++] = retangulo;
                break;
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(IsKeyDown(KEY_LEFT_CONTROL)){
                selecionado = selecionarObjeto(fase, camera);
            }else{
                Vector2 mousePos = GetMousePosition();
                mousePos = (Vector2){(mousePos.x - camera.offset.x) / camera.zoom, (mousePos.y - camera.offset.y) / camera.zoom};
                switch (tipo)
                {
                case INIMIGO:
                    fase.inimigo[fase.inimigo_atual++] = mousePos;
                    break;
                case VIDA:
                    fase.vida[fase.vida_atual++] = mousePos;
                    break;
                case FLECHA:
                    fase.flecha[fase.flecha_atual++] = mousePos;
                    break;
                case PORTAL:
                    fase.portal[fase.portal_atual++] = mousePos;
                    break;
                }
            }
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
            }
        }

        if (IsKeyPressed(KEY_F)) telaCheia();

        //APAGA ULTIMO RETANGULO
        if (IsKeyPressed(KEY_DELETE))
        {
            switch (tipo)
            {
            case PAREDE:
                if (fase.parede_atual > 0){
                    fase.parede[--fase.parede_atual] = (Rectangle){0, 0, 0, 0};
                }
                break;
            case PISO:
                if (fase.piso_atual > 0){
                    fase.piso[--fase.piso_atual] = (Rectangle){0, 0, 0, 0};
                }
                break;
            case INIMIGO:
                if (fase.inimigo_atual > 0){
                    fase.inimigo[--fase.inimigo_atual] = (Vector2){0, 0};
                }
                break;
            case VIDA:
                if (fase.vida_atual > 0){
                    fase.vida[--fase.vida_atual] = (Vector2){0, 0};
                }
                break;
            case FLECHA:
                if (fase.flecha_atual > 0){
                    fase.flecha[--fase.flecha_atual] = (Vector2){0, 0};
                }
                break;
            case PORTAL:
                if (fase.portal_atual > 0){
                    fase.portal[--fase.portal_atual] = (Vector2){0, 0};
                }
                break;
            }
        }

        //-------------------------------------------------------
        if (IsKeyPressed(KEY_ESCAPE))
        {
            sair = telaSair(fase);
            if (sair) break;
        }
        if (IsKeyPressed(KEY_TAB))
        {
            telaOpcoes(&tipo, &fase);
        }

        CheckFileOnScreen(&fase);

        //---------------------Desenho da Tela-------------------
        BeginDrawing();
            ClearBackground((Color){50, 50, 50, 255});
            BeginMode2D(camera);

                desenhaGrid();

                for (int i = 0; i < fase.piso_atual; i++){
                    drawFloor(fase.piso[i]);
                }
                for (int i = 0; i < fase.parede_atual; i++){
                    drawWall(fase.parede[i]);
                }
                for (int i = 0; i < fase.inimigo_atual; i++){
                    drawEnemie(fase.inimigo[i]);
                }
                for (int i = 0; i < fase.vida_atual; i++){
                    drawLife(fase.vida[i]);
                }
                for (int i = 0; i < fase.flecha_atual; i++){
                    drawArrow(fase.flecha[i]);
                }
                for (int i = 0; i < fase.portal_atual; i++){
                    drawPortal(fase.portal[i]);
                }
                
                switch (selecionado.tipo)
                {
                case PAREDE:
                    DrawRectangleGradientEx(fase.parede[selecionado.indice], DARKBLUE, BLACK, BLACK, DARKBLUE);
                    DrawRectangleLinesEx(fase.parede[selecionado.indice], 2, LIGHTGRAY);
                    break;
                case PISO:
                    DrawRectangleGradientEx(fase.piso[selecionado.indice], DARKGREEN, BLACK, BLACK, DARKGREEN);
                    DrawRectangleLinesEx(fase.piso[selecionado.indice], 2, LIGHTGRAY);
                    break;
                case INIMIGO:
                    DrawCircleGradient(fase.inimigo[selecionado.indice].x, fase.inimigo[selecionado.indice].y, 12,PURPLE, BLACK);
                    break;
                case VIDA:
                    DrawCircleGradient(fase.vida[selecionado.indice].x, fase.vida[selecionado.indice].y, 12,RED, BLACK);
                    break;
                case FLECHA:
                    DrawCircleGradient(fase.flecha[selecionado.indice].x, fase.flecha[selecionado.indice].y, 12,GREEN, BLACK);
                    break;
                }

                DrawRectangleRec(retangulo, (Color){0,0,0,100});
                DrawRectangleLinesEx(retangulo, 2, (Color){180, 240, 100, 255});

                DrawCircle(0, 0, 2, GREEN);

                drawInfoPoint("INICIO", fase.inicio);
                drawInfoPoint("FINAL", fase.fim);

            EndMode2D();

            DrawText(FormatText("Paredes: %i", fase.parede_atual),    10, 10 +0*ESPACAMENTO_P1, 20, tipo == PAREDE ? GREEN :DARKGREEN);
            DrawText(FormatText("Pisos: %i",  fase.piso_atual),       10, 10 +1*ESPACAMENTO_P1, 20, tipo == PISO ? GREEN :DARKGREEN);
            DrawText(FormatText("Inimigos: %i", fase.inimigo_atual),  10, 10 +2*ESPACAMENTO_P1, 20, tipo == INIMIGO ? GREEN :DARKGREEN);
            DrawText(FormatText("Vidas: %i", fase.vida_atual),        10, 10 +3*ESPACAMENTO_P1, 20, tipo == VIDA ? GREEN :DARKGREEN);
            DrawText(FormatText("Flechas: %i", fase.flecha_atual),    10, 10 +4*ESPACAMENTO_P1, 20, tipo == FLECHA ? GREEN :DARKGREEN);
            DrawText(FormatText("Portais: %i", fase.portal_atual),    10, 10 +5*ESPACAMENTO_P1, 20, tipo == PORTAL ? GREEN :DARKGREEN);

            DrawText((FormatText("Zoom: %.2f", camera.zoom)), 10, 10 +7*ESPACAMENTO_P1, 20, LIGHTGRAY);
            DrawText((FormatText("Selecionado: %i %i", selecionado.tipo, selecionado.indice)), 10, 10 +8*ESPACAMENTO_P1, 20, LIGHTGRAY);

            if (IsKeyDown(KEY_F1))
                desenhaTelaAjuda();
            else
                DrawText("Presione F1 para Ajuda", tela.width - 240, 10, 20, LIGHTGRAY);

            DrawFPS(10,tela.height - 40);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}