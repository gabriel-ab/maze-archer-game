#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/projetil.h"
    #include "../../lib/som.h"
#endif
void posicionaInimigos(Personagem *inimigo);
void fase_1();

void fase_1()
{
    Rectangle PAREDES[] = {
        -1504, -1728, 32, 192,
        -1504, -1408, 32, 192,
        -1504, -1088, 32, 192,
        -1504, -768, 32, 192,
        -1504, -1920, 32, 64,
        -1504, -448, 32, 64,
        -1696, -416, 192, 32,
        -1696, -704, 192, 32,
        -1696, -1024, 192, 32,
        -1696, -1344, 192, 32,
        -1696, -1664, 192, 32,
        -1696, -1920, 192, 32,
        -1728, -1920, 32, 1536,
        -1472, -1920, 640, 32,
        -1312, -1760, 480, 32,
        -1312, -1728, 32, 1344,
        -1280, -416, 608, 32,
        -1728, -192, 1056, 32,
        -704, -768, 32, 352,
        -704, -160, 32, 352,
        -704, 192, 832, 32,
        -704, -800, 832, 32,
        96, -768, 32, 352,
        96, -160, 32, 352,
        96, -416, 448, 32,
        96, -192, 448, 32,
        512, -704, 32, 288,
        512, -160, 32, 768,
        704, -160, 32, 768,
        288, -736, 256, 32,
        288, -1056, 32, 320,
        704, -736, 32, 320,
        896, -1056, 32, 320,
        736, -736, 192, 32,
        480, -1088, 448, 32,
        -192, 576, 704, 32,
        736, 576, 384, 32,
        704, 704, 416, 32,
        1088, 384, 256, 32,
        1088, 896, 256, 32,
        1088, 736, 32, 160,
        1088, 416, 32, 160,
        1312, 416, 32, 480,
        -192, 704, 736, 32,
        512, 736, 224, 32,
        -768, 448, 608, 32,
        -192, 736, 32, 160,
        -160, 864, 64, 32,
        -128, 896, 32, 224,
        -768, 1120, 672, 32,
        -192, 480, 32, 96,
        -416, 704, 224, 32,
        -768, 896, 288, 32,
        -768, 480, 32, 512,
        -1792, 448, 1024, 32,
        -960, 640, 32, 928,
        -1152, 480, 32, 320,
        -1344, 960, 384, 32,
        -1792, 544, 480, 32,
        -2080, 192, 480, 32,
        -2080, 224, 32, 192,
        -1632, 224, 32, 224,
        -1632, 576, 32, 224,
        -2080, 416, 32, 384,
        -2048, 768, 416, 32,
        -1952, 448, 32, 128,
        288, -1504, 32, 448,
        480, -1504, 32, 416,
        -96, -1920, 192, 32,
        224, -1920, 192, 32,
        544, -1920, 192, 32,
        -832, -1760, 32, 128,
        -704, -1760, 32, 128,
        -992, -1088, 736, 32,
        -672, -1664, 416, 32,
        -992, -1664, 160, 32,
        -992, -1632, 32, 544,
        -256, -1664, 32, 608,
        -672, -1760, 992, 32,
        -832, -1920, 608, 32,
        -256, -2048, 32, 128,
        -256, -2080, 992, 32,
        0, -2048, 32, 128,
        320, -2048, 32, 128,
        704, -2048, 32, 128,
        480, -1760, 32, 256,
        704, -1888, 32, 160,
        512, -1760, 192, 32,
        256, -1728, 32, 256,
        736, -128, 448, 32,
        736, -480, 448, 32,
        1152, -448, 32, 320,
        -1344, 576, 32, 384,
        -768, 1152, 32, 288,
        -736, 1408, 864, 32,
        96, 1440, 32, 416,
        -1184, 1824, 1280, 32,
        -1184, 1568, 256, 32,
        -1216, 1568, 32, 288,
        -1728, -384, 32, 192
    };
    int n_paredes = sizeof(PAREDES)/sizeof(Rectangle);

    Rectangle PISO[] = {
        -1696, -1888, 384, 1696,
        -1312, -1888, 1088, 128,
        -224, -2048, 928, 288,
        288, -1760, 192, 704,
        -800, -1760, 96, 128,
        -960, -1632, 704, 544,
        -672, -768, 768, 960,
        -1312, -384, 1856, 192,
        704, -448, 448, 320,
        320, -1056, 576, 320,
        544, -736, 160, 1472,
        1120, 416, 192, 480,
        -736, 480, 544, 640,
        -192, 896, 64, 224,
        -192, 608, 1312, 96,
        -2048, 224, 416, 544,
        -1312, 480, 544, 480,
        -1632, 480, 320, 64,
        -928, 960, 192, 640,
        -1184, 1600, 448, 224,
        -736, 1440, 832, 384
    };
    int n_pisoTextures = sizeof(PISO)/sizeof(Rectangle);
  

    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){-1054,1716};
    xala.altura = 20;
    xala.largura = 20;

    Projetil bala[quantidade_maxima_flechas];

    //indice da flecha
    int projetil_atual = xala.quantidadeFlechas -1;

    //Limpando atributos
    for(int i = 0; i < quantidade_maxima_flechas; i++){
        bala[i].ativa = false;
    }
    Image temp = LoadImage("resources/images/marmore.png");
    ImageColorTint(&temp,(Color){50,50,150,255});
    pisoTexture = LoadTextureFromImage(temp);
    UnloadImage(temp);
    paredeTexture = LoadTexture("resources/images/pedra_brilhante.png");
    setTextureCropped(&flechasTexture, "resources/images/flechas.png", (Rectangle){0,0,64,64});

    for( int i = 0; i < quantidade_maxima_flechas; i++) {
        bala[i].textura = flechasTexture;
    }

    int n_inimigos = 30;
    Personagem inimigo[n_inimigos]; 
    

    for(int i = 0; i < n_inimigos; i++)
    {
        inimigo[i] = inimigoContructor();
    }
    posicionaInimigos(inimigo);

    setTargetCamera(&xala);
    cam.zoom = 1.6;
    // SetTargetFPS(60);



    // ------------ PORTAL ------------- //
    ///Retangulo responsável por representar a parte
    ///que o personagem colide para passar de fase
    int currentFrame = 0;
    int frameCount = 0;
    portalTexture =  LoadTexture("resources/images/portal.png");
    Rectangle portalCollision = (Rectangle) {-400, 1500, 32, 64 };
    Rectangle frameRecPortal = (Rectangle) {0 ,0 , portalTexture.width/4, portalTexture.height};
    // -------------------------------- //

    HideCursor();
    
    while(telaAtual == TELA_FASE_1){ 
        
        if(isPaused) {
            telaPausa();
        } else {

            if(IsKeyPressed(KEY_ESCAPE)) {
                isPaused = true;
            }

            if(xala.vida < 1) {
                telaAnterior = telaAtual;
                telaAtual = TELA_FRACASSO;
            }

            if(CheckCollisionPointRec(xala.posicao, portalCollision)) {
                telaAtual = TELA_FASE_2;
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

            playMusic(2);
       
            movimentar(&xala);
            colisaoPersonagem(&xala, PAREDES, n_paredes);


            // -----------Atualização da Camera------------- //
            atualizarCamera(&cam, xala.posicao);
            verificarTamanhoTela();


            if(IsKeyPressed(KEY_F)) telaCheia();            //
            if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;    // Temporario
            if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;  //
            
            // -------------------------------------------- //
            

            //------------Logica do Projetil--------------

         
            checkClickBow(projetil_atual);
            if(projetil_atual > -1)
            {
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    mira(xala,&bala[projetil_atual],cam);
                }
                else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    bala[projetil_atual].ativa = 1;
                    atira(xala,&bala[projetil_atual]);
                    projetil_atual--;
                }
            }
            
            for(int i = 0; i < xala.quantidadeFlechas; i++)
            {   
                if(bala[i].ativa)
                {
                    aplicarInerciaV(&bala[i].posicao, bala[i].velocidade);
                    aplicarAtritoProjetil(&bala[i],0.5);
                    colisaoProjetil_mapa(&bala[i], PAREDES, n_paredes);
                    colisaoProjetil_inimigo(&bala[i], inimigo, n_inimigos);
                }
            }
            
            if(bala[projetil_atual].velocidade.x == 0 && bala[projetil_atual].velocidade.y == 0 && bala[projetil_atual].ativa)
            {
                bala[projetil_atual].ativa = false;
            }
            
            // RAFAEL PARTE DE PEGAR OBJETO (flechas)
            if(projetil_atual +1 < xala.quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario

            //---------------------------------------------
            


            //----------Atualização dos inimigos-----------
            for( int i = 0; i < n_inimigos; i++)
            {
                if(inimigo[i].vida > 0) {
                    logicaInimigo(&inimigo[i], &xala);
                    colisaoPersonagem(&inimigo[i], PAREDES, n_paredes);
                    atualizarPersonagem(&inimigo[i]);
                }
            }



            //--------------INVUNERABILIDADE---------------
            if(xala.invulneravel)
            {
                if(GetTime() -xala.tempoInvulneravel > 2)
                {
                    xala.invulneravel = 0;
                }
            }

            BeginDrawing();
                ClearBackground((Color){20,20,20,255});

                BeginMode2D(cam);

                    
                    drawPiso(PISO, n_pisoTextures);
                    drawParedes(PAREDES, n_paredes);
                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){-400, 1500}, WHITE);
                    
                    drawInimigos(inimigo, n_inimigos);

                    DrawCircle(0,0,2,WHITE);
                    DrawCircleV(xala.posicao,10,xala.invulneravel ? GRAY : BLUE);

                    for (int i = 0; i < xala.quantidadeFlechas; i++)
                    {
                        
                        if(i > projetil_atual){
                            DrawTexturePro(bala[i].textura,
                                (Rectangle){0,28,64,8},
                                (Rectangle){
                                    bala[i].posicao.x,
                                    bala[i].posicao.y,
                                    64, 6},
                                (Vector2){48,2},
                                bala[i].angulo,WHITE);
                        }
                    }

                EndMode2D();
                
                DrawCircleV(GetMousePosition(),5,PURPLE);
                DrawText(TextFormat("Vida do inimigo: %i", temp_vida_inimigo),10,100,20,YELLOW);
                drawHUD(xala.vida, projetil_atual +1);
                
            EndDrawing();
        }
        if(isRestarting) 
        {
            isRestarting = false;
            break;
        }
    }
    
}
void posicionaInimigos(Personagem *inimigo)
{
    Vector2 inimigoPos[] = {
        -472, -601,
        -126, -608,
        -500, -116,
        -250, 13,
        -283, -273,
        -23, 103,
        -492, 119,
        -639, 549,
        -642, 794,
        -343, 557,
        -296, 863,
        -255, 995,
        -286, 1052,
        -1698, 678,
        -1961, 711,
        -1954, 281,
        1108, -407,
        1116, -196,
        802, -818,
        786, -941,
        -861, -1203,
        -610, -1214,
        -1610, -524,
        -1631, -1166,
        -1639, -1258,
        -344, -1481,
        -417, -1375,
        -463, -1282,
        628, -1986,
        -400, 1600
    };
    int n_inimigos = sizeof(inimigoPos)/sizeof(Vector2);
    for( int i = 0; i < n_inimigos; i++)
    {
        inimigo[i].posicao = inimigoPos[i];
    }

}
