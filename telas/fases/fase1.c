#include <math.h>
#include <raylib.h>

#include "../../lib/tela.h"
#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/acao.h"

void fase1();

void fase1()
{
    InitWindow(800,600,"JOGO"); //temporario
    
    Rectangle MAPA[] = {
        -278, -166, 18, 332,
        -264, -164, 481, 13,
        -261, 146, 466, 14,
        204, -156, 19, 256
    };
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
    
    while(!WindowShouldClose()){

        movimentar(&xala, MAPA);
        
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

        cam.offset.x = tela.width/2  -xala.position.x;
        cam.offset.y = tela.height/2 -xala.position.y;
        

        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode2D(cam);

                for(int i = 0; i < TAM_MAPA; i++){
                    DrawRectangleRec(MAPA[i],BLACK);
                }
                DrawCircleV(cam.target,10,RED);
                DrawCircleV(xala.position,10,BLUE);
                DrawCircleV(bala.origem,5,GREEN);
                DrawCircleV(cam.offset,5,PURPLE);
                DrawRectangleRec(xala.linhaColisaoCima,colideCima);
                DrawRectangleRec(xala.linhaColisaoBaixo,colideBaixo);
                DrawRectangleRec(xala.linhaColisaoEsquerda,colideEsq);
                DrawRectangleRec(xala.linhaColisaoDireita,colideDir);
                
                
            EndMode2D();

            DrawText(FormatText("target %.2f %.2f",cam.target.x, cam.target.y),10,10,20,YELLOW);
            DrawText(FormatText("vel %.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,40,20,YELLOW);
            DrawText(FormatText("angulo %.2f",bala.angulo),10,70,20,YELLOW);
            DrawText(FormatText("zoom %.2f",cam.zoom),10,100,20,YELLOW);
            DrawText(FormatText("tiro %i",bala.ativa),10,130,20,YELLOW);

        EndDrawing();
    }
    CloseWindow(); //temporario
}
