#include <raylib.h>
#include "headers/tela.h"
#include <stdio.h>

#define MAX_RETANGULOS 100
#define MAX_VIDAS 20
#define MAX_INIMIGOS 50

#define paredeH3 (Rectangle) { 0, 0, 32, 128 }
#define paredeV3 (Rectangle) { 0, 0, 128, 32 }
#define paredeH5 (Rectangle) { 0, 0, 32, 6 * 32 }
#define paredeV5 (Rectangle) { 0, 0, 6 * 32, 32 }
#define paredeH8 (Rectangle) { 0, 0, 32, 320 }
#define paredeV8 (Rectangle) { 0, 0, 320, 32 }

#define piso2_2 (Rectangle) { 0, 0, 64, 64 }
#define piso4_4 (Rectangle) { 0, 0, 4 * 32, 4 * 32 }
#define piso6_6 (Rectangle) { 0, 0, 6 * 32, 6 * 32 }
#define piso8_8 (Rectangle) { 0, 0, 8 * 32, 8 * 32 }
#define piso16_6 (Rectangle) { 0, 0, 16 * 32, 6 * 32 }
#define piso6_16 (Rectangle) { 0, 0, 6 * 32, 16 * 32 }

typedef enum
{
    PAREDE = 1,
    PISO = 2,
    INIMIGO = 3
} TipoDeRetangulo;

typedef enum
{
    OPCAO_INICIO = 0,
    OPCAO_FIM,
    OPCAO_VIDA,
    OPCAO_INIMIGO
} Opcoes;

