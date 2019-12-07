#include <raylib.h>

#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/draw.h"
#include "../../lib/data.h"

#define TAM_MAPA_3 76
#define TAM_PISO_3 19
#define TAM_ARMADILHAS_3 15

void fase_3();
void draw_fase_3(Personagem* xala,Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]);
void logica_fase_3(Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]);


//----- TEMPORÁRIO ----//
Rectangle frameRec;
Rectangle frameRecPortal;
Rectangle portalCollision;
// ------------------ //
bool isUpgradeNotGetted;
Rectangle vidaUpgrade = (Rectangle) {20, 20, 16, 16};
//Rectangle vidaUpgrade = (Rectangle) {950, 990, 16, 16};

//Função responsável por representar a Fase 3
void fase_3()
{

    Rectangle PAREDES[] = {
        -128, -160, 256, 32,
        -128, 128, 256, 32,
        -160, -160, 32, 320,
        128, -160, 32, 128,
        128, 32, 32, 128,
        160, 32, 416, 32,
        160, -64, 416, 32,
        1120, -64, 416, 32,
        1120, 32, 416, 32,
        2080, 32, 416, 32,
        2080, -64, 416, 32,
        3040, -64, 416, 32,
        3040, 32, 416, 32,
        1120, 928, 416, 32,
        1120, 1024, 416, 32,
        576, 32, 32, 224,
        1088, 32, 32, 224,
        1536, 32, 32, 224,
        2048, 32, 32, 224,
        1536, 736, 32, 224,
        1536, 1024, 32, 192,
        1536, -192, 32, 160,
        2048, -192, 32, 160,
        1088, -192, 32, 160,
        576, -192, 32, 160,
        576, 256, 544, 32,
        608, -1184, 480, 32,
        1568, -1184, 480, 32,
        576, -1184, 32, 512,
        1088, -1184, 32, 512,
        1536, -1184, 32, 512,
        2048, -1184, 32, 512,
        576, -672, 224, 32,
        576, -224, 224, 32,
        864, -224, 256, 32,
        864, -672, 256, 32,
        1536, -672, 256, 32,
        1536, -224, 256, 32,
        1856, -224, 224, 32,
        1856, -672, 224, 32,
        1856, 256, 224, 32,
        1536, 256, 256, 32,
        864, -640, 32, 416,
        768, -640, 32, 416,
        1760, -640, 32, 416,
        1856, -640, 32, 416,
        1856, 288, 32, 416,
        1760, 288, 32, 416,
        1536, 704, 256, 32,
        1856, 704, 192, 32,
        2048, 704, 32, 512,
        1536, 1216, 544, 32,
        1088, 1024, 32, 96,
        1088, 864, 32, 96,
        832, 832, 288, 32,
        832, 1120, 288, 32,
        800, 832, 32, 320,
        2528, 448, 480, 32,
        2496, 32, 32, 448,
        3008, 32, 32, 448,
        3456, 32, 32, 96,
        3456, -128, 32, 96,
        3456, -160, 288, 32,
        3456, 128, 288, 32,
        3744, -160, 32, 320,
        3008, -384, 32, 352,
        2496, -384, 32, 352,
        2496, -416, 224, 32,
        2784, -416, 256, 32,
        2784, -992, 32, 576,
        2688, -992, 32, 576,
        2624, -992, 64, 32,
        2816, -992, 64, 32,
        2880, -1248, 32, 288,
        2592, -1248, 32, 288,
        2592, -1280, 320, 32,
    };

    Rectangle PISO[] = {
       -128, -128, 256, 256,
        128, -32, 480, 64,
        608, -192, 480, 448,
        1088, -32, 480, 64,
        1568, -192, 480, 448,
        800, -672, 64, 480,
        1792, -672, 64, 480,
        1792, 256, 64, 480,
        1568, 736, 480, 480,
        1568, -1152, 480, 480,
        608, -1152, 480, 480,
        2048, -32, 480, 64,
        1088, 960, 480, 64,
        832, 864, 256, 256,
        2528, -384, 480, 832,
        2720, -992, 64, 608,
        3008, -32, 480, 64,
        3488, -128, 256, 256,
        2624, -1248, 256, 256,
    };

    Rectangle ARMADILHAS[] = {
        2720, -96, 64, 288,//
        2624, 64, 256, 64,//
        704, -128, 32, 288,
        928, -128, 32, 288,
        800, -64, 64, 160,
        768, -992, 160, 160,
        1664, -832, 64, 32,
        1696, -864, 64, 32,
        1728, -896, 64, 32,
        1760, -928, 64, 32,
        1792, -960, 64, 32,
        1824, -928, 64, 32,
        1856, -896, 64, 32,
        1888, -864, 64, 32,
        1920, -832, 64, 32,
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
    xala.posicao = (Vector2){0, 0 /*2700, -1184*/};
    xala.altura = 20;
    xala.largura = 20;

    setTargetCamera(&xala);

    isUpgradeNotGetted = true;
    isPaused = false;
    isRestarting = false;

    while(telaAtual == TELA_FASE_3) {
        
        if(isPaused) 
        {
            telaPausa(&isPaused, &isRestarting);

        } else 
        {
            draw_fase_3(&xala, PAREDES, PISO, ARMADILHAS);
            logica_fase_3(&xala, PAREDES, ARMADILHAS); 
        }

        if(isRestarting) 
        {
            break;
        }
    }

}

//Função responsável por exibir a Fase 3
void draw_fase_3(Personagem* xala, Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]) {
    
    BeginDrawing();
        BeginMode2D(cam);

            ClearBackground(BLACK);

            drawPiso(PISO, TAM_PISO_3, frameRec);
            drawArmadilhas(ARMADILHAS, TAM_ARMADILHAS_3, frameRec);
            drawParedes(PAREDES, TAM_MAPA_3);
            DrawTextureRec(portal, frameRecPortal, (Vector2){2720, -1184}, RED);
            
            if(isUpgradeNotGetted) {
                DrawTexture(vida, vidaUpgrade.x, vidaUpgrade.y,  WHITE);
            }
            

            drawXala(xala, count);

        EndMode2D();

        drawHUD(xala->vida, 0);

    EndDrawing();
}

//Função responsável pela lógica da Fase 3
void logica_fase_3(Personagem* xala, Rectangle PAREDES[], Rectangle ARMADILHA[]) {
    
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

    if(CheckCollisionPointRec(xala->posicao, vidaUpgrade) && isUpgradeNotGetted) {
        vida_maxima++;
        xala->vida = vida_maxima;
        isUpgradeNotGetted = false;
    }

    if(CheckCollisionPointRec(xala->posicao, portalCollision)) {
        save(TELA_FASE_4);
        telaAtual = TELA_FASE_4;
    }
    
    movimentar(xala);
    colisaoPersonagem(xala, PAREDES, TAM_MAPA_3);
    cam.target = xala->posicao;

    //------------Logica do INVULNERABILIDADE--------------
    for (int i = 0; i < TAM_ARMADILHAS_3; i++)
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
