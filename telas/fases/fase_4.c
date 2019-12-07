#include <raylib.h>

#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"

#define TAM_MAPA_4 4
#define TAM_PISO_4 1
#define TAM_ARMADILHAS_4 0

void fase_4();
void draw_fase_4(Personagem* xala,Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]);
void logica_fase_4(Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]);

//----- TEMPORÁRIO ----//
Rectangle frameRec;
Rectangle frameRecPortal;
Rectangle portalCollision;
// ------------------ //

//Função responsável por representar a Fase 3
void fase_4() {

    Rectangle PAREDES[] = {
        -128, -160, 256, 32,
        -128, 128, 256, 32,
        -160, -160, 32, 320,
        128, -160, 32, 320,
    };

    Rectangle PISO[] = {
       -128, -128, 256, 256,
    };

    Rectangle ARMADILHAS[] = {
    };

    // ----------------- TEXTURE CENÁRIO --------------- //
    setTextureCropped(&piso, "resources/images/full.png", (Rectangle){960,64,32,32 });
    setTextureCropped(&parede, "resources/images/floortileset.png", (Rectangle){32,128,32,32 });
    setTextureCropped(&armadilha, "resources/images/full.png", (Rectangle){1920,160,128,32 });
    setTexture(&portal, "resources/images/portal.png",260, 160);
    //--------------------------------------------------//


    frameRec = (Rectangle) {0 ,0 ,30, 30};
    frameRecPortal = (Rectangle) {0 ,0 , portal.width/4, 160};

    portalCollision = (Rectangle) {2740, -1145, 30, 60 };

    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){0, 0};
    xala.altura = 20;
    xala.largura = 20;

    setTargetCamera(&xala);

    isPaused = false;
    isRestarting = false;

    while(telaAtual == TELA_FASE_4) {
        
        if(isPaused) {
            telaPausa(&isPaused, &isRestarting);
        } else {
            draw_fase_4(&xala, PAREDES, PISO, ARMADILHAS);
            logica_fase_4(&xala, PAREDES, ARMADILHAS); 
        }

        if(isRestarting) {
            break;
        }
    }

}

//Função responsável por exibir a Fase 3
void draw_fase_4(Personagem* xala, Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]) {
    
    BeginDrawing();
        BeginMode2D(cam);

            ClearBackground(BLACK);

            drawPiso(PISO, TAM_PISO_4, frameRec);
            drawArmadilhas(ARMADILHAS, TAM_ARMADILHAS_4, frameRec);
            drawParedes(PAREDES, TAM_MAPA_4);
            DrawTextureRec(portal, frameRecPortal, (Vector2){2720, -1184}, RED);
            drawXala(xala, count);

        EndMode2D();

        drawHUD(xala->vida, 0);

    EndDrawing();
}

//Função responsável pela lógica da Fase 3
void logica_fase_4(Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]) {
    
    // ----------- TEMPORARIO -------------- //
    if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;    
    if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;
    if(IsKeyDown(KEY_Z)) {
        telaAtual = 100;
        jogo_rodando = false;
    } 
    // ------------------------------------ //

    if(IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
    }

    if(xala->vida < 1) {
        telaAnterior = telaAtual;
        telaAtual = TELA_FRACASSO;
    }

    if(CheckCollisionPointRec(xala->posicao, portalCollision)) {
        isRestarting = true;
    }
    
    movimentar(xala);
    colisaoPersonagem(xala, PAREDES, TAM_MAPA_4);
    cam.target = xala->posicao;

    //------------Logica do INVULNERABILIDADE--------------
    for (int i = 0; i < TAM_ARMADILHAS_4; i++)
    {
        if(CheckCollisionPointRec(xala->posicao, ARMADILHA[i]) && !(xala->invulneravel)) {
            xala->vida--;
            xala->invulneravel = !(xala->invulneravel);
        }
    }

    if(xala->invulneravel){
        count++;
        if(count > 60) {
            tempo_invunerabilidade--;
            count = 0;
        }
    }

    if(tempo_invunerabilidade < 1) {
        xala->invulneravel = !(xala->invulneravel);
        tempo_invunerabilidade = TEMPO_MAX_INVULNERAVEL;
    }
    //---------------------------------------------------


    //--------Logica do ANIMAÇÃO SPRITE LAVA----------
    frameCount++;
    if (frameCount >= (20))
    {
        frameCount = 0;
        currentFrame++;

        if (currentFrame > 4) currentFrame = 0;
        
        frameRec.x = (float)currentFrame * (float)armadilha.width/4;
        frameRecPortal.x = (float)currentFrame * (float)portal.width/4;
    }
    //-------------------------------------------

}