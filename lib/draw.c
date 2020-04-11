#include "draw.h"

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

void desenhaTelaAjuda(void)
{
    #ifndef TEXTO_AJUDA
        #define TEXTO_AJUDA
        #define AJUDA_0 "TAB = Menu de Opções"
        #define AJUDA_1 "Ctrl + Clique Esquerdo = Seleciona Objeto"
        #define AJUDA_2 "1,2,3,4,5,6 = Retangulos Predefinidos de Paredes e Pisos"
        #define AJUDA_3 "Setas = Movimenta paredes e pisos"
        #define AJUDA_4 "Shift + Setas = Edição de tamanho do Objeto"
        #define AJUDA_5 "Clique Esquerdo = Insere Vida, flecha ou inimigo"
        #define AJUDA_6 "Clique Direito = Posições especiais"
        #define AJUDA_7 "Del = Apaga o Ultimo objeto ativo"
        #define AJUDA_8 "Page Up/Down = Zoom"
        #define AJUDA_9 "Enter = Fixa Objeto"
        #define AJUDA_10 "Carregar Mapa: arrastar para janela do programa"
        #define AJUDA_11 "(O mapa atual será apagado)"
    #endif
    DrawRectangle(0, 0, tela.width, tela.height, (Color){30, 30, 30, 200});

    DrawText(AJUDA_0, tela.width / 2 - MeasureText(AJUDA_0, 20) / 2, tela.height / 5 - 3 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_1, tela.width / 2 - MeasureText(AJUDA_1, 20) / 2, tela.height / 5 - 1 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_2, tela.width / 2 - MeasureText(AJUDA_2, 20) / 2, tela.height / 5 + 0 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_3, tela.width / 2 - MeasureText(AJUDA_3, 20) / 2, tela.height / 5 + 1 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_4, tela.width / 2 - MeasureText(AJUDA_4, 20) / 2, tela.height / 5 + 2 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_5, tela.width / 2 - MeasureText(AJUDA_5, 20) / 2, tela.height / 5 + 3 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_6, tela.width / 2 - MeasureText(AJUDA_6, 20) / 2, tela.height / 5 + 4 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_7, tela.width / 2 - MeasureText(AJUDA_7, 20) / 2, tela.height / 5 + 6 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_8, tela.width / 2 - MeasureText(AJUDA_8, 20) / 2, tela.height / 5 + 7 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_9, tela.width / 2 - MeasureText(AJUDA_9, 20) / 2, tela.height / 5 + 8 * ESPACAMENTO_P2, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_10, tela.width / 2 - MeasureText(AJUDA_10, 20) / 2, tela.height -40, 20, (Color){200, 200, 200, 255});
    DrawText(AJUDA_11, tela.width / 2 - MeasureText(AJUDA_11, 20) / 2, tela.height -20, 20, (Color){200, 200, 200, 255});
}

void drawFloor(Rectangle floor){
    DrawRectangleRec(floor, (Color){0,30,0,255});
    DrawRectangleLinesEx(floor, 2, (Color){80, 200, 80, 255});
}
void drawWall(Rectangle wall){
    DrawRectangleRec(wall, (Color){0,0,30,255});
    DrawRectangleLinesEx(wall, 2, (Color){80, 80, 200, 255});
}
void drawEnemie(Vector2 enemie){
    DrawCircleV(enemie, 8, PURPLE);
    DrawCircleV(enemie, 4, BLACK);
}
void drawArrow(Vector2 arrow){
    DrawCircleSector((Vector2){arrow.x,arrow.y -24}, 8, 120, 240,3,GREEN);
    DrawRectangle(arrow.x -2, arrow.y -32,4,32,BROWN);
    DrawCircleV(arrow, 8, DARKGREEN);
    DrawCircleV(arrow, 4, GREEN);
}
void drawLife(Vector2 life){
    DrawLineEx((Vector2){life.x, life.y -16}, (Vector2){life.x, life.y +16}, 8, RED);
    DrawLineEx((Vector2){life.x -16, life.y}, (Vector2){life.x +16, life.y}, 8, RED);
}
void drawPortal(Vector2 portal){
    DrawRectangleRounded(
        (Rectangle){
            portal.x -16,
            portal.y -24,
            32,
            48
        },
        1.0,
        20,
        Fade(BLUE,0.5)
    );
    DrawCircleGradient(portal.x ,portal.y, 14, BLANK, LIGHTGRAY);
}

void drawInfoPoint(char *text, Vector2 pos){
    DrawRectangleRec((Rectangle){pos.x - 8, pos.y - 8, 16, 16}, DARKBLUE);
    DrawCircleV(pos, 5, BLUE);
    DrawText(text, pos.x - 16, pos.y + 10, 12, WHITE);
}