void desenhaGrid(void);
void desenhaTelaAjuda(void);
void selecionarTipo(int *tipo);
void telaOpcao(int *opcao);
int telaSair();

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(tela.width, tela.height, "Criador de fases");

    Rectangle retangulo = {0, 0, 32, 32};

    Rectangle parede[MAX_RETANGULOS];
    int parede_atual = 0;

    Rectangle piso[MAX_RETANGULOS];
    int piso_atual = 0;

    Vector2 vida[20];
    int vida_atual = 0;

    Vector2 inimigo[20];
    int inimigo_atual = 0;

    //zerando valores
    for (int i = 0; i < MAX_RETANGULOS; i++)
    {
        parede[i] = (Rectangle){0, 0, 0, 0};
        piso[i] = (Rectangle){0, 0, 0, 0};
    }

    Camera2D camera;
    camera.zoom = 1;
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){tela.width / 2, tela.height / 2};

    Vector2 inicioFase = {0, 0};
    Vector2 fimFase = {0, 0};

    FILE *arquivo;

    int tipo = 1, sair = 0, salvar = 0;

    Vector2 bufferPosicao;
    int opcaoPonto;

    double tempoAnt = 0;

    SetExitKey(0);

    while (!WindowShouldClose())
    {
        //update
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();

        if (IsKeyDown(KEY_PAGE_UP)) camera.zoom += 0.001;
        if (IsKeyDown(KEY_PAGE_DOWN) && camera.zoom > 0)camera.zoom -= 0.001;

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

        //-------------TROCAR TIPO DE RETANGULO--------------
        if (IsKeyPressed(KEY_TAB))
        {
            selecionarTipo(&tipo);
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            sair = telaSair();
            if(sair == 2) salvar = 1;
            if (sair) break;
        }

        //MOVIMENTAÇÃO DA CAMERA
            if (IsKeyDown(KEY_W)) camera.offset.y += 2;
            if (IsKeyDown(KEY_S)) camera.offset.y -= 2;
            if (IsKeyDown(KEY_A)) camera.offset.x += 2;
            if (IsKeyDown(KEY_D)) camera.offset.x -= 2;
        //

        //EDIÇÃO DO TAMANHO E MOVIMENTAÇÃO DO OBJETO
        if (GetTime() - tempoAnt >= 0.1)
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
                parede[parede_atual++] = retangulo;
                break;
            case PISO:
                piso[piso_atual++] = retangulo;
                break;
            case INIMIGO:
                inimigo[inimigo_atual].x = (GetMouseX() - camera.offset.x) / camera.zoom;
                inimigo[inimigo_atual].y = (GetMouseY() - camera.offset.y) / camera.zoom;
                inimigo_atual++;
                break;
                
            }
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            inimigo[inimigo_atual].x = (GetMouseX() - camera.offset.x) / camera.zoom;
            inimigo[inimigo_atual].y = (GetMouseY() - camera.offset.y) / camera.zoom;
            inimigo_atual++;
        }

        //-----------------TELA DE OPÇÕES----------------//
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            mousePos = (Vector2){(mousePos.x - camera.offset.x) / camera.zoom, (mousePos.y - camera.offset.y) / camera.zoom};

            telaOpcao(&opcaoPonto);
            switch (opcaoPonto)
            {
                case OPCAO_INICIO:
                    inicioFase = mousePos;
                    break;

                case OPCAO_FIM:
                    fimFase = mousePos;
                    break;

                case OPCAO_VIDA:
                    vida[vida_atual++] = mousePos;
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
                if (parede_atual > 0)
                {
                    parede[--parede_atual] = (Rectangle){0, 0, 0, 0};
                }
                break;
            case PISO:
                if (piso_atual > 0)
                {
                    piso[--piso_atual] = (Rectangle){0, 0, 0, 0};
                }
                break;
            case INIMIGO:
                if (inimigo_atual > 0)
                {
                    inimigo[--inimigo_atual] = (Vector2){0, 0};
                }
                break;
            }
        }

        //---------------------Desenho da Tela-------------------
        BeginDrawing();
            ClearBackground((Color){50, 50, 50, 255});
            BeginMode2D(camera);

                desenhaGrid();

                for (int i = 0; i < parede_atual; i++)
                {
                    DrawRectangleRec(parede[i], BLACK);
                    DrawRectangleLinesEx(parede[i], 1, (Color){100, 240, 100, 255});
                    if (parede[i].width == 0 && parede[i].height == 0)
                        break;
                }
                for (int i = 0; i < piso_atual; i++)
                {
                    DrawRectangleRec(piso[i], BLACK);
                    DrawRectangleLinesEx(piso[i], 1, (Color){100, 100, 200, 255});
                }
                for (int i = 0; i < inimigo_atual; i++)
                {
                    DrawCircleV(inimigo[i], 8, RED);
                    DrawCircleV(inimigo[i], 4, PURPLE);
                }

                DrawRectangleRec(retangulo, BLACK);
                DrawRectangleLinesEx(retangulo, 1, (Color){180, 240, 100, 255});

                DrawCircle(0, 0, 2, GREEN);

                DrawRectangleRec((Rectangle){inicioFase.x - 8, inicioFase.y - 8, 16, 16}, DARKBLUE);
                DrawCircleV(inicioFase, 5, BLUE);
                DrawText("INICIO", inicioFase.x - 16, inicioFase.y + 10, 12, WHITE);

                DrawRectangleRec((Rectangle){fimFase.x - 8, fimFase.y - 8, 16, 16}, DARKBLUE);
                DrawCircleV(fimFase, 5, BLUE);
                DrawText("FINAL", fimFase.x - 15, fimFase.y + 10, 12, WHITE);

            EndMode2D();

            DrawText(FormatText("Numero de paredes: %i", parede_atual), 10, 10, 20, tipo == PAREDE ? GREEN :DARKGREEN);
            DrawText(FormatText("Numero de pisos: %i", piso_atual), 10, 30, 20, tipo == PISO ? GREEN :DARKGREEN);
            DrawText(FormatText("Numero de inimigos: %i", inimigo_atual), 10, 50, 20, tipo == INIMIGO ? GREEN :DARKGREEN);

            DrawText((FormatText("Zoom: %.2f", camera.zoom)), 10, 70, 20, YELLOW);

            if (IsKeyDown(KEY_F1))
            {
                desenhaTelaAjuda();
            }
            if (IsKeyUp(KEY_F1))
            {
                DrawText("Presione F1 para Ajuda", tela.width - 240, 10, 20, YELLOW);
            }

        EndDrawing();
    }

    //Impressão do MAPA
    if (salvar)
    {
        arquivo = fopen("retangulos_da_fase.txt", "a");
        fprintf(arquivo, "\nInicio de Jogo = (Vector2){%.f,%.f}", inicioFase.x, inicioFase.y);
        fprintf(arquivo, "\nFim do Jogo = (Vector2){%.f,%.f}", fimFase.x, fimFase.y);

        fprintf(arquivo, "\n\n//------------PAREDES----------//");
        fprintf(arquivo, "\nRectangle parede = {");
        for (int i = 0; i < parede_atual; i++)
        {
            fprintf(arquivo, "\n%.f, %.f, %.f, %.f,", parede[i].x, parede[i].y, parede[i].width, parede[i].height);
        }
        fprintf(arquivo, "\n}");

        fprintf(arquivo, "\n\n//-------------PISOS-----------//");
        fprintf(arquivo, "\nRectangle piso = {");
        for (int i = 0; i < piso_atual; i++)
        {
            fprintf(arquivo, "\n%.f, %.f, %.f, %.f,", piso[i].x, piso[i].y, piso[i].width, piso[i].height);
        }
        fprintf(arquivo, "\n}");


        fprintf(arquivo, "\n\n//-----------INIMIGOS----------//");
        fprintf(arquivo, "\nVector2 inimigos = {");
        for (int i = 0; i < inimigo_atual; i++)
        {
            fprintf(arquivo, "\n%.f, %.f,", inimigo[i].x, inimigo[i].y);
        }
        fprintf(arquivo, "\n}");

        fclose(arquivo);
    }
    CloseWindow();

    return 0;
}
void desenhaGrid(void)
{
    DrawLine(-2048, 0, 2048, 0, (Color){100, 100, 100, 255});
    DrawLine(0, -2048, 0, 2048, (Color){100, 100, 100, 255});

    DrawLine(256, -2048, 256, 2048, (Color){100, 100, 100, 255});
    DrawLine(-256, -2048, -256, 2048, (Color){100, 100, 100, 255});
    DrawLine(-2048, -256, 2048, -256, (Color){100, 100, 100, 255});
    DrawLine(-2048, 256, 2048, 250, (Color){100, 100, 100, 255});

    DrawLine(1024, -2048, 1024, 2048, (Color){100, 100, 100, 255});
    DrawLine(-1024, -2048, -1024, 2048, (Color){100, 100, 100, 255});
    DrawLine(-2048, -1024, 2048, -1024, (Color){100, 100, 100, 255});
    DrawLine(-2048, 1024, 2048, 1024, (Color){100, 100, 100, 255});
}

