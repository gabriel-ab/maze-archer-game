#include <raylib.h>


void telaConfiguracao(Texture2D *background, Rectangle botoes[], char *textButtons[]);
void logicaBotoesConfiguracao(Rectangle botoes[], int *telaAtual);

//TELA DE CONFIGURAÇÃO
void telaConfiguracao(Texture2D *background, Rectangle botoes[], char *textButtons[]) {
    BeginDrawing();
            
        ClearBackground(RAYWHITE);

        DrawTexture(*background, 0, 0, WHITE);

        for (int i = 0; i < 3; i++)
        {
            DrawRectangleRec(botoes[i], CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){128,0,0, 255} : (Color){164,0,0, 255});
            DrawRectangleLines((int)botoes[i].x-5, (int) botoes[i].y-5, (int) botoes[i].width+10, (int) botoes[i].height+10, CheckCollisionPointRec(GetMousePosition(), botoes[i]) ? (Color){164,0,0, 255} : (Color){128,0,0, 255});
            DrawText( textButtons[i], (int)( botoes[i].x + botoes[i].width/2 - MeasureText(textButtons[i], 20)/2), (int) botoes[i].y + 16, 20, WHITE);
        }

    EndDrawing();
}

void logicaBotoesConfiguracao(Rectangle botoes[], int *telaAtual) {

    // IR PARA TELA DE RESOLUÇÃO
    if(CheckCollisionPointRec(GetMousePosition(), botoes[0])) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            *(telaAtual) = 3;
        }
    }

    //VOLTAR PARA O MENU
    if (CheckCollisionPointRec(GetMousePosition(), botoes[2]))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            *(telaAtual) = 0;
        }
    }
}
