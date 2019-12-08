#include <raylib.h>

#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"

#define TAM_MAPA_4 4
#define TAM_PISO_4 1
#define TAM_ARMADILHAS_4 1

void fase_4();
void draw_fase_4(Personagem* xala,Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]);
void logica_fase_4(Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]);

Rectangle frameRecPortal;
Rectangle portalCollision;

Projetil dardo;

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
        -96, 128, 32, 32,
    };

    // ----------------- TEXTURE CENÁRIO --------------- //
    setTextureCropped(&piso, "resources/images/full.png", (Rectangle){32*17,32*4,32,32 });
    setTextureCropped(&parede, "resources/images/full.png", (Rectangle){32*23,32*14,32,32 });
    setTextureCropped(&armadilha, "resources/images/dardo_inativo.png", (Rectangle){0, 0, 32, 32});
    setTexture(&portal, "resources/images/portal.png",260, 160);
    //--------------------------------------------------//


    portalCollision = (Rectangle) {2740, -1145, 30, 60 };
    frameRecPortal = (Rectangle) {0 ,0 , portal.width/4, 160};
    
    dardo.ativa = false;
    dardo.posicao = (Vector2) {-96, 128, 32, 32,};
    setTextureCropped(&dardo.textura, "resources/images/full.png", (Rectangle) {32*7, 32*25, 32, 32});

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

            drawPiso(PISO, TAM_PISO_4);
            drawParedes(PAREDES, TAM_MAPA_4);
            drawArmadilhas(ARMADILHAS, TAM_ARMADILHAS_4);

            if(dardo.ativa) {
                DrawTextureEx(dardo.textura, dardo.posicao, 0, 1, WHITE);
            }
            DrawTextureRec(portal, frameRecPortal, (Vector2){32, -64}, GREEN);
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


    // -------- Logica do ANIMAÇÃO SPRITE DARDO E PORTAL ---------- //
    frameCount++;
    if(frameCount >=60*6) {
        frameCount = 0;
    }
    
    if (frameCount % 20 == 0)
    {
        currentFrame++;

        if (currentFrame > 4) 
        {
             currentFrame = 0;
        }

        frameRecPortal.x = (float)currentFrame * (float)portal.width/4;
    }

    if(frameCount == 0) {
        setTextureCropped(&armadilha, "resources/images/dardo_inativo.png", (Rectangle){0, 0, 32, 32});
    }

    if(frameCount == 180) {
        setTextureCropped(&armadilha, "resources/images/dardo_ativo.png", (Rectangle){0, 0, 32, 32});
    }
    

    if(frameCount == 240) {
        dardo.ativa = true;
    }


    if(dardo.ativa) {
        dardo.posicao.y -= 5;
    }

    for(int i = 0; i < TAM_MAPA_4; i++) {
        bool isColindindo = CheckCollisionPointRec(dardo.posicao, PAREDES[i]);
        bool isColindindoParedeAtual =  !CheckCollisionPointRec(dardo.posicao, (Rectangle){-96, 128, 32, 32});
        if(isColindindo && isColindindoParedeAtual) {
            dardo.ativa = false;
            dardo.posicao = (Vector2) {-96, 128};
        }
    }

    
    // ------------------------------------------------------------ //
}