void selecionarTipo(int *tipo)
{
    int confirma = 0;
    int opcao = 1;
    Texture2D fundo = LoadTextureFromImage(GetScreenData());

    Rectangle botao[3] = {
        tela.width / 2 - MeasureText("PAREDE", 20) / 2,
        tela.height / 2 + 30,
        MeasureText("PAREDE", 20),
        20,
        tela.width / 2 - MeasureText("PISO", 20) / 2,
        tela.height / 2 + 50,
        MeasureText("PISO", 20),
        20,
        tela.width / 2 - MeasureText("INIMIGO", 20) / 2,
        tela.height / 2 + 70,
        MeasureText("INIMIGO", 20),
        20
    };

    while (!confirma)
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(fundo, 0,0, (Color){255,255,255,100});
            DrawText("SELECIONE O TIPO DE RETANGULO:", tela.width / 2 - MeasureText("SELECIONE O TIPO DE RETANGULO:", 25) / 2, tela.height / 2, 25, RED);
            DrawText(opcao == 1 ? "PAREDE" : "parede", tela.width / 2 - MeasureText("PAREDE", 20) / 2, tela.height / 2 + 30, 20, RED);
            DrawText(opcao == 2 ? "PISO" : "piso", tela.width / 2 - MeasureText("PISO", 20) / 2, tela.height / 2 + 50, 20, RED);
            DrawText(opcao == 3 ? "INIMIGO" : "inimigo", tela.width / 2 - MeasureText("INIMIGO", 20) / 2, tela.height / 2 + 70, 20, RED);
        EndDrawing();

        if (IsKeyPressed(KEY_UP) && opcao >= 2) opcao--;
        if (IsKeyPressed(KEY_DOWN) && opcao <= 2) opcao++;
        if (IsKeyPressed(KEY_ENTER)) confirma = 1;
        for( int i = 0; i < 3; i++){
            if (CheckCollisionPointRec(GetMousePosition(), botao[i])) opcao = i + 1;    
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) confirma = 1;

        if (confirma && opcao == 1) *tipo = PAREDE;
        if (confirma && opcao == 2) *tipo = PISO;
        if (confirma && opcao == 3) *tipo = INIMIGO;
    }
}

