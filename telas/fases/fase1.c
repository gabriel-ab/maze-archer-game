#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/projetil.h"
#endif
void fase1();

void fase1()
{
    // InitWindow(800,600,"JOGO"); //temporario
    
    Rectangle MAPA[] = {
        -256, -256, 256, 32,
        -256, -224, 32, 256,
        -256, 32, 256, 32,
        -96, -96, 96, 32,
        0, -160, 32, 96,
        32, -96, 32, 96,
        64, -96, 96, 32,
        96, -256, 32, 160,
        -32, 64, 96, 32,
        64, 64, 256, 32,
        288, -96, 32, 160,
        128, -192, 256, 32,
        448, -288, 32, 256,
        384, 32, 160, 32,
    };
    Projetil bala;

    // Texture2D grama = LoadTexture("resources/images/grama.png");
    Texture2D piso = LoadTexture("resources/images/ciano.png");

    Personagem xala;
    xala = personagemConstructor();
    xala.position = (Vector2){-175,-161};
    xala.altura = 20;
    xala.largura = 20;

    Camera2D cam;
    cam.zoom = 1;
    cam.rotation = 0;
    cam.target = xala.position;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};
    int largura = 32, altura = 32;

    SetTargetFPS(60);
    
    while(IsKeyUp(KEY_ESCAPE)){ 

        movimentar(&xala, MAPA);
        
        //------------Logica do Projetil--------------
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            bala.ativa = 1;
            mira(xala,&bala,cam);
            atira(xala,&bala);
        }
        if(bala.velocidade.x == 0 && bala.velocidade.y == 0){
            bala.ativa = 0;
        }
        else{
            atualizaProjetil(&bala);
            aplicarAtritoProjetil(&bala,0.4);
            colisaoProjetil(&bala,MAPA);
        }
        
        if(IsKeyPressed(KEY_F)) telaCheia();            //
        if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;    // Temporario
        if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;  //
        
        cam.target = xala.position;
        cameraSegue(&cam,REC_SEGUE);
        /*
        #ifdef __linux__
            cam.offset.x = tela.width/2 ;
            cam.offset.y = tela.height/2;
        #elif __WIN32
            cam.offset.x = tela.width/2  -cam.target.x;
            cam.offset.y = tela.height/2 -cam.target.y;
        #endif
        */
        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode2D(cam);

                for(int i = 0; i < TAM_MAPA1; i++){
                    DrawRectangleRec(MAPA[i],BLACK);
                    
                    // Função para colocar textura em retangulos
                    /* 
                        sourceRec = retangulo no espaço vetorial da textura
                        destRec = retangulo onde o sourceRec vai ser colocado
                    */
                    DrawTexturePro(piso,
                        (Rectangle){0,0,MAPA[i].width,MAPA[i].height},
                        MAPA[i],
                        (Vector2){0,0},
                        0,WHITE
                    );
                    
                }
                DrawCircleV(cam.offset,10,YELLOW);
                DrawCircleV(cam.target,10,RED);
                DrawCircle(0,0,10,RED);
                DrawCircleV(xala.position,10,BLUE);
                DrawCircleV(bala.posicao,5,GREEN);
                DrawCircle(
                    (GetMouseX() -cam.offset.x),
                    (GetMouseY() -cam.offset.y),
                    5,PURPLE);

                DrawRectangleRec(xala.linhaColisaoCima,colideCima);
                DrawRectangleRec(xala.linhaColisaoBaixo,colideBaixo);
                DrawRectangleRec(xala.linhaColisaoEsquerda,colideEsq);
                DrawRectangleRec(xala.linhaColisaoDireita,colideDir);
                
                
            EndMode2D();

            DrawText(FormatText("xala.position %.2f %.2f",xala.position.x, xala.position.y),10,150,20,YELLOW);
            DrawText(FormatText("target %.2f %.2f",cam.target.x, cam.target.y),10,200,20,YELLOW);
            DrawText(FormatText("offset %.2f %.2f",cam.offset.x, cam.offset.y),10,10,20,YELLOW);
            DrawText(FormatText("vel %.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,40,20,YELLOW);
            DrawText(FormatText("angulo %.2f",bala.angulo),10,70,20,YELLOW);
            DrawText(FormatText("zoom %.2f",cam.zoom),10,100,20,YELLOW);
            DrawText(FormatText("Projetil %i",bala.ativa),10,130,20,YELLOW);

        EndDrawing();
    }
    telaAtual = 0;
    // CloseWindow(); //temporario
}
