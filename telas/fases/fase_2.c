#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/projetil.h"
    #include "../../lib/som.h"
#endif

#define TAM_MAPA_2 32 
#define TAM_PISO_2 13
#define QTD_INIMIGO_2 61

void fase_2();
void set_posicao_inimigos_2(Personagem inimigos[]);

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
        3136, 544, 32, 224,
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
    Texture2D marca_1;
    Texture2D marca_2;
    Texture2D marca_3;
    Texture2D marca_extra;
    setTextureCropped(&pisoTexture, "resources/images/full.png", (Rectangle){32*17,32*4,32,32 });
    setTextureCropped(&paredeTexture, "resources/images/full.png", (Rectangle){32*23,32*14,32,32 });
    setTexture(&portalTexture, "resources/images/portal.png",260, 160);
    setTextureCropped(&flechasTexture, "resources/images/Flechas.png", (Rectangle){0,0,64,64});
    setTextureCropped(&marca_1, "resources/images/full.png", (Rectangle){32*9, 32*10, 32,32});
    setTextureCropped(&marca_2, "resources/images/full.png", (Rectangle){32*24, 32*10,32,32});
    setTextureCropped(&marca_3, "resources/images/full.png", (Rectangle){32*56, 32*9,32,32});
    
    setTextureCropped(&marca_extra, "resources/images/full.png", (Rectangle){32*56, 32*9, 32, 32});
    //----------------------------------------------------------//



    // ------------ XALA ------------ //
    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){0, 0};
    xala.altura = 20;
    xala.largura = 20;
    // ----------------------------- //



    // ------------ INIMIGO ----------- //
    Personagem inimigos[QTD_INIMIGO_2];

    //Inicializando os inimigos
    for(int i = 0; i < QTD_INIMIGO_2; i++)
    {
        inimigos[i] = inimigoContructor();
    }
    set_posicao_inimigos_2(inimigos);

    // -------------------------------- //



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


    Rectangle portal_errado_1_collision = (Rectangle) {350, 410, 30, 60 };
    Rectangle portal_errado_2_collision = (Rectangle) {1131, -557, 30, 60 };
    Rectangle portal_certo_collision = (Rectangle) {2252, -224, 30, 60 };

    Rectangle frameRecPortal = (Rectangle) {0 ,0 , portalTexture.width/4, 160};
    // -------------------------------- //
    


    int contadorPortal = 0;
    Rectangle vidaUpgrade = (Rectangle) {3090, 640, 16, 16};;
    bool isUpgradeGetted = false;
    bool estaColidindo = false;



    while(telaAtual == TELA_FASE_2){ 
        
        //FUNCAO PARA TOCAR O SOM DE FUNDO
        playMusic(3);
        if(isPaused) 
        {
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
            if(CheckCollisionPointRec(xala.posicao, portal_certo_collision) && contadorPortal >= 2) {
                telaAtual = TELA_FASE_3;
                save();
            }

            if(CheckCollisionPointRec(xala.posicao, portal_certo_collision)) {
                contadorPortal++;
                estaColidindo = true;
                xala.posicao = (Vector2){0, 0};
            }

            // Apenas muda posição de xala
            if(CheckCollisionPointRec(xala.posicao, portal_errado_1_collision)) {
                xala.posicao = (Vector2){0, 0};
            }

            // Muda posição de xala e revive os inimigos
            if(CheckCollisionPointRec(xala.posicao, portal_errado_2_collision)) {
                xala.posicao = (Vector2){0, 0};
                set_posicao_inimigos_2(inimigos);
            }

            if(contadorPortal == 1 && estaColidindo) {
                setTextureCropped(&marca_extra, "resources/images/full.png", (Rectangle){32*24, 32*10, 32, 32});
                portal_errado_1_collision = (Rectangle) {2252, -224, 30, 60 };
                portal_errado_2_collision = (Rectangle) {1131, -557, 30, 60 };
                portal_certo_collision = (Rectangle) {350, 410, 30, 60 };
                set_posicao_inimigos_2(inimigos);
                estaColidindo = false;
            }

            if(contadorPortal == 2 && estaColidindo) {
                setTextureCropped(&marca_extra, "resources/images/full.png", (Rectangle){32*9, 32*10, 32, 32});
                portal_errado_1_collision = (Rectangle) {350, 410, 30, 60 };
                portal_errado_2_collision = (Rectangle) {2252, -224, 30, 60 };
                portal_certo_collision = (Rectangle) {1131, -557, 30, 60 };
                set_posicao_inimigos_2(inimigos);
                estaColidindo = false;
            }

            if(CheckCollisionPointRec(xala.posicao, vidaUpgrade) && !isUpgradeGetted && contadorPortal == 2) {
                vida_maxima_xala++;
                xala.vida = vida_maxima_xala;
                isUpgradeGetted = true;
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
                    colisaoProjetil_inimigo(&flechas[i], inimigos, QTD_INIMIGO_2);
                }
            }
            
            if(flechas[projetil_atual].velocidade.x == 0 && flechas[projetil_atual].velocidade.y == 0 && flechas[projetil_atual].ativa)
            {
                flechas[projetil_atual].ativa = false;
            }
            
            // RAFAEL PARTE DE PEGAR OBJETO (flechas)
            if(projetil_atual +1 < xala.quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario

            // -------------------------------------------------------- //



            // ---------- ATUALIZAÇÃO DOS INIMIGOS ----------- //
            for( int i = 0; i < QTD_INIMIGO_2; i++)
            {
                if(inimigos[i].vida > 0) {
                    logicaInimigo(&inimigos[i], &xala);
                    colisaoPersonagem(&inimigos[i], PAREDE, TAM_MAPA_2);
                    atualizarPersonagem(&inimigos[i]);
                }
            }
            // ------------------------------------------------ //


            movimentar(&xala);
            colisaoPersonagem(&xala, PAREDE, TAM_MAPA_2);
            atualizarCamera(&cam, xala.posicao);
        

            BeginDrawing();
                ClearBackground(GRAY);

                BeginMode2D(cam);
                    
                    drawParedes(PAREDE, TAM_MAPA_2);
                    drawPiso(PISO, TAM_PISO_2);

                    if(contadorPortal == 0) {
                        DrawTexture(marca_extra, -185, 190, WHITE);
                    }

                    if(contadorPortal == 1) {
                        DrawTexture(marca_extra, 3090, 640, WHITE);
                    }

                    if(contadorPortal == 2) {
                        DrawTexture(marca_extra, 1240, 501, WHITE);
                    }                    
                    
                    if(!isUpgradeGetted && contadorPortal == 2) {
                        DrawTexture(vidaTexture, vidaUpgrade.x, vidaUpgrade.y,  WHITE);
                    }

                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){1096, -627}, GREEN);
                    DrawTexture(marca_1, 1115, -577, WHITE);

                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){317, 390}, GREEN);
                    DrawTexture(marca_2, 335, 450, WHITE);

                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){2220, -290}, GREEN);
                    DrawTexture(marca_3, 2240, -234, WHITE);
                    
                    drawInimigos(inimigos, QTD_INIMIGO_2);
                    drawXala(&xala, 0);
                    drawFlecha(flechas, xala.quantidadeFlechas);

                EndMode2D();

                DrawText(FormatText("%.2f %.2f",xala.posicao.x, xala.posicao.y),10,100,20,YELLOW);

                // "Mira" do mouse
                DrawCircleV(GetMousePosition(), 5, PURPLE);

                drawHUD(xala.vida, projetil_atual+1);

            EndDrawing();
        }
        if(isRestarting) 
        {
            if(isUpgradeGetted) {
                vida_maxima_xala--;
            }
            isRestarting = false;
            break;
        }
    }
}

