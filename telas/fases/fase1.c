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
    // InitWindow(800,600,"JOGO"); //temporario
    
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
    Projetil bala;

    Texture2D chao = LoadTexture("resources/images/chao_cav.png");
    Texture2D bloco = LoadTexture("resources/images/pedra.png");
    Image temp = LoadImage("resources/images/flechas.png");
    ImageCrop(&temp,(Rectangle){0,0,64,64});
    bala.textura = LoadTextureFromImage(temp);

    UnloadImage(temp);

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
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            playFx(4);
        }
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            StopSound(arco);
            playFx(3);
        }
        if(bala.velocidade.x == 0 && bala.velocidade.y == 0){
            bala.ativa = 0;
            
        }
        if(bala.ativa){
            atualizaProjetil(&bala);
            aplicarAtritoProjetil(&bala,1.5);
            colisaoProjetil(&bala,parede);
        }
        //---------------------------------------------
        
        if(IsKeyPressed(KEY_F)) telaCheia();            //
        if(IsKeyDown(KEY_PAGE_UP)) cam.zoom += 0.01;    // Temporario
        if(IsKeyDown(KEY_PAGE_DOWN)) cam.zoom -= 0.01;  //
        
        //-----------Atualização da Camera-------------
        cameraSegueFocoRec(&cam, xala.position, REC_TELA_1_POR_3);
        
        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode2D(cam);

                for(int i = 0; i < sizeof(piso)/sizeof(Rectangle); i++){
                    // DrawRectangleRec(parede[i],BLACK);
                    
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
                for(int i = 0; i < sizeof(parede)/sizeof(Rectangle); i++){
                    DrawTexturePro(bloco,
                        (Rectangle){0,0,parede[i].width,parede[i].height},
                        parede[i],
                        (Vector2){0,0},
                        0,WHITE
                    );

                    
                }
                DrawCircleV(cam.offset,10,YELLOW);
                DrawCircle(0,0,2,WHITE);
                DrawCircleV(xala.position,10,BLUE);
                DrawCircleV(bala.posicao,5,GREEN);

                DrawTexturePro(bala.textura,
                (Rectangle){0,28,64,8},
                (Rectangle){
                    bala.posicao.x,
                    bala.posicao.y,
                    64, 6},
                (Vector2){48,2},
                bala.angulo,WHITE);

                DrawCircle(
                    (GetMouseX() -cam.offset.x),
                    (GetMouseY() -cam.offset.y),
                    5,PURPLE);

                DrawRectangleRec(xala.linhaColisaoCima,colideCima);
                DrawRectangleRec(xala.linhaColisaoBaixo,colideBaixo);
                DrawRectangleRec(xala.linhaColisaoEsquerda,colideEsq);
                DrawRectangleRec(xala.linhaColisaoDireita,colideDir);
                
                
            EndMode2D();
            DrawRectangleLinesEx(REC_TELA_1_POR_3,1,WHITE);

            DrawText(FormatText("xala.position %.2f %.2f",xala.position.x, xala.position.y),10,150,20,YELLOW);
            DrawText(FormatText("target %.2f %.2f",cam.target.x, cam.target.y),10,200,20,YELLOW);
            DrawText(FormatText("offset %.2f %.2f",cam.offset.x, cam.offset.y),10,10,20,YELLOW);
            DrawText(FormatText("vel %.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,40,20,YELLOW);
            DrawText(FormatText("angulo %.2f",bala.angulo),10,70,20,YELLOW);
            DrawText(FormatText("zoom %.2f",cam.zoom),10,100,20,YELLOW);
            DrawText(FormatText("Projetil %i",bala.ativa),10,130,20,YELLOW);
            
            DrawText(FormatText("cos(angulo)*textura %f",cos(bala.angulo*DEG2RAD)*bala.textura.width/2),10,300,20,YELLOW);
            DrawText(FormatText("sin(angulo)*textura %f",sin(bala.angulo*DEG2RAD)*bala.textura.height/2),10,320,20,YELLOW);

        EndDrawing();
    }
    telaAtual = 0;
    // CloseWindow(); //temporario
}
