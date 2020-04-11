#include "screens.h"

void telaOpcoes(int *tipo, Mapa *fase)
{
    int confirma = 0;
    int opcao = 0;
    Texture2D fundo = LoadTextureFromImage(GetScreenData());

    Rectangle botao[] = {
        tela.width / 2 - MeasureText("PAREDE", 20) / 2,
        tela.height / 2 + 1*ESPACAMENTO_P2,
        MeasureText("PAREDE", 20),
        20,
        tela.width / 2 - MeasureText("PISO", 20) / 2,
        tela.height / 2 + 2*ESPACAMENTO_P2,
        MeasureText("PISO", 20),
        20,
        tela.width / 2 - MeasureText("INIMIGO", 20) / 2,
        tela.height / 2 + 3*ESPACAMENTO_P2,
        MeasureText("INIMIGO", 20),
        20,
        tela.width / 2 - MeasureText("VIDA", 20) / 2,
        tela.height / 2 + 4*ESPACAMENTO_P2,
        MeasureText("VIDA", 20),
        20,
        tela.width / 2 - MeasureText("FLECHA", 20) / 2,
        tela.height / 2 + 5*ESPACAMENTO_P2,
        MeasureText("FLECHA", 20),
        20,
        tela.width / 2 - MeasureText("PORTAL", 20) / 2,
        tela.height / 2 + 6*ESPACAMENTO_P2,
        MeasureText("PORTAL", 20),
        20
    };

    

    while (!confirma && IsKeyUp(KEY_ESCAPE))
    {
        CheckFileOnScreen(fase);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(fundo, 0,0, (Color){255,255,255,100});
            DrawText("____OBJETOS____", tela.width / 2 - MeasureText("____OBJETOS____", 30) / 2, tela.height / 2.8, 30, GREEN);
            DrawText("PAREDE",  botao[0].x, botao[0].y, 20, opcao == 0 ? GREEN: DARKGREEN);
            DrawText("PISO",    botao[1].x, botao[1].y, 20, opcao == 1 ? GREEN: DARKGREEN);
            DrawText("INIMIGO", botao[2].x, botao[2].y, 20, opcao == 2 ? GREEN: DARKGREEN);
            DrawText("VIDA",    botao[3].x, botao[3].y, 20, opcao == 3 ? GREEN: DARKGREEN);
            DrawText("FLECHA",  botao[4].x, botao[4].y, 20, opcao == 4 ? GREEN: DARKGREEN);
            DrawText("PORTAL",  botao[5].x, botao[5].y, 20, opcao == 5 ? GREEN: DARKGREEN);
            DrawRectangleLines(tela.width / 2 -100, tela.height/2 +25 +opcao*ESPACAMENTO_P2, 200, 30, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_UP)) {
            if(opcao > 0)
                opcao--;
            else
                opcao = sizeof(botao)/sizeof(Rectangle) -1;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            if(opcao < sizeof(botao)/sizeof(Rectangle) -1)
                opcao++;
            else
                opcao = 0;
        }
        if (IsKeyPressed(KEY_ENTER)) confirma = 1;
        if (IsKeyPressed(KEY_ESCAPE)) break;

        for( int i = 0; i < sizeof(botao)/sizeof(Rectangle); i++){
            if (CheckCollisionPointRec(GetMousePosition(), botao[i])) opcao = i;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            confirma = 1;
            for( int i = 0; i < sizeof(botao)/sizeof(Rectangle); i++){
                if (CheckCollisionPointRec(GetMousePosition(), botao[i])){
                    opcao = i;
                    break;
                }
                else opcao = -1;
            }
        }

        if(confirma){
            switch(opcao){
                case PAREDE:  *tipo = PAREDE; break;
                case PISO:    *tipo = PISO; break;
                case INIMIGO: *tipo = INIMIGO; break;
                case VIDA:    *tipo = VIDA; break;
                case FLECHA:  *tipo = FLECHA; break;
                case PORTAL:  *tipo = PORTAL; break;
            }
        }
    }
}

int telaSair(Mapa fase)
{
    Texture2D fundo = LoadTextureFromImage(GetScreenData());
    
    const char *text_B1 = "SALVAR MAPA";
    const char *text_B2 = "EXPORTAR CÓDIGO";
    const char *text_B3 = "SAIR";
    const char *text_B4 = "VOLTAR";
    const int DIST_BOTOES = 30; //distancia entre cada botão
    

    Rectangle botao[] = {
        tela.width / 2 - MeasureText(text_B1, 20) / 2,
        tela.height / 2 + DIST_BOTOES,
        MeasureText(text_B1, 20),
        20,
        tela.width / 2 - MeasureText(text_B2, 20) / 2,
        tela.height / 2 + 2*DIST_BOTOES,
        MeasureText(text_B2, 20),
        20,
        tela.width / 2 - MeasureText(text_B3, 20) / 2,
        tela.height / 2 + 3*DIST_BOTOES,
        MeasureText(text_B3, 20),
        20,
        tela.width / 2 - MeasureText(text_B4, 20) / 2,
        tela.height / 2 + 4*DIST_BOTOES,
        MeasureText(text_B4, 20),
        20
    };

    bool confirma = 0;
    int opcao = 0;
    while (!confirma)
    {
        BeginDrawing();
        ClearBackground(BLACK);
            DrawTexture(fundo, 0, 0, (Color){255, 255, 255, 100});

            DrawText("DESEJA SAIR?", tela.width / 2 - MeasureText("DESEJA SAIR?", 30) / 2, tela.height / 2.8, 30, RED);
            DrawText(text_B1, tela.width / 2 - MeasureText(text_B1, 20) / 2, tela.height / 2 + 1*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawText(text_B2, tela.width / 2 - MeasureText(text_B2, 20) / 2, tela.height / 2 + 2*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawText(text_B3, tela.width / 2 - MeasureText(text_B3, 20) / 2, tela.height / 2 + 3*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawText(text_B4, tela.width / 2 - MeasureText(text_B4, 20) / 2, tela.height / 2 + 4*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawRectangleLines(tela.width / 2 -120, tela.height/2 +(opcao +1)*DIST_BOTOES -5, 240, 30, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_UP)) {
            if(opcao > 0)
                opcao--;
            else
                opcao = sizeof(botao)/sizeof(Rectangle) -1;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            if(opcao < sizeof(botao)/sizeof(Rectangle) -1)
                opcao++;
            else
                opcao = 0;
        }
        if (IsKeyPressed(KEY_ENTER)) confirma = 1;

        for(int i = 0; i < 4; i++){
            if (CheckCollisionPointRec(GetMousePosition(), botao[i])) opcao = i;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            confirma = true;
        }
        else if(IsKeyPressed(KEY_ESCAPE)){
            confirma = true;
            opcao = -1;
        }
    }
    switch (opcao)
    {
        case 0: salvar(fase); break;
        case 1: exportar(fase); break;
        case 2: return 1; //Unico caminho para fechar o programa
    }
    return 0;
}

void telaBotaoDireito(int *opcao)
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