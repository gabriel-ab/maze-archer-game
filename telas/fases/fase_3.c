#include <raylib.h>

#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/draw.c"
#include "../../lib/data.c"

#define TAM_MAPA_3 76
#define TAM_PISO_3 19
#define TAM_ARMADILHAS_3 15
#define QTD_INIMIGO_3 60

void fase_3();
void draw_fase_3(Personagem* xala, Personagem inimigos[], Projetil flechas[], Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]);
void logica_fase_3(Personagem* xala, Personagem inimigo[], Projetil flecha[], Rectangle PAREDES[], Rectangle ARMADILHA[]);
void set_posicao_inimigos(Personagem inimigos[]);

Rectangle frameRecArmadilha;
Rectangle frameRecPortal;
Rectangle portalCollision;

Rectangle vidaUpgrade;
bool isUpgradeGetted;

int projetil_atual;

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
    setTextureCropped(&pisoTexture, "resources/images/full.png", (Rectangle){960,64,32,32 });
    setTextureCropped(&paredeTexture, "resources/images/floortileset.png", (Rectangle){32,128,32,32 });
    setTextureCropped(&armadilhaTexture, "resources/images/full.png", (Rectangle){1920,160,128,32 });
    setTexture(&portalTexture, "resources/images/portal.png",260, 160);
    setTextureCropped(&flechasTexture, "resources/images/Flechas.png", (Rectangle){0,0,64,64});
    //--------------------------------------------------//


    frameRecArmadilha = (Rectangle) {0 ,0 ,30, 30};
    frameRecPortal = (Rectangle) {0 ,0 , portalTexture.width/4, 160};



    ///Retangulo responsável por representar a parte
    ///que o personagem colide para passar de fase
    portalCollision = (Rectangle) {2740, -1145, 30, 60 };



    ///Retangulo responsável por representar o item que
    /// aumenta a vida máxima de xala
    vidaUpgrade = (Rectangle) {950, 990, 16, 16};
    isUpgradeGetted = false;


    
    // ------------ XALA ------------ //
    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){0, 0};
    xala.altura = 20;
    xala.largura = 20;
    // ----------------------------- //



    // ------------ INIMIGO ----------- //
    Personagem inimigos[QTD_INIMIGO_3];

    //Inicializando os inimigos
    for(int i = 0; i < QTD_INIMIGO_3; i++)
    {
        inimigos[i] = inimigoContructor();
    }
    set_posicao_inimigos(inimigos);

    // -------------------------------- //



    // ------------FLECHA ------------ //
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



    while(telaAtual == TELA_FASE_3) {
        
        if(isPaused) 
        {
            telaPausa();

        } else 
        {
            draw_fase_3(&xala, inimigos, flechas, PAREDES, PISO, ARMADILHAS);
            logica_fase_3(&xala, inimigos, flechas, PAREDES, ARMADILHAS); 
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

//Função responsável por exibir a Fase 3
void draw_fase_3(Personagem* xala, Personagem inimigos[], Projetil flechas[], Rectangle PAREDES[], Rectangle PISO[], Rectangle ARMADILHAS[]) {
    
    BeginDrawing();
        BeginMode2D(cam);

            ClearBackground(BLACK);

            drawPiso(PISO, TAM_PISO_3);
            drawArmadilhasRec(ARMADILHAS, TAM_ARMADILHAS_3, frameRecArmadilha);
            drawParedes(PAREDES, TAM_MAPA_3);
            DrawTextureRec(portalTexture, frameRecPortal, (Vector2){2720, -1184}, RED);
            drawInimigos(inimigos, QTD_INIMIGO_3);


            if(!isUpgradeGetted) {
                DrawTexture(vidaTexture, vidaUpgrade.x, vidaUpgrade.y,  WHITE);
            }
            

            drawXala(xala, count);
            drawFlecha(flechas, xala->quantidadeFlechas);


        EndMode2D();

        // "Mira" do mouse
        DrawCircleV(GetMousePosition(), 5, PURPLE);

        drawHUD(xala->vida, projetil_atual+1);

    EndDrawing();
}

//Função responsável pela lógica da Fase 3
void logica_fase_3(Personagem* xala, Personagem inimigo[], Projetil flecha[], Rectangle PAREDES[], Rectangle ARMADILHA[]) {
    
    playMusic(2);
    HideCursor();

    if(IsKeyPressed(KEY_ESCAPE)) {
        isPaused = !isPaused;
    }

    if(xala->vida < 1) {
        telaAnterior = telaAtual;
        telaAtual = TELA_FRACASSO;
    }

    if(CheckCollisionPointRec(xala->posicao, vidaUpgrade) && !isUpgradeGetted) {
        vida_maxima_xala++;
        xala->vida = vida_maxima_xala;
        isUpgradeGetted = true;
    }

    if(CheckCollisionPointRec(xala->posicao, portalCollision)) {
        telaAtual = TELA_FASE_4;
        save();
    }
    


    // -------------- ATUALIZAÇÃO DE XALA ---------------- //
    movimentar(xala);
    colisaoPersonagem(xala, PAREDES, TAM_MAPA_3);
    atualizarCamera(&cam, xala->posicao);
    // --------------------------------------------------- //



    // ------------ LÓGICA DA INVULNERABILIDADE -------------- //
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
    // -------------------------------------------------------- //




    // ---------- ATUALIZAÇÃO DOS INIMIGOS ----------- //
    for( int i = 0; i < QTD_INIMIGO_3; i++)
    {
        if(inimigo[i].vida > 0) {
            logicaInimigo(&inimigo[i],&xala);
            colisaoPersonagem(&inimigo[i], PAREDES, TAM_MAPA_3);
            atualizarPersonagem(&inimigo[i]);
        }
    }
    // ------------------------------------------------ //




    // ----------------------- LÓGICA DO PROJÉTIL ------------------------ //
    
    checkClickBow(projetil_atual);

    if(projetil_atual > -1)
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            mira(*xala,&flecha[projetil_atual],cam);
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            flecha[projetil_atual].ativa = true;

            atira( *xala, &flecha[projetil_atual] );

            projetil_atual--;
        }
    }
    
    for(int i = 0; i < xala->quantidadeFlechas; i++)
    {   
        if(flecha[i].ativa)
        {
            aplicarInerciaV(&flecha[i].posicao, flecha[i].velocidade);
            aplicarAtritoProjetil(&flecha[i],0.5);
            colisaoProjetil_mapa(&flecha[i], PAREDES, TAM_MAPA_3);
            colisaoProjetil_inimigo(&flecha[i], inimigo, QTD_INIMIGO_3);
        }
    }
    
    if(flecha[projetil_atual].velocidade.x == 0 && flecha[projetil_atual].velocidade.y == 0 && flecha[projetil_atual].ativa)
    {
        flecha[projetil_atual].ativa = false;
    }
    
    // RAFAEL PARTE DE PEGAR OBJETO (flechas)
    if(projetil_atual +1 < xala->quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario

    // -------------------------------------------------------- //



    // -------- LÓGICA DA ANIMAÇÃO: SPRITE LAVA & PORTAL ---------- //
    frameCount++;
    if (frameCount >= (20))
    {
        frameCount = 0;
        currentFrame++;

        if (currentFrame > 4) currentFrame = 0;
        
        frameRecArmadilha.x = (float)currentFrame * (float)armadilhaTexture.width/4;
        frameRecPortal.x = (float)currentFrame * (float)portalTexture.width/4;
    }
    // ------------------------------------------------------------ //

}

void set_posicao_inimigos(Personagem inimigos[]) {
    inimigos[0].posicao = (Vector2){666, -99};
    inimigos[1].posicao = (Vector2){666, 130};
    inimigos[2].posicao = (Vector2){833, 132};
    inimigos[3].posicao = (Vector2){911, 210};
    inimigos[4].posicao = (Vector2){1042, 92};
    inimigos[5].posicao = (Vector2){1052, -104};

    inimigos[6].posicao = (Vector2){672, -768};
    inimigos[7].posicao = (Vector2){729, -868};
    inimigos[8].posicao = (Vector2){650, -968};
    inimigos[9].posicao = (Vector2){772, -1068};
    inimigos[10].posicao = (Vector2){900, -1017};
    inimigos[11].posicao = (Vector2){1041, -1095};
    inimigos[12].posicao = (Vector2){1000, -948};
    inimigos[13].posicao = (Vector2){990, -810};

    inimigos[14].posicao = (Vector2){1729, -123};
    inimigos[15].posicao = (Vector2){1824, -45};
    inimigos[16].posicao = (Vector2){1902, -123};
    inimigos[17].posicao = (Vector2){1902, -123};
    inimigos[18].posicao = (Vector2){1906, 0};
    inimigos[19].posicao = (Vector2){1828, 75};
    inimigos[20].posicao = (Vector2){1871, 175};
    inimigos[21].posicao = (Vector2){1750, 119};
    inimigos[22].posicao = (Vector2){1781, 41};
    inimigos[23].posicao = (Vector2){1578, 245};

    inimigos[24].posicao = (Vector2){1670, 911};
    inimigos[25].posicao = (Vector2){1613, 989};
    inimigos[26].posicao = (Vector2){1670, 1067};
    inimigos[27].posicao = (Vector2){1592, 1145};
    inimigos[28].posicao = (Vector2){1739, 1002};
    inimigos[29].posicao = (Vector2){1860, 1080};
    inimigos[30].posicao = (Vector2){1917, 1158};
    inimigos[31].posicao = (Vector2){1933, 950};
    inimigos[32].posicao = (Vector2){1909, 806};

    inimigos[33].posicao = (Vector2){2616, -228};
    inimigos[34].posicao = (Vector2){2672, -328};
    inimigos[35].posicao = (Vector2){2750, -228};
    inimigos[36].posicao = (Vector2){2872, -300};
    inimigos[37].posicao = (Vector2){2928, -159};
    inimigos[38].posicao = (Vector2){2850, -80};
    inimigos[39].posicao = (Vector2){2928, 0};
    inimigos[40].posicao = (Vector2){2930, 74};
    inimigos[41].posicao = (Vector2){2986, 174};
    inimigos[42].posicao = (Vector2){2900, 275};
    inimigos[43].posicao = (Vector2){2864, 352};
    inimigos[44].posicao = (Vector2){2981, 430};
    inimigos[45].posicao = (Vector2){2702, 364};
    inimigos[46].posicao = (Vector2){2581, 420};
    inimigos[47].posicao = (Vector2){2540, 277};
    inimigos[48].posicao = (Vector2){2645, 255};
    inimigos[49].posicao = (Vector2){2726, 205};
    inimigos[50].posicao = (Vector2){2695, 45};

    inimigos[51].posicao = (Vector2){1828, -724};
    inimigos[52].posicao = (Vector2){1820, -864};
    inimigos[53].posicao = (Vector2){1598, -753};
    inimigos[54].posicao = (Vector2){1605, -945};
    inimigos[55].posicao = (Vector2){1682, -1023};
    inimigos[56].posicao = (Vector2){1604, -1101};
    inimigos[57].posicao = (Vector2){1772, -1046};
    inimigos[58].posicao = (Vector2){1915, -1042};
    inimigos[59].posicao = (Vector2){1993, -942};
}

