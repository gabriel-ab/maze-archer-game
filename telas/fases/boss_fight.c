#include <raylib.h>

#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/draw.h"

#define MAX_PEDRAS 50

typedef struct Pedra {
    bool ativa;
    int altura;
    int largura;
    Vector2 posicao;
    Vector2 velocidade;
    Color color;
    Rectangle linhaColisaoCima;
    Rectangle linhaColisaoEsquerda;
    Rectangle linhaColisaoBaixo;
    Rectangle linhaColisaoDireita;
} Pedra;


void boss_fight();
void draw_boss_fight(Personagem* xala, Personagem* boss, Projetil flechas[], Rectangle PAREDES[], Rectangle PISO[]);
void logica_boss_fight(Personagem* xala, Personagem* boss, Projetil flecha[], Rectangle PAREDES[]);
void movimentacaoBoss(Vector2 alvo);
Pedra pedraConstructor();
void setLinhaColisaoBoss(Personagem *boss);
void setLinhaColisaoPedra(Pedra *pedra);

Personagem boss;
Rectangle frameRecPersonagem;
Rectangle barraVidaBoss;


Pedra *pedras;
Texture2D pedraTexture;
int pedrasCount = 0;

int vidaBoss;
int contador;

Rectangle end1;
Rectangle end2;

//Função responsável por representar a Fase final
void boss_fight()
{

    Rectangle PISO[] = { -128, -128, 512, 512};

    Rectangle PAREDES[] = {
        -128, -160, 512, 32,
        -160, -160, 32, 576,
        -128, 384, 512, 32,
        384, -160, 32, 576
    };


    pedras = (Pedra *)malloc(MAX_PEDRAS*sizeof(Pedra));


    // ----------- XALA ------------ //
    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){50, 50};
    xala.altura = 48;
    xala.largura = 48;
    xala.sprite = spriteConstructor("resources/images/personagem.png",48,48,15);
    // ----------------------------- //



    // ----------- BOSS ------------ //
    boss = inimigoContructor();
    boss.vida = 10;
    boss.altura = 64;
    boss.largura = 32;
    setLinhaColisaoBoss(&boss);
    frameRecPersonagem = (Rectangle) {0, 0, 64, 64};
    barraVidaBoss = (Rectangle) {
        GetScreenWidth() / 10, 
        GetScreenHeight() - GetScreenHeight() / 10, 
        GetScreenWidth() - GetScreenWidth() / 5,
        32
    };
    // ----------------------------- //


    vidaBoss = barraVidaBoss.width/boss.vida;


    // ----------------- TEXTURE CENÁRIO --------------- //
    setTexture(&portalTexture, "resources/images/portal.png",260, 160);
    setTextureCropped(&boss.sprite, "resources/images/golem-walk.png", (Rectangle){0,128,448,64});
    setTextureCropped(&flechasTexture, "resources/images/Flechas.png", (Rectangle){0,0,64,64});
    pisoTexture = LoadTexture("resources/images/cave_floor.png");
    paredeTexture = LoadTexture("resources/images/tijolos.png");
    pedraTexture = LoadTexture("resources/images/pedra.png");
    //--------------------------------------------------//



    // ------------FLECHA ------------ //
    Projetil flechas[quantidade_maxima_flechas];

    // indice da flecha
    projetil_atual = xala.quantidadeFlechas -1;
    

    // Inicializando as flechas
    for(int i = 0; i < quantidade_maxima_flechas; i++){
        flechas[i].ativa = false;
        flechas[i].textura = flechasTexture;
    }
    // -------------------------------- //

    end1 = (Rectangle) {0 - GetScreenWidth(),0, GetScreenWidth(), GetScreenHeight()};
    end2 = (Rectangle) {GetScreenWidth(),0, GetScreenWidth(), GetScreenHeight()};

    setTargetCamera(&xala);

    
    while(telaAtual == BOSS_FIGHT && !WindowShouldClose()) {
        TEMPO = GetTime();
        if(isPaused) 
        {
            telaPausa();

        } else 
        {
            draw_boss_fight(&xala, &boss, flechas, PAREDES, PISO);
            logica_boss_fight(&xala, &boss, flechas, PAREDES); 
        }

        if(isRestarting) 
        {
            isRestarting = false;
            break;
        }
    }

    free(pedras);      
    UnloadTexture(pedraTexture);
}