void desenhaTelaAjuda(void)
{
    #ifndef TEXTO_AJUDA
        #define TEXTO_AJUDA
        #define AJUDA_0 "1,2,3,4,5,6 = Retangulos Predefinidos de Paredes e Pisos"
        #define AJUDA_1 "TAB = Parede / Piso / Inimigo"
        #define AJUDA_2 "Setas = Movimenta Os Objetos"
        #define AJUDA_3 "Shift + Setas = Edição de tamanho do Objeto"
        #define AJUDA_4 "Clique Esquerdo = Retangulo Personalizado"
        #define AJUDA_5 "Clique Direito = Posição Do Inicio De Jogo"
        #define AJUDA_6 "Del = Cancela Retangulo Atual / Apaga Anteriores"
        #define AJUDA_7 "Page Up/Down = Zoom"
        #define AJUDA_8 "Enter = Fixa Retangulo"

        #define ESPACAMENTO 40
    #endif
    DrawRectangle(0, 0, tela.width, tela.height, (Color){30, 30, 30, 200});

    DrawText(AJUDA_0, tela.width / 2 - MeasureText(AJUDA_0, 20) / 2, tela.width / 5 - 3 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_1, tela.width / 2 - MeasureText(AJUDA_1, 20) / 2, tela.width / 5 - 1 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_2, tela.width / 2 - MeasureText(AJUDA_2, 20) / 2, tela.width / 5 + 0 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_3, tela.width / 2 - MeasureText(AJUDA_3, 20) / 2, tela.width / 5 + 1 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_4, tela.width / 2 - MeasureText(AJUDA_4, 20) / 2, tela.width / 5 + 2 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_5, tela.width / 2 - MeasureText(AJUDA_5, 20) / 2, tela.width / 5 + 3 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_6, tela.width / 2 - MeasureText(AJUDA_6, 20) / 2, tela.width / 5 + 4 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_7, tela.width / 2 - MeasureText(AJUDA_7, 20) / 2, tela.width / 5 + 6 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_8, tela.width / 2 - MeasureText(AJUDA_8, 20) / 2, tela.width / 5 + 7 * ESPACAMENTO, 20, (Color){200, 200, 200, 255});
}

