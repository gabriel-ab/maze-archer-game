#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/projetil.h"
    #include "../../lib/som.h"
#endif

#define TAM_MAPA_2 31 
#define TAM_PISO_2 13

void fase_2();

void fase_2()
{
    
    Rectangle PAREDE[] = {
        -256, -256, 32, 512,
        -256, -288, 512, 32,
        -256, 256, 512, 32,
        224, 64, 32, 192,
        224, -256, 32, 192,
        256, -96, 768, 32,
        256, 64, 320, 32,
        576, 64, 32, 288,
        288, 320, 288, 32,
        256, 320, 32, 320,
        288, 608, 608, 32,
        864, 352, 32, 256,
        736, 320, 160, 32,
        704, 64, 32, 288,
        736, 64, 288, 32,
        1024, 64, 32, 544,
        1056, 576, 448, 32,
        1472, 96, 32, 480,
        1472, -640, 32, 576,
        1024, -640, 32, 576,
        1024, -672, 480, 32,
        1056, -448, 320, 32,
        1504, -96, 992, 32,
        1504, 96, 800, 32,
        2176, -320, 32, 224,
        2592, -320, 32, 896,
        2016, 128, 32, 640,
        2048, 736, 1088, 32,
        2624, 544, 512, 32,
        2176, -352, 448, 32,
        2432, 96, 160, 32,
    };
    
    Rectangle PISO[] = {
        -224, -256, 448, 512,
        224, -64, 832, 128,
        608, 64, 96, 288,
        288, 352, 576, 256,
        1056, -416, 416, 992,
        1056, -640, 416, 192,
        1376, -448, 96, 32,
        1472, -64, 1120, 160,
        2208, -320, 384, 224,
        2496, -96, 96, 32,
        2304, 96, 128, 32,
        2048, 128, 544, 608,
        2592, 576, 544, 160,  
    };
    
    // ------------------- TEXTURA DO CENARIO ------------------- //
    setTextureCropped(&pisoTexture, "resources/images/full.png", (Rectangle){32*17,32*4,32,32 });
    setTextureCropped(&paredeTexture, "resources/images/full.png", (Rectangle){32*23,32*14,32,32 });
    setTexture(&portalTexture, "resources/images/portal.png",260, 160);
    setTextureCropped(&flechasTexture, "resources/images/Flechas.png", (Rectangle){0,0,64,64});
    //----------------------------------------------------------//
    

    // ------------ XALA ------------ //
    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){0, 0};
    xala.altura = 20;
    xala.largura = 20;
    // ----------------------------- //


    // ------------ FLECHA ------------ //
    Projetil flechas[quantidade_maxima_flechas];

    // indice da flecha
    int projetil_atual = xala.quantidadeFlechas -1;

    // Inicializando as flechas
    for(int i = 0; i < quantidade_maxima_flechas; i++){
        flechas[i].ativa = false;
        flechas[i].textura = flechasTexture;
    }
    // -------------------------------- //

    setTargetCamera(&xala);

    // ------------ PORTAL ------------- //
    ///Retangulo responsável por representar a parte
    ///que o personagem colide para passar de fase
    int currentFrame = 0;
    int frameCount = 0;
    Rectangle portalCollision = (Rectangle) {0, 50, 30, 60 };
    Rectangle frameRecPortal = (Rectangle) {0 ,0 , portalTexture.width/4, 160};
    // -------------------------------- //


    
    while(telaAtual == TELA_FASE_2){ 

        if(isPaused) {
            telaPausa();
        } else {

            HideCursor();

            if(IsKeyPressed(KEY_ESCAPE)) {
                isPaused = true;
            }

            if(xala.vida < 1) {
                telaAnterior = telaAtual;
                telaAtual = TELA_FRACASSO;
            }

            if(CheckCollisionPointRec(xala.posicao, portalCollision)) {
                telaAtual = TELA_FASE_3;
                save();
            }

            // -------- Logica do ANIMAÇÃO SPRITE PORTAL ---------- //
            frameCount++;
            if (frameCount >= (20))
            {
                frameCount = 0;
                currentFrame++;

                if (currentFrame > 4) currentFrame = 0;
                
                frameRecPortal.x = (float)currentFrame * (float)portalTexture.width/4;
            }
            // -----------------------------------------------------//

            // ----------------------- LÓGICA DO PROJÉTIL ------------------------ //
    
            checkClickBow(projetil_atual);

            if(projetil_atual > -1)
            {
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    mira(xala, &flechas[projetil_atual], cam);
                }

                if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    flechas[projetil_atual].ativa = true;

                    atira(xala, &flechas[projetil_atual]);

                    projetil_atual--;
                }
            }
            
            for(int i = 0; i < xala.quantidadeFlechas; i++)
            {   
                if(flechas[i].ativa)
                {
                    aplicarInerciaV(&flechas[i].posicao, flechas[i].velocidade);
                    aplicarAtritoProjetil(&flechas[i],0.5);
                    colisaoProjetil_mapa(&flechas[i], PAREDE, TAM_MAPA_2);
                    // colisaoProjetil_inimigo(&flechas[i], inimigo, QTD_INIMIGO_3);
                }
            }
            
            if(flechas[projetil_atual].velocidade.x == 0 && flechas[projetil_atual].velocidade.y == 0 && flechas[projetil_atual].ativa)
            {
                flechas[projetil_atual].ativa = false;
            }
            
            // RAFAEL PARTE DE PEGAR OBJETO (flechas)
            if(projetil_atual +1 < xala.quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario

            // -------------------------------------------------------- //


            movimentar(&xala);
            colisaoPersonagem(&xala, PAREDE, TAM_MAPA_2);
            atualizarCamera(&cam, xala.posicao);
        

            BeginDrawing();
                ClearBackground(GRAY);

                BeginMode2D(cam);
                    
                    drawParedes(PAREDE, TAM_MAPA_2);
                    drawPiso(PISO, TAM_PISO_2);
                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){0, 0}, GREEN);
                    drawXala(&xala, 0);
                    drawFlecha(flechas, xala.quantidadeFlechas);

                EndMode2D();

                // "Mira" do mouse
                DrawCircleV(GetMousePosition(), 5, PURPLE);

                drawHUD(xala.vida, projetil_atual+1);

            EndDrawing();
        }
        if(isRestarting) 
        {
            isRestarting = false;
            break;
        }
    }
}