void set_posicao_inimigos_2(Personagem inimigos[]) {

    inimigos[0].posicao = (Vector2){2930, 650};
    inimigos[1].posicao = (Vector2){664, -42};
    inimigos[2].posicao = (Vector2){608, 35};
    inimigos[3].posicao = (Vector2){621, 200};
    inimigos[4].posicao = (Vector2){693, 359};
    inimigos[5].posicao = (Vector2){594, 459};
    inimigos[6].posicao = (Vector2){819, 393};
    inimigos[7].posicao = (Vector2){763, 536};
    inimigos[8].posicao = (Vector2){531, 542};
    inimigos[9].posicao = (Vector2){466, 400};
    inimigos[10].posicao = (Vector2){325, 570};
    inimigos[11].posicao = (Vector2){924, -44};
    inimigos[12].posicao = (Vector2){1023, 53};
    inimigos[13].posicao = (Vector2){1167, 11};
    inimigos[14].posicao = (Vector2){1385, -132};
    inimigos[15].posicao = (Vector2){1364, -234};
    inimigos[16].posicao = (Vector2){1145, -225};
    inimigos[17].posicao = (Vector2){1242, -139};
    inimigos[18].posicao = (Vector2){1377, -543};
    inimigos[19].posicao = (Vector2){1295, -609};
    inimigos[20].posicao = (Vector2){1244, -475};
    inimigos[21].posicao = (Vector2){1124, 174};
    inimigos[22].posicao = (Vector2){1224, 230};
    inimigos[23].posicao = (Vector2){1407, 273};
    inimigos[24].posicao = (Vector2){1386, 317};
    inimigos[25].posicao = (Vector2){1315, 416};
    inimigos[26].posicao = (Vector2){1454, 516};
    inimigos[27].posicao = (Vector2){1224, 462};
    inimigos[28].posicao = (Vector2){1100, 548};
    inimigos[29].posicao = (Vector2){1077, 393};
    inimigos[30].posicao = (Vector2){1200, 300};
    inimigos[31].posicao = (Vector2){1142, 420};
    inimigos[32].posicao = (Vector2){1196, 243};
    inimigos[33].posicao = (Vector2){1600, -30};
    inimigos[34].posicao = (Vector2){1700, 70};
    inimigos[35].posicao = (Vector2){1844, 40};
    inimigos[36].posicao = (Vector2){2010, 25};
    inimigos[37].posicao = (Vector2){2152, 7};
    inimigos[38].posicao = (Vector2){2360, 33};
    inimigos[39].posicao = (Vector2){2580, -171};
    inimigos[40].posicao = (Vector2){2465, -271};
    inimigos[41].posicao = (Vector2){2387, -193};
    inimigos[42].posicao = (Vector2){2330, -131};
    inimigos[43].posicao = (Vector2){2330, -236};
    inimigos[44].posicao = (Vector2){2400, -261};
    inimigos[45].posicao = (Vector2){2331, 163};
    inimigos[46].posicao = (Vector2){2547, 253};
    inimigos[47].posicao = (Vector2){2470, 352};
    inimigos[48].posicao = (Vector2){2260, 322};
    inimigos[49].posicao = (Vector2){2117, 222};
    inimigos[50].posicao = (Vector2){2058, 366};
    inimigos[51].posicao = (Vector2){2258, 487};
    inimigos[52].posicao = (Vector2){2076, 708};
    inimigos[53].posicao = (Vector2){2320, 610};
    inimigos[54].posicao = (Vector2){2398, 508};
    inimigos[55].posicao = (Vector2){2430, 350};
    inimigos[56].posicao = (Vector2){2400, 620};
    inimigos[57].posicao = (Vector2){2600, 700};
    inimigos[58].posicao = (Vector2){2711, 630};
    inimigos[59].posicao = (Vector2){2810, 685};
}

