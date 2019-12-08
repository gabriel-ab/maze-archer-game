#include <math.h>
#include <raylib.h>

#ifndef TELA_H_INCLUDED
    #include "../../lib/tela.h"
    #include "../../lib/personagem.h"
    #include "../../lib/movimenta.h"
    #include "../../lib/acao.h"
    #include "../../lib/draw.c"
#endif

#define TAM_MAPA_2 31 
#define TAM_PISO_2 13
void fase_cave1();

void fase_cave1()
{
    // InitWindow(800,600,"JOGO"); //temporario
    
    
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
    
    //TEXTURA DO CENARIO
    setTexture(&piso, "resources/images/chao_cav.png", 32, 32);
    setTexture(&parede, "resources/images/pedra.png", 32, 32);
    //----------------------------------------------------------//
    
    framerec = (rectangle){0,0, 32, 32};
    
    Tiro bala;

    Personagem xala;
    xala = personagemConstructor();
    xala.altura = 20;
    xala.largura = 20;

    Camera2D cam;
    cam.zoom = 1;
    cam.rotation = 0;
    cam.target = xala.position;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};

    SetTargetFPS(60);
    
    while(IsKeyUp(KEY_ESCAPE)){ 

        movimentar(&xala, PAREDE);
        
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            bala.ativa = 1;
            mira(xala,&bala,cam);
            atira(&bala);
        }
        
        atualizaTiro(&bala);

        if(bala.origem.x == 20*xala.position.x || bala.origem.y == 20*xala.position.y )
        {
            bala.origem = xala.position;
            bala.velocidade = (Vector2){0,0};
            bala.ativa = 0;
        }
        
        if(IsKeyPressed(KEY_F))
        {
            telaCheia();
            atualizaCamera(&cam);
        }
        if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;
        if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;
        
        cam.target = xala.position;

        cam.offset.x = tela.width/2  -cam.target.x;
        cam.offset.y = tela.height/2 -cam.target.y;
        

        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode2D(cam);
                
                drawParedes(PAREDE, TAM_MAPA_2);
                drawPiso(PISO, TAM_PISO_2, framerec);
                
                DrawCircleV(cam.target,10,RED);
                DrawCircle(0,0,10,RED);
                DrawCircleV(xala.position,10,BLUE);
                DrawCircleV(bala.origem,5,GREEN);
                DrawCircleV(cam.offset,5,PURPLE);
                DrawCircle(
                    (GetMouseX() -cam.offset.x),
                    (GetMouseY() -cam.offset.y),
                    5,PURPLE);

                //DrawRectangleRec(xala.linhaColisaoCima,colideCima);
                //DrawRectangleRec(xala.linhaColisaoBaixo,colideBaixo);
                //DrawRectangleRec(xala.linhaColisaoEsquerda,colideEsq);
                //DrawRectangleRec(xala.linhaColisaoDireita,colideDir);
                drawXala(xala, count);
                
            EndMode2D();

            DrawText(FormatText("target %.2f %.2f",cam.offset.x, cam.offset.y),10,10,20,YELLOW);
            DrawText(FormatText("vel %.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,40,20,YELLOW);
            DrawText(FormatText("angulo %.2f",bala.angulo),10,70,20,YELLOW);
            DrawText(FormatText("zoom %.2f",cam.zoom),10,100,20,YELLOW);
            DrawText(FormatText("tiro %i",bala.ativa),10,130,20,YELLOW);

        EndDrawing();
    }
    telaAtual = 0;
    // CloseWindow(); //temporario
}
