#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/acao.h"
#endif
void fase1();

void fase1()
{
    // InitWindow(800,600,"JOGO"); //temporario
    
    Rectangle parede[] = {
        -192, -224, 448, 32,
        -192, -192, 32, 384,
        -160, 160, 416, 32,
        224, 32, 32, 128,
        224, -192, 32, 128,
        256, 32, 320, 32,
        256, -96, 320, 32,
        576, -224, 32, 160,
        576, 32, 288, 32,
        704, -352, 32, 288,
        576, -512, 32, 288,
        608, -512, 480, 32,
        704, -384, 480, 32,
        736, -96, 128, 32,
    };
    Rectangle piso[] = {
        -160, -192, 384, 352,
        608, -480, 96, 416,
        224, -64, 640, 96,
        704, -480, 480, 96
    };
    Projetil bala;

    Texture2D chao = LoadTexture("resources/images/teste_ceramica.png");
    Texture2D bloco = LoadTexture("resources/images/bosGround.png");

    Personagem xala;
    xala = personagemConstructor();
    xala.position = (Vector2){0,0};
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

        movimentar(&xala, parede);
        
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
            aplicarAtritoProjetil(&bala,1.5);
            colisaoProjetil(&bala,parede);
        }
        
        if(IsKeyPressed(KEY_F)) telaCheia();            //
        if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;    // Temporario
        if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;  //
        
        
        
        
        #ifdef __linux__
            cam.offset.x = tela.width/2 ;
            cam.offset.y = tela.height/2;
        #elif __WIN32   //possivel problema de versões do OpenGl 2.1 e 3.3
            cam.target = xala.position;
            cameraSegue(&cam,REC_SEGUE);
        #endif
        
        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode2D(cam);

                for(int i = 0; i < TAM_MAPA1; i++){
                    DrawRectangleRec(parede[i],BLACK);
                    
                    // Função para colocar textura em retangulos
                    /* 
                        sourceRec = retangulo no espaço vetorial da textura
                        destRec = retangulo onde o sourceRec vai ser colocado
                    */
                    DrawTexturePro(chao,
                        (Rectangle){0,0,piso[i].width,piso[i].height},
                        piso[i],
                        (Vector2){0,0},
                        0,WHITE
                    );
                }
                for(int i = 0; i < TAM_MAPA1; i++){
                    DrawTexturePro(bloco,
                        (Rectangle){0,0,parede[i].width,parede[i].height},
                        parede[i],
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
            DrawRectangleLinesEx(REC_SEGUE,1,WHITE);

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
