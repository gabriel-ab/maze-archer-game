#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/projetil.h"
    #include "../../lib/som.h"
#endif
void fase_1();

void fase_1()
{
    Rectangle PAREDES[] = {
        -256, -256, 32, 512,
        -224, -256, 352, 32,
        -224, 224, 352, 32,
        96, -96, 32, 320,
        128, -256, 544, 32,
        128, -96, 544, 32,
        640, -672, 32, 416,
        640, -64, 32, 416,
        800, -96, 32, 416,
        800, -640, 32, 416,
        832, -256, 512, 32,
        832, -96, 512, 32,
        1312, -544, 512, 32,
        1312, 160, 512, 32,
        1312, -64, 32, 224,
        1312, -512, 32, 256,
        1792, -512, 32, 672,
        448, 480, 32, 320,
        1056, 320, 32, 320,
        960, 320, 96, 32,
        832, 288, 160, 32,
        544, 320, 96, 32,
        480, 352, 96, 32,
        448, 384, 64, 32,
        448, 416, 32, 64,
        480, 768, 480, 32,
        960, 736, 32, 64,
        992, 704, 32, 64,
        1024, 672, 32, 64,
        1056, 640, 32, 64
    };
    int n_paredes = sizeof(PAREDES)/sizeof(Rectangle);

    Rectangle PISO[] = {
        -224, -224, 320, 448,
        96, -224, 1248, 128,
        672, -96, 128, 416,
        672, -640, 128, 416,
        1344, -512, 448, 672,
        672, 320, 288, 448,
        480, 416, 192, 352,
        960, 352, 96, 320,
        960, 672, 64, 32,
        960, 704, 32, 32,
        576, 352, 96, 64,
        512, 384, 64, 32
    };
    int n_pisoTextures = sizeof(PISO)/sizeof(Rectangle);
  

    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){0,0};
    xala.altura = 20;
    xala.largura = 20;

    Projetil bala[quantidade_maxima_flechas];

    //indice da flecha
    int projetil_atual = xala.quantidadeFlechas -1;

    //Limpando atributos
    for(int i = 0; i < quantidade_maxima_flechas; i++){
        bala[i].ativa = false;
    }

    pisoTexture = LoadTexture("resources/images/chao_cav.png");
    paredeTexture = LoadTexture("resources/images/pedra.png");
    setTextureCropped(&flechasTexture, "resources/images/Flechas.png", (Rectangle){0,0,64,64});

    for( int i = 0; i < quantidade_maxima_flechas; i++) {
        bala[i].textura = flechasTexture;
    }

    Personagem inimigo[10];
    int n_inimigos = sizeof(inimigo)/sizeof(Personagem);

    for(int i = 0; i < n_inimigos; i++)
    {
        inimigo[i] = inimigoContructor();
        inimigo[i].posicao = (Vector2){GetRandomValue(-200,200), GetRandomValue(-200,200)};
    }

    setTargetCamera(&xala);

    // SetTargetFPS(60);
    double contadorInvulneravel =0;


    // ------------ PORTAL ------------- //
    ///Retangulo responsável por representar a parte
    ///que o personagem colide para passar de fase
    int currentFrame = 0;
    int frameCount = 0;
    setTexture(&portalTexture, "resources/images/portal.png",260, 160);
    Rectangle portalCollision = (Rectangle) {1500, -100, 30, 60 };
    Rectangle frameRecPortal = (Rectangle) {0 ,0 , portalTexture.width/4, 160};
    // -------------------------------- //
    
    while(telaAtual == TELA_FASE_1){ 
        
        playMusic(2);
        
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
                if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
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
                logicaInimigo(&inimigo[i],&xala);

                colisaoPersonagem(&inimigo[i], PAREDES, n_paredes);
                atualizarPersonagem(&inimigo[i]);
            }



            //--------------INVUNERABILIDADE---------------
            if(xala.invulneravel)
            {
                if(GetTime() -contadorInvulneravel > 2)
                {
                    contadorInvulneravel =  GetTime();
                    xala.invulneravel = 0;
                }
            }

            BeginDrawing();
                ClearBackground(DARKGRAY);

                BeginMode2D(cam);

                    
                    drawPiso(PISO, n_pisoTextures);
                    drawParedes(PAREDES, n_paredes);
                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){1500, -150}, BLUE);


                    for(int i = 0; i < n_inimigos; i++)
                    {
                        DrawCircleV(inimigo[i].posicao, 10, (Color){150,150,255,120});
                    }

                    DrawCircle(0,0,2,WHITE);
                    DrawCircleV(xala.posicao,10,BLUE);
                    for (int i = 0; i < xala.quantidadeFlechas; i++)
                    {
                        DrawCircleV(bala[i].posicao,5,GREEN);

                        DrawTexturePro(bala[i].textura,
                        (Rectangle){0,28,64,8},
                        (Rectangle){
                            bala[i].posicao.x,
                            bala[i].posicao.y,
                            64, 6},
                        (Vector2){48,2},
                        bala[i].angulo,WHITE);
                    }

                    DrawCircle(
                        (GetMouseX() -cam.offset.x),
                        (GetMouseY() -cam.offset.y),
                        5,PURPLE);
                    DrawCircleV(c,10,BROWN); //Temporario visualização do hitbox do inimigo
                
                    

                EndMode2D();

                // DrawText(FormatText("xala.posicao %.2f %.2f",xala.posicao.x, xala.posicao.y),10,10,20,YELLOW);
                // DrawText(FormatText("target %.2f %.2f",cam.target.x, cam.target.y),10,30,20,YELLOW);
                // DrawText(FormatText("offset %.2f %.2f",cam.offset.x, cam.offset.y),10,50,20,YELLOW);
                // DrawText(FormatText("vel %.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,70,20,YELLOW);
                // DrawText(FormatText("zoom %.2f",cam.zoom),10,90,20,YELLOW);
                // DrawText(FormatText("Projetil atual %i",projetil_atual),10,130,20,YELLOW);
                DrawText(FormatText("invuneravel: %i",xala.invulneravel),10,200,20,YELLOW);
                // DrawText(FormatText("contador: %i",inimigo[0].acao.contador),10,240,20,YELLOW);

                drawHUD(xala.vida, xala.quantidadeFlechas);
                
                // DrawText(FormatText("nPAREDESs %i",n_pisoTextures),10,350,20,YELLOW);
            EndDrawing();
        }
        if(isRestarting) 
        {
            isRestarting = false;
            break;
        }
    }
    
}