//Função responsável por exibir a Fase final
void draw_boss_fight(Personagem* xala, Personagem* boss, Projetil flechas[], Rectangle PAREDES[], Rectangle PISO[]) {
    
    BeginDrawing();
        BeginMode2D(cam);

            ClearBackground(GRAY);

            drawPiso(PISO, 1);
            drawParedes(PAREDES, 4);

            if(boss->vida > 0) {

                //BOSS
                DrawTextureRec(
                    boss->sprite.textura, 
                    frameRecPersonagem, 
                    boss->posicao, 
                    WHITE);
            }
            drawXala(xala);
            drawFlecha(flechas, *xala);

            // ------------------ PEDRAS ----------------- //
            if(boss->vida > 0) {
                
                for (int i = 0; i < pedrasCount; i++)
                {
                    DrawTexture(pedraTexture, pedras[i].posicao.x, pedras[i].posicao.y, pedras[i].color);
                }
            }
            // -------------------------------------------- //

            
        EndMode2D();
        // "Mira" do mouse
        DrawCircleV(GetMousePosition(),5,PURPLE);

        if(boss->vida > 0) {
            // ----------- BARRA DE VIDA ---------------- //
            DrawRectangleRec(barraVidaBoss, RED);
            DrawRectangleLinesEx(
                (Rectangle) {
                    GetScreenWidth() / 10, 
                    GetScreenHeight() - GetScreenHeight() / 10, 
                    GetScreenWidth() - GetScreenWidth() / 5,
                    32
                }, 
                5, BLACK);
            DrawText(
                "GOLEM DE GELO", 
                barraVidaBoss.x + ((GetScreenWidth() - GetScreenWidth() / 5) / 2) - 20*3,
                barraVidaBoss.y + 8,
                20, BLACK);
            // ------------------------------------------ //
        }

        drawHUD(xala->vida, projetil_atual+1);

        if(boss->vida <= 0) {
            DrawRectangleRec(end1, BLACK);
            DrawRectangleRec(end2, BLACK);
        }

        if((CheckCollisionRecs(end1, end2))) {
            DrawText("CONTINUA . . .", GetScreenWidth()/2 - (20*6), GetScreenHeight()/2, 30, RED);
        }

    EndDrawing();
}

