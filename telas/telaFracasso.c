

void telaFracasso();
void drawTelaFracasso();
void logicaTelaFracasso();


void telaFracasso() {
    while(telaAtual == TELA_FRACASSO) {
        drawTelaFracasso();
        logicaTelaFracasso();
    }
}

void drawTelaFracasso() {

    BeginDrawing();
            
        ClearBackground(GRAY);

        DrawText("YOU DIED", tela.width/2 - 400, tela.height/2 - 50, 100, YELLOW);

    EndDrawing();
}


void logicaTelaFracasso() {
    if(IsKeyDown(KEY_P)) {
        WindowShouldClose();
    }
}