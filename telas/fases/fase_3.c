#include <raylib.h>
#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"


#include "../telaPausa.c"

#define TEMPO_INVULNERAVEL 2

bool isPaused = false;

int count = 0;
int tempoInvunerabilidade = TEMPO_INVULNERAVEL;

void fase_3();
void draw_fase_3(Camera2D* cam,Personagem* xala, Texture2D piso, Rectangle MAPA[], Rectangle ARMADILHAS[]);
void logica_fase_3(Camera2D* cam,Personagem* xala, Rectangle MAPA[], Rectangle ARMADILHA[]);

void drawMapa(Texture2D piso, Rectangle MAPA[]);
void drawArmadilhas(Rectangle ARMADILHAS[]);

void fase_3() {

    Rectangle MAPA[] = {
        -32, 0, 32, 448,
        -32, -32, 960, 32,
        -32, 448, 288, 32,
        256, 0, 32, 256,
        256, 352, 32, 704,
        -32, 1024, 288, 32,
        -32, 1056, 32, 736,
        -32, 1792, 288, 32,
        128, 1664, 288, 32,
        128, 1184, 32, 480,
        128, 1152, 352, 32,
        224, 1824, 32, 448,
        256, 2240, 800, 32,
        416, 1664, 640, 32,
        1056, 1856, 32, 416,
        544, 1824, 256, 256,
        480, 128, 32, 1056,
        800, 128, 32, 1056,
        512, 128, 288, 32,
        928, -32, 288, 32,
        1216, -32, 32, 320,
        992, 128, 32, 896,
        1024, 128, 32, 896,
        1248, 256, 416, 32,
        1664, -32, 32, 320,
        2208, -32, 32, 320,
        1664, -64, 576, 32,
        1056, 448, 576, 32,
        1632, 448, 32, 96,
        1632, 544, 32, 288,
        1056, 992, 192, 32,
        1248, 736, 32, 288,
        1248, 704, 352, 32,
        1568, 736, 32, 832,
        992, 1152, 64, 320,
        1056, 1152, 224, 32,
        1248, 1184, 32, 384,
        1280, 1536, 288, 32,
        800, 1184, 32, 480,
        992, 1472, 192, 32,
        1152, 1504, 32, 192,
        1184, 1664, 480, 32,
        1632, 832, 32, 832,
        1696, 256, 352, 32,
        2208, 288, 352, 32,
        2208, 800, 352, 32,
        2528, 320, 32, 480,
        2208, 512, 32, 288,
        2208, 832, 32, 448,
        2528, 832, 32, 736,
        2208, 1536, 320, 32,
        2208, 1440, 32, 96,
        2208, 1568, 32, 576,
        2528, 1568, 32, 864,
        2208, 2336, 32, 96,
        2240, 2400, 288, 32,
        1792, 576, 32, 960,
        2048, 576, 32, 960,
        1792, 544, 288, 32,
        1792, 1536, 288, 32,
        1088, 1856, 576, 32,
        1248, 1888, 32, 544,
        1280, 2400, 928, 32,
        1632, 2144, 32, 256,
        1632, 1888, 32, 96,
        1440, 1888, 32, 384,
        1792, 1856, 32, 416,
        2048, 1856, 32, 416,
        1792, 1824, 288, 32,
        1792, 2272, 288, 32,
    };

    Rectangle ARMADILHAS[] = {
        50, 100, 20, 20,
    };

    setVidaSprite("resources/images/heart pixel art 254x254.png");
    Texture2D piso = LoadTexture("resources/images/ciano.png");

    Personagem xala;
    xala = personagemConstructor();
    xala.position = (Vector2){10,10};
    xala.altura = 20;
    xala.largura = 20;

    Camera2D cam;
    cam.zoom = 1;
    cam.rotation = 0;
    cam.target = xala.position;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};
    int largura = 32, altura = 32;

    while(telaAtual == TELA_FASE_3) {
        draw_fase_3(&cam, &xala, piso, MAPA, ARMADILHAS);
        logica_fase_3(&cam, &xala, MAPA, ARMADILHAS);
    }

}

void draw_fase_3(Camera2D* cam, Personagem* xala, Texture2D piso, Rectangle MAPA[], Rectangle ARMADILHAS[]) {
    
    BeginDrawing();
        BeginMode2D(*cam);

            ClearBackground(GRAY);

            drawArmadilhas(ARMADILHAS);
            drawMapa(piso, MAPA);
            DrawRectangle(xala->position.x, xala->position.y, xala->largura, xala->altura, RED);
            DrawRectangleRec(xala->linhaColisaoCima,colideCima);
            DrawRectangleRec(xala->linhaColisaoBaixo,colideBaixo);
            DrawRectangleRec(xala->linhaColisaoEsquerda,colideEsq);
            DrawRectangleRec(xala->linhaColisaoDireita,colideDir);

            

        EndMode2D();

        DrawText(FormatText("Vida: %i", xala->vida), 10,40,20, YELLOW);
        DrawText(FormatText("Contador: %i", count), 10,60,20, YELLOW);
        DrawText(FormatText("Tempo Invulnerável: %i", tempoInvunerabilidade), 10,80,20, YELLOW);

        drawHUD(xala->vida);

        if(isPaused) telaPausa(&isPaused);

    EndDrawing();
}

void logica_fase_3(Camera2D* cam,Personagem* xala, Rectangle MAPA[], Rectangle ARMADILHA[]) {
    if(xala->vida < 1) {
        telaAtual = TELA_FRACASSO;
    }
    
    if(IsKeyDown(KEY_ESCAPE)) isPaused = true;
    movimentar(xala, MAPA);
    cam->target = xala->position;

    if(CheckCollisionPointRec(xala->position, ARMADILHA[0]) && !(xala->invulneravel)) {
         xala->vida--;
         xala->invulneravel = !(xala->invulneravel);
    }

    if(xala->invulneravel){
        count++;
        if(count > 60) {
            tempoInvunerabilidade--;
            count = 0;
        }
    }

    if(tempoInvunerabilidade < 1) {
        xala->invulneravel = !(xala->invulneravel);
        tempoInvunerabilidade = TEMPO_INVULNERAVEL;
    }

    if(IsKeyDown(KEY_PAGE_UP)) cam->zoom += 0.01;    // Temporario
    if(IsKeyDown(KEY_PAGE_DOWN)) cam->zoom -= 0.01;

}

void drawMapa(Texture2D piso, Rectangle MAPA[]) {
    for(int i = 0; i < TAM_MAPA1; i++){
                
        DrawRectangleRec(MAPA[i],BLACK);
        
        DrawTexturePro(piso,
            (Rectangle){0,0,MAPA[i].width,MAPA[i].height},
            MAPA[i],
            (Vector2){0,0},
            0,WHITE
        );
        
    }
}

void drawArmadilhas(Rectangle ARMADILHAS[]) {
    for(int i = 0; i < 4; i++){
                
        DrawRectangleRec(ARMADILHAS[i],BLACK);
        
    }
}