#include <raylib.h>
#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"

#include "../telaPausa.c"

#define TEMPO_INVULNERAVEL 2
int count = 0;
int tempoInvunerabilidade = TEMPO_INVULNERAVEL;

bool isPaused;
bool isRestarting;

void fase_3();
void draw_fase_3(Camera2D* cam, Personagem* xala,Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]);
void logica_fase_3(Camera2D* cam,Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]);
void drawParedes(Rectangle PAREDES[]);
void drawPiso(Rectangle PISO[]);
void drawArmadilhas(Rectangle ARMADILHAS[]);

Rectangle frameRec;
int currentFrame;
int frameCount;

Personagem inimigo;
Projetil flecha;


//Função responsável por representar a Fase 3
void fase_3() {

    Rectangle PAREDES[] = {
        -32, 0, 32, 256,
        256, 0, 32, 256,
        -32, -32, 320, 32,
        -32, 256, 320, 32,
    };

    Rectangle PISO[] = {
        0, 0, 256, 256,
    };

    Rectangle ARMADILHAS[] = {
        50, 100, 20, 20,
    };

    // ----------------- TEXTURE CENÁRIO --------------- //
    setTextureCropped(&piso, "resources/images/full.png", (Rectangle){960,64,32,32 });
    setTextureCropped(&parede, "resources/images/floortileset.png", (Rectangle){32,128,32,32 });
    setTextureCropped(&armadilha, "resources/images/full.png", (Rectangle){1920,160,128,32 });


    // ----------------- TEXTURE FLECHA ---------------- //
    Image temp = LoadImage("resources/images/Flechas.png");
    ImageCrop(&temp,(Rectangle){0,0,64,64});
    flecha.textura = LoadTextureFromImage(temp);
    UnloadImage(temp);
    // ------------------------------------------------- //
  
    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){10,10};
    xala.altura = 20;
    xala.largura = 20;

    Camera2D cam;
    cam.zoom = 1;
    cam.rotation = 0;
    cam.target = xala.posicao;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};
    int largura = 32, altura = 32;

    isPaused = false;
    isRestarting = false;

    while(telaAtual == TELA_FASE_3) {
        
        if(isPaused) {
            telaPausa(&isPaused, &isRestarting);
        } else {
            draw_fase_3(&cam, &xala, PAREDES, PISO, ARMADILHAS);
            logica_fase_3(&cam, &xala, PAREDES, ARMADILHAS); 
        }

        if(isRestarting) {
            break;
        }
    }

}

//Função responsável por exibir a Fase 3
void draw_fase_3(Camera2D* cam, Personagem* xala, Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]) {
    
    BeginDrawing();
        BeginMode2D(*cam);

            ClearBackground(BLACK);

            drawPiso(PISO);
            drawArmadilhas(ARMADILHAS);
            drawParedes(PAREDES);
            
            DrawCircleV(xala->posicao,10,BLUE);

            DrawTexturePro(flecha.textura,
                (Rectangle){0,28,64,8},
                (Rectangle){
                    flecha.posicao.x,
                    flecha.posicao.y,
                    64, 6},
                (Vector2){48,2},
                flecha.angulo,WHITE);

                DrawCircle(
                    (GetMouseX() -cam->offset.x),
                    (GetMouseY() -cam->offset.y),
                    5,PURPLE);

        EndMode2D();

        drawHUD(xala->vida, 4);
        DrawText(FormatText("VIDA INIMIGO: %i", inimigo.vida), 0, 100, 20, RED);

    EndDrawing();
}

//Função responsável pela lógica da Fase 3
void logica_fase_3(Camera2D* cam,Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]) {
    
    if(IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }

    if(xala->vida < 1) {
        telaAnterior = telaAtual;
        telaAtual = TELA_FRACASSO;
    }
    
    movimentar(xala);
    colisaoPersonagem(xala, PAREDES, 4);
    cam->target = xala->posicao;

    //------------Logica do INVULNERABILIDADE--------------
    if(CheckCollisionPointRec(xala->posicao, ARMADILHA[0]) && !(xala->invulneravel)) {
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
    //---------------------------------------------------


    //--------Logica do ANIMAÇÃO SPRITE LAVA----------
    frameCount++;
    if (frameCount >= (60))
    {
        frameCount = 0;
        currentFrame++;

        if (currentFrame > 4) currentFrame = 0;

        frameRec.x = (float)currentFrame*(float)armadilha.width/4;
    }
    //-------------------------------------------

}

//Função responsável por incluir as paredes da Fase 3
void drawParedes(Rectangle PAREDES[]) {
    for(int i = 0; i < TAM_MAPA1; i++){
                
        DrawRectangleRec(PAREDES[i],RED);
        
        DrawTexturePro(parede,
            (Rectangle){0,0,PAREDES[i].width,PAREDES[i].height},
            PAREDES[i],
            (Vector2){0,0},
            0,BROWN
        );
        
    }
}

//Função responsável por incluir os pisos da Fase 3
void drawPiso(Rectangle PISO[]) {     
    for(int posX = 0; posX < PISO[0].width; posX+=32) {
        for (int posY = 0; posY < PISO[0].height; posY+=32)
        {
            DrawTexture(piso,posX, posY,WHITE);
        }
        
    }
}

//Função responsável por incluir as armadilhas da Fase 3
void drawArmadilhas(Rectangle ARMADILHAS[]) {
    for(int i = 0; i < 1; i++){
        DrawTextureRec(armadilha, frameRec, (Vector2) {ARMADILHAS[i].x,ARMADILHAS[i].y}, WHITE);
    }
}