int telaSair()
{
    Texture2D fundo = LoadTextureFromImage(GetScreenData());

    #ifndef TEXT_BOTOES
        #define TEXT_BOTOES
        #define TEXT_B1 "SALVAR E SAIR"
        #define TEXT_B2 "SAIR"
        #define TEXT_B3 "VOLTAR"
    #endif

    Rectangle botao[] = {
        tela.width / 2 - MeasureText(TEXT_B1, 20) / 2,
        tela.height / 2 + 30,
        MeasureText(TEXT_B1, 20),
        20,
        tela.width / 2 - MeasureText(TEXT_B2, 20) / 2,
        tela.height / 2 + 50,
        MeasureText(TEXT_B2, 20),
        20,
        tela.width / 2 - MeasureText(TEXT_B3, 20) / 2,
        tela.height / 2 + 70,
        MeasureText(TEXT_B3, 20),
        20
    };

    int confirma = 0;
    int opcao = 1;
    while (!confirma)
    {
        BeginDrawing();
        ClearBackground(BLACK);
            DrawTexture(fundo, 0, 0, (Color){255, 255, 255, 100});

            DrawText("DESEJA SAIR?", tela.width / 2 - MeasureText("DESEJA SAIR?", 20) / 2, tela.height / 2, 20, RED);
            DrawText(TEXT_B1, tela.width / 2 - MeasureText(TEXT_B1, 20) / 2, tela.height / 2 + 30, 20, RED);
            DrawText(TEXT_B2, tela.width / 2 - MeasureText(TEXT_B2, 20) / 2, tela.height / 2 + 50, 20, RED);
            DrawText(TEXT_B3, tela.width / 2 - MeasureText(TEXT_B3, 20) / 2, tela.height / 2 + 70, 20, RED);
            DrawText(">                        <", tela.width / 2 - MeasureText(">                        <", 20) / 2, tela.height / 2 +30 +20*(opcao -1), 20, RED);
        EndDrawing();

        if (IsKeyPressed(KEY_UP) && opcao >= 2) opcao--;
        if (IsKeyPressed(KEY_DOWN) && opcao <= 2) opcao++;
        if (IsKeyPressed(KEY_ENTER)) confirma = 1;

        if (CheckCollisionPointRec(GetMousePosition(), botao[0])) opcao = 1;
        if (CheckCollisionPointRec(GetMousePosition(), botao[1])) opcao = 2;
        if (CheckCollisionPointRec(GetMousePosition(), botao[2])) opcao = 3;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) confirma = 1;

        if (confirma && opcao == 1) return 2;
        if (confirma && opcao == 2) return 1;
        if (confirma && opcao == 3) return 0;
    }
}

void telaOpcao(int *opcao)
{

    Texture2D fundo = LoadTextureFromImage(GetScreenData());

    Rectangle botao[2] = {
        tela.width / 2 - MeasureText("Ponto Inicial do Jogo", 20) / 2,
        tela.height / 2 + 30,
        MeasureText("Ponto Inicial do Jogo", 20),
        20,
        tela.width / 2 - MeasureText("Ponto Final do Jogo", 20) / 2,
        tela.height / 2 + 50,
        MeasureText("Ponto Final do Jogo", 20),
        20,
    };

    int confirma = 0;

    while (!confirma)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(fundo, 0, 0, (Color){255, 255, 255, 100});

        DrawText(
            "O QUE DESEJA FAZER NESTE PONTO?",
            tela.width / 2 - MeasureText("O QUE DESEJA FAZER NESTE PONTO?", 20) / 2,
            tela.height / 2,
            20,
            RED);
        DrawText(
            "Ponto Inicial do Jogo",
            tela.width / 2 - MeasureText("Ponto Inicial do Jogo", 20) / 2,
            tela.height / 2 + 30,
            20,
            (Color){200, 100, 100, 255});

        DrawText(
            "Ponto Final do Jogo",
            tela.width / 2 - MeasureText("Ponto Final do Jogo", 20) / 2,
            tela.height / 2 + 50,
            20,
            (Color){200, 100, 100, 255});

        DrawText(
            "->",
            tela.width / 2 - MeasureText("Ponto Inicial do Jogo", 20) / 2 - 80,
            *opcao == OPCAO_INICIO ? tela.height / 2 + 30 : tela.height / 2 + 50,
            25,
            (Color){200, 100, 100, 255});
        EndDrawing();

        if (CheckCollisionPointRec(GetMousePosition(), botao[0]))
            *opcao = OPCAO_INICIO;
        if (CheckCollisionPointRec(GetMousePosition(), botao[1]))
            *opcao = OPCAO_FIM;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            confirma = 1;

        if (IsKeyPressed(KEY_UP))
            *opcao = OPCAO_INICIO;
        if (IsKeyPressed(KEY_DOWN))
            *opcao = OPCAO_FIM;
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
            confirma = 1;
    }
}