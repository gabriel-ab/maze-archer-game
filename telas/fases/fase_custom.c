#include "../../inc/data.h"
#include "../../inc/projetil.h"
#include "../../inc/tela.h"
#include "../../inc/textura.h"

void fase_custom(){

    //-------------LOADING---------------//
    Mapa fase = LoadMapa(diretorio);
    for(int i = 0; i < fase.n_inimigos; i++)
    {
        fase.inimigo[i].sprite = spriteConstructor(inimigoTexture,32,32,10);
    }
    for (int i = 0; i < fase.n_vidas; i++){
        fase.vida[i].sprite = spriteConstructor(vidaTexture, 32, 32, 1);
        fase.vida[i].ativo = true;
    }
    for (int i = 0; i < fase.n_flechas; i++){
        fase.flecha[i].sprite = spriteConstructor(arrowTexture, 32, 32, 1);
        fase.flecha[i].ativo = true;
    }
    for (int i = 0; i < fase.n_bombas; i++)
    {
        fase.bomba[i].sprite = spriteConstructor(bombaTexture, 160, 160, 12);
        fase.bomba[i].damageFrame = 6;
        fase.bomba[i].status = TRAP_READY;
    }

    Personagem xala = personagemConstructor();
    xala.sprite = spriteConstructor(xalaTexture,48,48,15);
    xala.posicao = fase.inicio;
    
    //Flechas do jogo
    Projetil flecha[MAX_FLECHAS];
    xala.quantidadeFlechas = flechas_no_save;
    projetil_atual = xala.quantidadeFlechas -1;

    //TEXTURAS DA FASE
    pisoTexture = LoadTexture("resources/images/marmore.png");
    paredeTexture = LoadTexture("resources/images/pedra_brilhante.png");
    
    for (int i = 0; i < MAX_FLECHAS; i++){
        flecha[i].sprite = spriteConstructor(flechaTexture, 40, 7, 1);
        flecha[i].ativa = false;
    }

    setTargetCamera(&xala);
    Portal saida;
    saida.sprite = spriteConstructor(portalTexture,36,52,10);

    saida.posicao = (Vector2){0,0}; //temp
    //saida.posicao = fase.fim;

    saida.destino = TELA_MENU; 
    telaAtual = 5;
    
    while(telaAtual == 5 && !WindowShouldClose()){
        TEMPO = GetTime();

        if(isPaused) {
            telaPausa();
        } else {
            //==========================DRAWING============================//
            BeginDrawing();
                ClearBackground((Color){20,20,20,255});

                BeginMode2D(cam);

                    drawPiso(fase.piso, fase.n_pisos);
                    drawParedes(fase.parede, fase.n_paredes);
                    drawPortal(saida, 1.0f, WHITE);

                    for (int i = 0; i < fase.n_vidas; i++)
                    {
                        if(fase.vida[i].ativo)
                        {
                            drawSprite(fase.vida[i].sprite, fase.vida[i].posicao, (Vector2){0,0}, 0, 0.7, WHITE);
                            if (CheckCollisionCircles(xala.posicao, 16, fase.vida[i].posicao, 10))
                            {
                                xala.vida++;
                                fase.vida[i].ativo = false;
                            }
                        }
                    }
                    for (int i = 0; i < fase.n_flechas; i++)
                    {
                        if(fase.flecha[i].ativo)
                        {
                            drawSprite(fase.flecha[i].sprite, fase.flecha[i].posicao, (Vector2){0,0}, 0, 0.7, WHITE);
                            if (CheckCollisionCircles(xala.posicao, 16, fase.flecha[i].posicao, 10))
                            {
                                xala.quantidadeFlechas++;
                                projetil_atual++;
                                fase.flecha[i].ativo = false;
                            }
                        }
                    }
                    for (int i = 0 ; i < fase.n_bombas; i++)
                    {
                        drawSprite(fase.bomba[i].sprite, fase.bomba[i].posicao, (Vector2){0,0},0,1,WHITE);
                    }
                    drawInimigos(fase.inimigo, fase.n_inimigos);

                    drawXala(&xala);
                    drawFlecha(flecha, xala);
                    
                EndMode2D();
                
                DrawCircleV(GetMousePosition(),5,PURPLE);
                drawHUD(xala.vida, projetil_atual +1);
            EndDrawing();

            //==========================LOGIC============================//

            if(IsKeyPressed(KEY_ESCAPE)) isPaused = true;

            if(xala.vida < 1) {
                telaAnterior = telaAtual;
                telaAtual = TELA_FRACASSO;
            }

            // -------- ANIMAÇÂO DO PORTAL ------------
            animaSpriteLinha(&saida.sprite);
            if (CheckCollisionCircles(xala.posicao, 10, saida.posicao, 10)){
                telaAtual = saida.destino;
                save();
            }
            playMusic(2);

            // -----------Atualização da Camera----------
            atualizarCamera(&cam, xala.posicao);
            cam.zoom += (float)GetMouseWheelMove()/10.0f;
            verificarTamanhoTela();
            
            // ------------Logica do Projetil-------------- 
            checkClickBow();
            if(projetil_atual > -1)
            {
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    mira(xala,&flecha[projetil_atual],cam);
                    mirando = true;
                }
                else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    mirando = false;
                    flecha[projetil_atual].ativa = 1;
                    atira(xala,&flecha[projetil_atual]);
                    projetil_atual--;
                }
            }
            

            // ------------------Física------------------
            movimentar(&xala);
            colisaoPersonagem(&xala, fase.parede, fase.n_paredes);
            // --------------Fisica da Flecha------------
            for(int i = 0; i < xala.quantidadeFlechas; i++)
            {   
                if(flecha[i].ativa)
                {
                    aplicarInerciaV(&flecha[i].posicao, flecha[i].velocidade);
                    aplicarAtritoProjetil(&flecha[i],0.5);
                    colisaoProjetil_mapa(&flecha[i], fase.parede, fase.n_paredes);
                    colisaoProjetil_inimigo(&flecha[i], fase.inimigo, fase.n_inimigos);
                }
            }
            
            if(flecha[projetil_atual].ativa && flecha[projetil_atual].velocidade.x == 0 && flecha[projetil_atual].velocidade.y == 0)
            {
                flecha[projetil_atual].ativa = false;
            }
            
            // ----------Recuperação da flecha-------------
            if(projetil_atual +1 < xala.quantidadeFlechas && IsKeyPressed(KEY_SPACE)) projetil_atual++; // era temporario

            //----------Atualização dos sprites------------
            if(IsKeyDown(KEY_A)) {
                xala.sprite.n_segmento = 0;
                animaSprite(&xala.sprite, segmentos_xala);
            }
            if(IsKeyDown(KEY_D)) {
                xala.sprite.n_segmento = 1;
                animaSprite(&xala.sprite, segmentos_xala);
            }
            if(IsKeyDown(KEY_W) || IsKeyDown(KEY_S)){
                animaSprite(&xala.sprite, segmentos_xala);
            }

            //----------Atualização dos inimigos-----------
            for (int i = 0; i < fase.n_inimigos; i++)
            {
                if(fase.inimigo[i].vida > 0) {
                    animaSpriteLinha(&fase.inimigo[i].sprite);
                    logicaInimigo(&fase.inimigo[i], &xala);
                    colisaoPersonagem(&fase.inimigo[i], fase.parede , fase.n_paredes);
                    atualizarPersonagem(&fase.inimigo[i]);
                }
            }

            //----------------Trap Logic-------------------
            for (int i = 0; i < fase.n_bombas; i++)
            {
                if( 
                    CheckCollisionCircles(flecha[projetil_atual +1].posicao,10, fase.bomba[i].posicao, 10) && 
                    flecha[projetil_atual +1].ativa && 
                    fase.bomba[i].status == TRAP_READY
                ) {
                    fase.bomba[i].status = TRAP_ON;
                    flecha[projetil_atual +1].velocidade = (Vector2){0,0};
                }

                if (fase.bomba[i].sprite.frameAtual == fase.bomba[i].damageFrame) //frame de Dano será pulado, 
                {
                    explosionCollision(fase.bomba[i], &xala);
                    for (int j = 0; j < fase.n_inimigos; j++)
                    {
                        explosionCollision(fase.bomba[i], &fase.inimigo[j]);
                    }
                    fase.bomba[i].sprite.frameAtual++;
                }
                animarBomba(&fase.bomba[i]);
            }
            //--------------INVUNERABILIDADE---------------
            if(xala.invulneravel)
            {
                if(TEMPO -xala.tempoInvulneravel > 2)
                {
                    xala.invulneravel = 0;
                }
            }
        }
        if(isRestarting) 
        {
            isRestarting = false;
            break;
        }
    }
}