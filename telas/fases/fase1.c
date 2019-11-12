#include <raylib.h>
#include <math.h>

#include "../../lib/tela.h"
#include "../../lib/personagem.h"
#include "../../lib/movimenta.h"
#include "../../lib/shoot.h"

void fase1();

void main () {
    fase1();
}

void fase1()
{
    InitWindow(1280,720,"JOGO"); //temporario
    Rectangle MAPA[] = {
        -20,-20,1300, 10,
        0,720,1280, 10,
        -20,-20,10, 720,
        1280,0,10, 720,
    };

    Personagem xala;
    xala = personagemConstructor();
    xala.altura = 20;
    xala.largura = 20;

    Camera2D cam;
    cam.zoom = 3;
    cam.rotation = 0;
    cam.target = xala.position;
    cam.offset = (Vector2){GetScreenWidth()/2 , GetScreenHeight()/2};


    // *************** SHOOT******************
    Shoot shoot[PLAYER_MAX_SHOOTS] = { 0 };

    for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
    {
        shoot[i].position = (Vector2){0, 0};
        shoot[i].speed = (Vector2){0, 0};
        shoot[i].radius = 2;
        shoot[i].active = false;
        shoot[i].lifeSpawn = 0;
        shoot[i].color = WHITE;
    }

    float angle = 0;

    // *************** SHOOT******************
    
    while(!WindowShouldClose()){

        movimentar(&xala, MAPA, &angle);
        cam.target = xala.position;

        if (IsKeyPressed(KEY_SPACE))
        {
            for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
            {
                if (!shoot[i].active)
                {
                    shoot[i].position = (Vector2){ xala.position.x, xala.position.y};
                    shoot[i].active = true;
                    shoot[i].speed.x = sin(angle * DEG2RAD);
                    shoot[i].speed.y = cos(angle * DEG2RAD);
                    shoot[i].rotation = angle;
                    break;
                }
            }
        }

        // Shoot life timer
        for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
        {
            if (shoot[i].active) shoot[i].lifeSpawn++;
        }

        // Shot logic
        for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
        {
            if (shoot[i].active)
            {
                // Movement
                shoot[i].position.x += shoot[i].speed.x;
                shoot[i].position.y -= shoot[i].speed.y;

                // Collision logic: shoot vs walls
                if  (shoot[i].position.x > tela.width + shoot[i].radius)
                {
                    shoot[i].active = false;
                    shoot[i].lifeSpawn = 0;
                }
                else if (shoot[i].position.x < 0 - shoot[i].radius)
                {
                    shoot[i].active = false;
                    shoot[i].lifeSpawn = 0;
                }
                if (shoot[i].position.y > tela.height + shoot[i].radius)
                {
                    shoot[i].active = false;
                    shoot[i].lifeSpawn = 0;
                }
                else if (shoot[i].position.y < 0 - shoot[i].radius)
                {
                    shoot[i].active = false;
                    shoot[i].lifeSpawn = 0;
                }

                // Life of shoot
                if (shoot[i].lifeSpawn >= 360)
                {
                    shoot[i].position = (Vector2){0, 0};
                    shoot[i].speed = (Vector2){0, 0};
                    shoot[i].lifeSpawn = 0;
                    shoot[i].active = false;
                }
            }
        }

        BeginDrawing();
            ClearBackground(GRAY);

            BeginMode2D(cam);

                for(int i = 0; i < TAM_MAPA; i++){
                    DrawRectangleRec(MAPA[i],BLACK);
                }
                DrawCircleV(xala.position,10,BLUE);
                DrawRectangleRec(xala.linhaColisaoCima,colideCima);
                DrawRectangleRec(xala.linhaColisaoBaixo,colideBaixo);
                DrawRectangleRec(xala.linhaColisaoEsquerda,colideEsq);
                DrawRectangleRec(xala.linhaColisaoDireita,colideDir);

                // Draw shoot
                for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
                {
                    if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, BLACK);
                }
               

            EndMode2D();

            DrawText(FormatText("%.2f %.2f",cam.target.x, cam.target.y),10,10,20,YELLOW);
            DrawText(FormatText("%.2f %.2f",xala.velocidade.x, xala.velocidade.y),10,40,20,YELLOW);
            DrawText(FormatText("%lu",sizeof(MAPA)),10,70,20,YELLOW);

        EndDrawing();
    }
    CloseWindow(); //temporario
}
