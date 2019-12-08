#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/projetil.h"
    #include "../../lib/som.h"
#endif
void fase1();

void fase1()
{
        Rectangle parede[] = {
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
    int n_paredes = sizeof(parede)/sizeof(Rectangle);

    Rectangle piso[] = {
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
    int n_pisos = sizeof(piso)/sizeof(Rectangle);
    
    

    Projetil bala[N_MAX_PROJETEIS];

    //NUMERO ATUAL DE FLECHAS
    int n_projeteis = 4;

    //indice da flecha
    int projetil_atual = n_projeteis -1;

    //Limpando atributos
    for(int i = 0; i < N_MAX_PROJETEIS; i++){
        bala[i].ativa = 0;
    }

    Texture2D pisoTexture = LoadTexture("resources/images/chao_cav.png");
    Texture2D paredeTexture = LoadTexture("resources/images/pedra.png");

    Image temp = LoadImage("resources/images/flechas.png");
    ImageCrop(&temp,(Rectangle){0,0,64,64});

    for( int i = 0; i < N_MAX_PROJETEIS; i++) {
        bala[i].textura = LoadTextureFromImage(temp);
    }
    UnloadImage(temp);

    Personagem xala;
    xala = personagemConstructor();
    xala.posicao = (Vector2){0,0};
    xala.altura = 20;
    xala.largura = 20;

    Personagem inimigo[10];
    int n_inimigos = sizeof(inimigo)/sizeof(Personagem);

    for(int i = 0; i < n_inimigos; i++)
    {
        inimigo[i] = inimigoContructor();
        inimigo[i].posicao = (Vector2){GetRandomValue(-200,200), GetRandomValue(-200,200)};
    }

    Camera2D cam;
    cam.zoom = 1;
    cam.rotation = 0;
    cam.target = xala.posicao;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};

    SetTargetFPS(60);
    double contadorInvulneravel =0;
    
    while(IsKeyUp(KEY_ESCAPE)){ 
       
        playMusic(2);
       
        movimentar(&xala);
        colisaoPersonagem(&xala, parede, n_paredes);
        //------------Logica do Projetil--------------

        /*if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && projetil_atual > -1){
            playFx(4);
        }
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && projetil_atual > -1){
            StopSound(arco);
            playFx(3);
        }*/
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
        
        for(int i = 0; i < n_projeteis; i++)
        {   
            if(bala[i].ativa)
            {
                aplicarInerciaV(&bala[i].posicao, bala[i].velocidade);
                aplicarAtritoProjetil(&bala[i],0.5);
                colisaoProjetil_mapa(&bala[i], parede, n_paredes);
                colisaoProjetil_inimigo(&bala[i], inimigo, n_inimigos);
            }
        }
        
        if(bala[projetil_atual].velocidade.x == 0 && bala[projetil_atual].velocidade.y == 0 && bala[projetil_atual].ativa)
        {
            bala[projetil_atual].ativa = 0;
        }
        
        // RAFAEL PARTE DE PEGAR OBJETO (flechas)
        if(projetil_atual +1 < n_projeteis && IsKeyPressed(KEY_SPACE)) projetil_atual++; //temporario

        //---------------------------------------------
        
        if(IsKeyPressed(KEY_F)) telaCheia();            //
        if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;    // Temporario
        if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;  //
        
        //-----------Atualização da Camera-------------
        atualizarCamera(&cam, xala.posicao);

        verificarTamanhoTela();

        //----------Atualização dos inimigos-----------
        for( int i = 0; i < n_inimigos; i++)
        {
            logicaInimigo(&inimigo[i],&xala);

            colisaoPersonagem(&inimigo[i], parede, n_paredes);
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

                for(int i = 0; i < n_pisos; i++)
                {
                    DrawTexturePro(pisoTexture,
                        (Rectangle){0,0,piso[i].width,piso[i].height},
                        piso[i],
                        (Vector2){0,0},
                        0,WHITE
                    );
                }
                for(int i = 0; i < n_paredes; i++)
                {
                    DrawTexturePro(paredeTexture,
                        (Rectangle){0,0,parede[i].width,parede[i].height},
                        parede[i],
                        (Vector2){0,0},
                        0,WHITE
                    );
                }
                for(int i = 0; i < n_inimigos; i++)
                {
                    DrawCircleV(inimigo[i].posicao, 10, (Color){150,150,255,120});
                }

                DrawCircle(0,0,2,WHITE);
                DrawCircleV(xala.posicao,10,BLUE);
                for (int i = 0; i < n_projeteis; i++)
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
            DrawText(FormatText("VIDA: %i",xala.vida),10,160,20,YELLOW);
            DrawText(FormatText("invuneravel: %i",xala.invulneravel),10,200,20,YELLOW);
            DrawText(FormatText("contador: %i",inimigo[0].acao.contador),10,240,20,YELLOW);
            
            // DrawText(FormatText("nparedes %i",n_pisos),10,350,20,YELLOW);
        EndDrawing();
    }
    telaAtual = 0;
}
