
#include <raylib.h>

void menuScreen(Texture2D *background, Rectangle botoes[], char *textButtons[]);
void logicaBotoesMenu(Rectangle botoes[], int *telaAtual, Sound somBotao, bool *jogo_rodando);

//TELA DE MENU
void menuScreen(Texture2D *background, Rectangle botoes[], char *textButtons[]) {

    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(*background, 0, 0, WHITE);

        
        for (int i = 0; i < 4; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtons[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtons[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }
        

    EndDrawing();
}

void logicaBotoesMenu(Rectangle botoes[], int *telaAtual, Sound somBotao, bool *jogo_rodando) {
    
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[0]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            *(telaAtual) = 1;
            
        }
    }
    
    //IR PARA TELA DE CONFIGURAÇÕES
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            *(telaAtual) = 2;
        }
    }

    //SAIR DO JOGO
    if (CheckCollisionPointRec(GetMousePosition(), botoes[3]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            PlaySound(somBotao);
            if(!IsSoundPlaying(somBotao)) {
                *(jogo_rodando) = false;
            }
            
        }
    }
   
}