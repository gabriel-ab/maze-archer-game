    #include "../../lib/som.h"
#include "../../lib/tela.h"
#include "../../lib/define.h"
#include "../../lib/data.h"
#include <string.h>


#define N_BOXES_ON_SCREEN (int)(tela.width / (BOX_SIZE.x))

// OBS: O botão é centralizado por padrão.
// Os pontos (x,y) definem o centro do botão
void drawButton(Rectangle botao, const char *texto, bool selecionado){
    DrawRectangleRec(
        (Rectangle){
            botao.x -botao.width/2,
            botao.y -botao.height/2,
            botao.width ,
            botao.height
        },
        selecionado ? (Color){50,0,0, 255} : (Color){100,0,0, 255}
    ); //Desenha o box
    DrawRectangleLinesEx(
        (Rectangle){
            botao.x -botao.width/2 -5,
            botao.y -botao.height/2 -5,
            botao.width +10,
            botao.height +10
        },
        1,
        selecionado ? LIGHTGRAY : (Color){128,0,0, 255});
    
    DrawText(
        texto,
        botao.x -MeasureText(texto, 20)/2,
        botao.y -botao.height/4,
        20,
        YELLOW
    );
    
}

void selecao_de_mapa(){
    int n_fases = 0, seletor = 2;

    #ifdef _WIN32
        char **arquivos = GetDirectoryFiles("resources\\fases\\", &n_fases); //array de strings
    #elif __linux__
        char **arquivos = GetDirectoryFiles("resources/fases/", &n_fases); //array de strings
    #endif
    bool confirma = false;

    Camera2D rolador = { 0 };
    rolador.zoom = 1;
    Vector2 mousePos = GetMousePosition();
    bool rolagem_automatica = true;

    while (!confirma && !WindowShouldClose())
    {
        if (mousePos.x != GetMousePosition().x) rolagem_automatica = false;

        #ifdef _WIN32
            if (rolagem_automatica){
                rolador.offset.y = rolador.offset.y*0.8 -seletor*12 +tela.height*0.05;
            }
            else if (CheckCollisionPointCircle(mousePos,(Vector2){100,-50},200)){
                rolador.offset.y += 5;
            }
            else if (CheckCollisionPointCircle(mousePos,(Vector2){100,tela.height+50},200)){
                rolador.offset.y -= 5;
            }
        #elif __linux__
            if (rolagem_automatica){
                rolador.target.y = rolador.target.y*0.8 +seletor*12 -tela.height*0.05;
            }
            else if (CheckCollisionPointCircle(mousePos,(Vector2){100,-50},200)){
                rolador.target.y -= 5;
            }
            else if (CheckCollisionPointCircle(mousePos,(Vector2){100,tela.height+50},200)){
                rolador.target.y += 5;
            }
        #endif
        else{
            static int fps = 0;
            fps++;
            if(fps > 300) //espera 5 segundos
            {
                rolagem_automatica = true;
                fps = 0;
            }
        }
        
        mousePos = GetMousePosition();
        BeginDrawing();
            ClearBackground(BLACK);
            drawMenuBackground(WHITE);
            DrawRectangleGradientV(0,0,tela.width, tela.height, (Color){150,150,150,100}, (Color){0,0,0,100});

                BeginMode2D(rolador);
                for (int i = 2; i < n_fases; i++)
                {
                    drawButton((Rectangle){tela.width/6, 240+ (i-2)*60, 240, 30}, arquivos[i], seletor == i);
                    if (CheckCollisionPointRec((Vector2){mousePos.x, mousePos.y +rolador.target.y} ,(Rectangle){tela.width/6, 240+ (i-2)*60, 240, 30}))
                    {
                        seletor = i;
                        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) confirma = true;
                    }
                }
                EndMode2D();
        EndDrawing();
        
        verificarTamanhoTela();
        playMusic(1);

        if(IsKeyPressed(KEY_UP) && seletor > 2)    seletor--;
        if(IsKeyPressed(KEY_DOWN) && seletor +1 < n_fases)  seletor++;

        #ifdef _WIN32
            rolador.offset.y += GetMouseWheelMove() * 5;
        #elif __linux__
            rolador.target.y -= GetMouseWheelMove() * 5;
        #endif

        if(IsKeyPressed(KEY_ESCAPE)){
            telaAtual = TELA_MENU;
            break;
        }
        if(IsKeyPressed(KEY_ENTER)) confirma = true;
    }
    if(confirma){
        //Carrega a fase do endereço selecionado
        strcpy(diretorio, "resources/fases/");
        strcat(diretorio, arquivos[seletor]);
        telaAtual = TELA_FASE_CUSTOM;
    }
    
}