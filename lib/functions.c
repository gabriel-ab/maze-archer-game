#include "functions.h"

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

void telaOpcoes(int *tipo, Mapa *fase)
{
    int confirma = 0;
    int opcao = 0;
    Texture2D fundo = LoadTextureFromImage(GetScreenData());

    Rectangle botao[3] = {
        tela.width / 2 - MeasureText("PAREDE", 20) / 2,
        tela.height / 2 + 30,
        MeasureText("PAREDE", 20),
        20,
        tela.width / 2 - MeasureText("PISO", 20) / 2,
        tela.height / 2 + 60,
        MeasureText("PISO", 20),
        20,
        tela.width / 2 - MeasureText("INIMIGO", 20) / 2,
        tela.height / 2 + 90,
        MeasureText("INIMIGO", 20),
        20
    };

    int count = 0;
    char **arquivosSoltos = {0};

    while (!confirma && IsKeyUp(KEY_ESCAPE))
    {
        if(IsFileDropped()){
            arquivosSoltos = GetDroppedFiles(&count);
            carregar(arquivosSoltos[count -1], fase);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(fundo, 0,0, (Color){255,255,255,100});
            DrawText("SELECIONE O TIPO DE RETANGULO:", tela.width / 2 - MeasureText("SELECIONE O TIPO DE RETANGULO:", 30) / 2, tela.height / 2.8, 30, GREEN);
            DrawText("PAREDE", botao[0].x, botao[0].y, 20, DARKGREEN);
            DrawText("PISO", botao[1].x, botao[1].y, 20, DARKGREEN);
            DrawText("INIMIGO", botao[2].x, botao[2].y, 20, DARKGREEN);
            DrawRectangleLines(tela.width / 2 -100, tela.height/2 +25 +opcao*30, 200, 30, WHITE);

            DrawText("Arraste arquivos aqui para carrega-los e sobrescrever o mapa atual (Salve antes)", tela.width/2 - MeasureText("Arraste arquivos aqui para carrega-los e sobrescrever o mapa atual (Salve antes)",20)/2, tela.height - 100,20, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_UP) && opcao > 0) opcao--;
        if (IsKeyPressed(KEY_DOWN) && opcao < 2) opcao++;
        if (IsKeyPressed(KEY_ENTER)) confirma = 1;
        if (IsKeyPressed(KEY_ESCAPE)) break;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            confirma = 1;
            for( int i = 0; i < 3; i++){
                if (CheckCollisionPointRec(GetMousePosition(), botao[i])) opcao = i + 1;
                else opcao = -1;
            }
        }

        if(confirma){
            switch(opcao){
                case 0: *tipo = PAREDE; break;
                case 1: *tipo = PISO; break;
                case 2: *tipo = INIMIGO; break;
            }
            GetKeyPressed();
        }
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

int telaSair(Mapa fase)
{
    Texture2D fundo = LoadTextureFromImage(GetScreenData());

    #ifndef TEXT_BOTOES
        #define TEXT_BOTOES
        #define TEXT_B1 "SALVAR MAPA"
        #define TEXT_B2 "EXPORTAR CÓDIGO"
        #define TEXT_B3 "SAIR"
        #define TEXT_B4 "VOLTAR"
        #define DIST_BOTOES 30 //distancia entre cada botão
    #endif

    Rectangle botao[] = {
        tela.width / 2 - MeasureText(TEXT_B1, 20) / 2,
        tela.height / 2 + DIST_BOTOES,
        MeasureText(TEXT_B1, 20),
        20,
        tela.width / 2 - MeasureText(TEXT_B2, 20) / 2,
        tela.height / 2 + 2*DIST_BOTOES,
        MeasureText(TEXT_B2, 20),
        20,
        tela.width / 2 - MeasureText(TEXT_B3, 20) / 2,
        tela.height / 2 + 3*DIST_BOTOES,
        MeasureText(TEXT_B3, 20),
        20,
        tela.width / 2 - MeasureText(TEXT_B4, 20) / 2,
        tela.height / 2 + 4*DIST_BOTOES,
        MeasureText(TEXT_B4, 20),
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
            DrawText(TEXT_B1, tela.width / 2 - MeasureText(TEXT_B1, 20) / 2, tela.height / 2 + 1*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawText(TEXT_B2, tela.width / 2 - MeasureText(TEXT_B2, 20) / 2, tela.height / 2 + 2*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawText(TEXT_B3, tela.width / 2 - MeasureText(TEXT_B3, 20) / 2, tela.height / 2 + 3*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawText(TEXT_B4, tela.width / 2 - MeasureText(TEXT_B4, 20) / 2, tela.height / 2 + 4*DIST_BOTOES, 20, (Color){255,80,80,255});
            DrawRectangleLines(tela.width / 2 -120, tela.height/2 +(opcao +1)*DIST_BOTOES -5, 240, 30, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_UP) && opcao > 0) opcao--;
        if (IsKeyPressed(KEY_DOWN) && opcao < 3) opcao++;
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

Objeto selecionarObjeto(Mapa fase, Camera2D camera){
    Vector2 mousePos = GetMousePosition();
    mousePos = (Vector2){(mousePos.x -camera.offset.x) / camera.zoom, (mousePos.y -camera.offset.y) / camera.zoom};

    for (int i = 0; i < fase.parede_atual; i++){
        if(CheckCollisionCircleRec(mousePos,5, fase.parede[i])){
            return (Objeto){PAREDE,i};
        }
    }
    for (int i = 0; i < fase.inimigo_atual; i++){
        if(CheckCollisionCircles(mousePos,5, fase.inimigo[i], 5)){
            return (Objeto){INIMIGO,i};
        }
    }
    for (int i = 0; i < fase.vida_atual; i++){
        if(CheckCollisionCircles(mousePos,5, fase.vida[i], 5)){
            return (Objeto){VIDA,i};
        }
    }
    for (int i = 0; i < fase.flecha_atual; i++){
        if(CheckCollisionCircles(mousePos,5, fase.flecha[i], 5)){
            return (Objeto){FLECHA,i};
        }
    }
    for (int i = 0; i < fase.piso_atual; i++){
        if(CheckCollisionCircleRec(mousePos,5, fase.piso[i])){
            return (Objeto){PISO,i};
        }
    }
    return (Objeto){NENHUM,NULL};
}