//Função responsável pela lógica da Fase final
void logica_boss_fight(Personagem* xala, Personagem* boss, Projetil flecha[], Rectangle PAREDES[]) {
    
    HideCursor();
    contador++;

    if(IsKeyPressed(KEY_ESCAPE)) {
        isPaused = !isPaused;
    }

    if(xala->vida < 1) {
        telaAnterior = telaAtual;
        telaAtual = TELA_FRACASSO;
    }

    if(CheckCollisionPointRec(xala->posicao, portalCollision)) {
        telaAtual = TELA_MENU;
        save();
    }
    

    // ----------- ATUALIZAÇÃO DE XALA -------------//
    movimentar(xala);
    colisaoPersonagem(xala, PAREDES, 4);
    atualizarCamera(&cam, xala->posicao);
    // --------------------------------------------------- //


    //--------------INVUNERABILIDADE---------------
    if(xala->invulneravel)
    {
        if(TEMPO -xala->tempoInvulneravel > 2)
        {
            xala->invulneravel = 0;
        }
    }


    // ------------- LÓGICA: MIRA & DISPARO DA FLECHA ------------------- //
    checkClickBow();

    if(projetil_atual > -1)
    {
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            mirando = true;
            mira(*xala,&flecha[projetil_atual],cam);
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mirando = false;
            flecha[projetil_atual].ativa = true;

            atira( *xala, &flecha[projetil_atual] );

            projetil_atual--;
        }
    }
    // ------------------------------------------------------------------ //
    


    // ------------ LÓGICA DESATIVAR FLECHA ----------------- //
    if(flecha[projetil_atual].velocidade.x == 0 && flecha[projetil_atual].velocidade.y == 0 && flecha[projetil_atual].ativa)
    {
        flecha[projetil_atual].ativa = false;
    }
    // ------------------------------------------------------- //
    


    // RAFAEL PARTE DE PEGAR OBJETO (flechas)
    if(projetil_atual +1 < xala->quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario
    // ------------------------------------------------------ //



    if(boss->vida > 0) {

        // ----------------- COLISÃO FLECHA E GOLEM --------------- //
        for(int i = 0; i < xala->quantidadeFlechas; i++)
        {   
            if(flecha[i].ativa)
            {
                aplicarInerciaV(&flecha[i].posicao, flecha[i].velocidade);
                aplicarAtritoProjetil(&flecha[i],0.5);
                colisaoProjetil_mapa(&flecha[i], PAREDES, 4);
                
                
                if(CheckCollisionCircleRec(flecha[i].posicao, 5, (Rectangle){boss->posicao.x, boss->posicao.y, boss->largura, boss->altura }))
                {
                    flecha[i].velocidade = boss->velocidade;
                    boss[i].vida--;
                    flecha[i].ativa = false;
                    barraVidaBoss.width = vidaBoss*(boss->vida);
                }
            }
        }
        // ------------------------------------------------------------- //

        // -------------- COLISÃO XALA PEDRA ------------ //
        for (int i = 0; i < pedrasCount; i++)
        {
            bool estaColidindo = CheckCollisionCircles(xala->posicao, 16, (Vector2){pedras[i].posicao.x + 16, pedras[i].posicao.y + 16}, 16);


            if(estaColidindo && pedras[i].ativa && !(xala->invulneravel))  {
                xala->vida--;
                xala->invulneravel = !(xala->invulneravel);
                xala->tempoInvulneravel = TEMPO;
                pedras[i].ativa = false;
                pedrasCount--;   
            }
        }
        // ------------------------------------------------ //
        


        // -------- LÓGICA DA ANIMAÇÃO: GOLEM ---------- //
        frameCount++;
        if (frameCount % 10 == 0)
        {
            currentFrame++;

            if (currentFrame > 7) currentFrame = 0;
            frameRecPersonagem.x = (float)currentFrame * (float)boss->sprite.textura.width/7;
        }
        // --------------------------------------------- //
        //----------Atualização dos sprites------------
        if(IsKeyDown(KEY_A)) {
            xala->sprite.n_segmento = 0;
            animaSprite(&xala->sprite, segmentos_xala);
        }
        if(IsKeyDown(KEY_D)) {
            xala->sprite.n_segmento = 1;
            animaSprite(&xala->sprite, segmentos_xala);
        }
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_S)){
            animaSprite(&xala->sprite, segmentos_xala);
        }

        //---------------------------------------------


        // ----------- ATUALIZAÇÃO DO BOSS -------------//
        if(!CheckCollisionPointCircle(
            xala->posicao, 
            (Vector2) {
                boss->posicao.x + boss->sprite.textura.height/2, 
                boss->posicao.y + boss->sprite.textura.height/2,
            }, 256) 
            || pedrasCount >= MAX_PEDRAS)
        {
            // Se o pedrasCount >= MAX_PEDRAS
            // Então o Boss vai para o canto inferior direito
            // Senão o Boss vai perseguir Xala
            if(pedrasCount >= MAX_PEDRAS) {
                
                if(
                    boss->posicao.x ==  192 && 
                    boss->posicao.y == 208
                ) {
                    currentFrame = 0;
                    
                    if(xala->posicao.x > boss->posicao.x) {
                        setTextureCropped(&boss->sprite, "resources/images/golem-walk.png", (Rectangle){0,192,448,64});
                    }

                    if(xala->posicao.x < boss->posicao.x) {
                        setTextureCropped(&boss->sprite, "resources/images/golem-walk.png", (Rectangle){0,64,448,64});
                    }
                }

                movimentacaoBoss((Vector2) {192, 208});

            } else {
                movimentacaoBoss(xala->posicao);
            }
            
            setLinhaColisaoBoss(boss);

        } else {
            // ----------------- ATAQUE BOSS ANIMAÇÃO -------------------- //
            if(xala->posicao.x > boss->posicao.x) {
                setTextureCropped(&boss->sprite, "resources/images/golem-atk.png", (Rectangle){0,320,448,64});
            }   

            if(xala->posicao.x < boss->posicao.x) {
                setTextureCropped(&boss->sprite, "resources/images/golem-atk.png", (Rectangle){0,128,448,64});
            }
            // ---------------------------------------------------//



            // ----------------- ATAQUE BOSS -------------------- //
            if(frameCount % 20 == 0 && currentFrame == 4) {
                for (int i = 0; i < 5; i++)
                {
                    pedras[pedrasCount] = pedraConstructor(boss);
                    setLinhaColisaoPedra(&pedras[i]);
                    pedrasCount++;
                }
            }
            // ---------------------------------------------------//
        }



        // ----------------- COLISÃO DAS PEDRAS COM A PAREDE -------------------- //
        for (int i = 0; i < pedrasCount; i++)
        {
            if(pedras[i].ativa) {
                
                pedras[i].posicao.x += pedras[i].velocidade.x;
                pedras[i].posicao.y += pedras[i].velocidade.y;

                for (int j = 0; j < 4; j++)
                {
                    if(CheckCollisionPointRec(pedras[i].posicao, PAREDES[j])) {
                        pedras[i].velocidade.x *= -1;
                        pedras[i].velocidade.y *= -1;
                    }
                }
            }
        }
        // ----------------------------------------------------------------------- //
        


        // PEDRA DESATIVA DEPOIS DE 10 SEGUNDOS
        for (int i = 0; i < pedrasCount; i++)
        {
            if(frameCount % 600 == 0) {
                pedras[i].ativa = false;
                
            }

            if(!pedras[i].ativa) {
                pedrasCount--;
            }
            setLinhaColisaoPedra(&pedras[i]);
        }
        // -----------------------------------  //

        
    }

    if(boss->vida <= 0 && !(CheckCollisionRecs(end1, end2))) {
        end1.x+=5;
        end2.x-=5;
        
    }

    if((CheckCollisionRecs(end1, end2))) {
        if(contador % 240 == 0) {
            telaAtual = TELA_MENU;
            ShowCursor();
            save();
        }
    }
}

