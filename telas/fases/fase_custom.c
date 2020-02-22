void fase_custom(){

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
    Personagem xala = personagemConstructor();
    xala.sprite = spriteConstructor(xalaTexture,48,48,15);
    xala.posicao = fase.inicio;
    
    //Flechas do jogo // Será global
    Projetil flecha[MAX_FLECHAS];
    xala.quantidadeFlechas = flechas_no_save;
    projetil_atual = xala.quantidadeFlechas -1;


    //TEXTURAS DA FASE
    pisoTexture = LoadTexture("resources/images/marmore.png");
    paredeTexture = LoadTexture("resources/images/pedra_brilhante.png");
    
    for (int i = 0; i < MAX_FLECHAS; i++){
        flecha[i].textura = flechasTexture;
        flecha[i].ativa = false;
    }
    setTargetCamera(&xala);
    

    int currentFrame = 0;
    int frameCount = 0;
    portalTexture =  LoadTexture("resources/images/portal.png");
    Rectangle portalCollision = (Rectangle) {fase.fim.x, fase.fim.y, 32, 64 };
    Rectangle frameRecPortal = (Rectangle) {0 ,0 , portalTexture.width/4, portalTexture.height};
    telaAtual = 5;
    
    
    while(telaAtual == 5 && !WindowShouldClose()){
        TEMPO = GetTime();

        if(isPaused) {
            telaPausa();
        } else {

            BeginDrawing();
                ClearBackground((Color){20,20,20,255});

                BeginMode2D(cam);

                    drawPiso(fase.piso, fase.n_pisos);
                    drawParedes(fase.parede, fase.n_paredes);
                    DrawTextureRec(portalTexture, frameRecPortal, (Vector2){-400, 1500}, WHITE);
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
                    drawInimigos(fase.inimigo, fase.n_inimigos);

                    DrawCircle(0,0,2,WHITE);
                    drawXala(&xala);
                    drawFlecha(flecha, xala);
                    
                EndMode2D();
                
                DrawCircleV(GetMousePosition(),5,PURPLE);
                drawHUD(xala.vida, projetil_atual +1);
            EndDrawing();

            if(IsKeyPressed(KEY_ESCAPE)) isPaused = true;

            if(xala.vida < 1) {
                telaAnterior = telaAtual;
                telaAtual = TELA_FRACASSO;
            }

            if(CheckCollisionPointRec(xala.posicao, portalCollision)) {
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
            
            if(flecha[projetil_atual].velocidade.x == 0 && flecha[projetil_atual].velocidade.y == 0 && flecha[projetil_atual].ativa)
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
            for (int i = 0; i < fase.n_inimigos; i++) animaSpriteLinha(&fase.inimigo[i].sprite);

            //----------Atualização dos inimigos-----------
            for( int i = 0; i < fase.n_inimigos; i++)
            {
                if(fase.inimigo[i].vida > 0) {
                    logicaInimigo(&fase.inimigo[i], &xala);
                    colisaoPersonagem(&fase.inimigo[i], fase.parede , fase.n_paredes);
                    atualizarPersonagem(&fase.inimigo[i]);
                }
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