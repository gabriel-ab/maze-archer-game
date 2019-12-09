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

int projetil_atual;
int dano;
int contador;

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
    xala.altura = 20;
    xala.largura = 20;
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


    dano = barraVidaBoss.width/boss.vida;


    // ----------------- TEXTURE CENÁRIO --------------- //
    setTexture(&portalTexture, "resources/images/portal.png",260, 160);
    setTextureCropped(&boss.sprite, "resources/images/golem-walk.png", (Rectangle){0,128,448,64});
    setTextureCropped(&flechasTexture, "resources/images/Flechas.png", (Rectangle){0,0,64,64});
    pisoTexture = LoadTexture("resources/images/chao_cav.png");
    paredeTexture = LoadTexture("resources/images/pedra.png");
    pedraTexture = LoadTexture("resources/images/pedra.png");
    //--------------------------------------------------//



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

    
    while(telaAtual == BOSS_FIGHT) {
        
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
                    boss->sprite, 
                    frameRecPersonagem, 
                    boss->posicao, 
                    WHITE);
            }
            
            drawFlecha(flechas, xala->quantidadeFlechas);

            drawXala(xala, count);

            // ------------------ PEDRAS ----------------- //
            if(boss->vida > 0) {
                
                for (int i = 0; i < pedrasCount; i++)
                {
                    DrawTexture(pedraTexture, pedras[i].posicao.x, pedras[i].posicao.y, pedras[i].color);
                }
            }
            // -------------------------------------------- //

            // "Mira" do mouse
            DrawCircle(
                (GetMouseX() -cam.offset.x),
                (GetMouseY() -cam.offset.y),
                5,PURPLE
            );
            
        EndMode2D();

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


        drawHUD(boss->vida, 0);

    EndDrawing();
}

//Função responsável pela lógica da Fase final
void logica_boss_fight(Personagem* xala, Personagem* boss, Projetil flecha[], Rectangle PAREDES[]) {
    
    HideCursor();
    contador++;

    if(IsKeyPressed(KEY_P)) {
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


    // -------------- COLISÃO XALA PEDRA ------------ //
    for (int i = 0; i < pedrasCount; i++)
    {
        bool estaColidindo = CheckCollisionPointRec(xala->posicao, pedras[i].linhaColisaoCima) ||
            CheckCollisionPointRec(xala->posicao, pedras[i].linhaColisaoBaixo) ||
            CheckCollisionPointRec(xala->posicao, pedras[i].linhaColisaoEsquerda) ||
            CheckCollisionPointRec(xala->posicao, pedras[i].linhaColisaoDireita);

        if(estaColidindo && pedras[i].ativa)  {
            xala->vida--;
            xala->invulneravel = !(xala->invulneravel);
            pedras[i].ativa = false;
            pedrasCount--;   
        }
    }
    // ------------------------------------------------ //



    // ------------ LÓGICA DA INVULNERABILIDADE -------------- //

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



    // ------------- LÓGICA: MIRA & DISPARO DA FLECHA ------------------- //
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
    // ------------------------------------------------------------------ //
    


    // ----------------- COLISÃO FLECHA E GOLEM --------------- //
    for(int i = 0; i < xala->quantidadeFlechas; i++)
    {   
        if(flecha[i].ativa)
        {
            aplicarInerciaV(&flecha[i].posicao, flecha[i].velocidade);
            aplicarAtritoProjetil(&flecha[i],0.5);
            colisaoProjetil_mapa(&flecha[i], PAREDES, 4);
            
            
            if(
                CheckCollisionCircleRec(flecha[i].posicao, 5, boss->linhaColisaoCima) ||
                CheckCollisionCircleRec(flecha[i].posicao, 5, boss->linhaColisaoBaixo) ||
                CheckCollisionCircleRec(flecha[i].posicao, 5, boss->linhaColisaoEsquerda) ||
                CheckCollisionCircleRec(flecha[i].posicao, 5, boss->linhaColisaoDireita)
            )
            {
                flecha[i].velocidade = boss->velocidade;
                boss[i].vida--;
                flecha[i].ativa = false;
                barraVidaBoss.width -= dano;
            }

            
        }
    }
    // ------------------------------------------------------------- //
    


    // ------------ LÓGICA DESATIVAR FLECHA ----------------- //
    if(flecha[projetil_atual].velocidade.x == 0 && flecha[projetil_atual].velocidade.y == 0 && flecha[projetil_atual].ativa)
    {
        flecha[projetil_atual].ativa = false;
    }
    // ------------------------------------------------------- //
    


    // RAFAEL PARTE DE PEGAR OBJETO (flechas)
    if(projetil_atual +1 < xala->quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario
    // ------------------------------------------------------ //



    // -------- LÓGICA DA ANIMAÇÃO: GOLEM ---------- //
    frameCount++;
    if (frameCount % 10 == 0)
    {
        currentFrame++;

        if (currentFrame > 7) currentFrame = 0;
        frameRecPersonagem.x = (float)currentFrame * (float)boss->sprite.width/7;
    }
    // --------------------------------------------- //



    if(boss->vida > 0) {
        
        // ----------- ATUALIZAÇÃO DO BOSS -------------//
        if(!CheckCollisionPointCircle(
            xala->posicao, 
            (Vector2) {
                boss->posicao.x + boss->sprite.height/2, 
                boss->posicao.y + boss->sprite.height/2,
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