void movimentacaoBoss(Vector2 alvo) {
    if(alvo.x > boss.posicao.x) {
        setTextureCropped(&boss.sprite, "resources/images/golem-walk.png", (Rectangle){0,192,448,64});
        boss.posicao.x++;
    }

    if(alvo.x < boss.posicao.x) {
        setTextureCropped(&boss.sprite, "resources/images/golem-walk.png", (Rectangle){0,64,448,64});
        boss.posicao.x--;
    }

    if(alvo.y > boss.posicao.y) {
        boss.posicao.y++;
    }

    if(alvo.y  < boss.posicao.y) {
        boss.posicao.y--;
    }
}

Pedra pedraConstructor(Personagem *boss) {
    Pedra pedra;
    pedra.ativa = true;
    pedra.posicao = boss->posicao;
    pedra.velocidade.x = (float)GetRandomValue(-250, 250)/60.0f;
    pedra.velocidade.y = (float)GetRandomValue(-250, 250)/60.0f;
    pedra.altura = 32;
    pedra.largura = 32;
    pedra.color = WHITE;
    return pedra;
}

void setLinhaColisaoBoss(Personagem *boss) {
    boss->linhaColisaoCima =
        (Rectangle){
            boss->posicao.x,
            boss->posicao.y - 5,
            boss->largura + 5, 1};

    boss->linhaColisaoBaixo =
        (Rectangle){
            boss->posicao.x,
            boss->posicao.y + boss->altura,
            boss->largura + 5, 1};

    boss->linhaColisaoEsquerda =
        (Rectangle){
            boss->posicao.x,
            boss->posicao.y - 5,
            1, boss->altura + 5};

    boss->linhaColisaoDireita =
        (Rectangle){
            boss->posicao.x + boss->largura + 5,
            boss->posicao.y - 5,
            1, boss->altura + 5};

    return boss;
}

void setLinhaColisaoPedra(Pedra *pedra) {
    pedra->linhaColisaoCima =
        (Rectangle){
            pedra->posicao.x,
            pedra->posicao.y - 5,
            pedra->largura + 5, 1};

    pedra->linhaColisaoBaixo =
        (Rectangle){
            pedra->posicao.x,
            pedra->posicao.y + pedra->altura,
            pedra->largura + 5, 1};

    pedra->linhaColisaoEsquerda =
        (Rectangle){
            pedra->posicao.x,
            pedra->posicao.y - 5,
            1, pedra->altura + 5};

    pedra->linhaColisaoDireita =
        (Rectangle){
            pedra->posicao.x + pedra->largura + 5,
            pedra->posicao.y - 5,
            1, pedra->altura + 5};

    return pedra;
}
