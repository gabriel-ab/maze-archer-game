#include "../include/draw.h"


//Função responsável por desenhar a personagem principal
void drawXala(Personagem* xala) {
    static double contador = 0;
    //Se Xala está invunerável ela começa a piscar
    if(xala->invulneravel) {
        if(TEMPO -contador > 0.10){
            contador = TEMPO;
        }else{
            drawSprite(xala->sprite,xala->posicao, (Vector2){0,16},0,1,RED);
        }
    } else {
        drawSprite(xala->sprite,xala->posicao, (Vector2){0,16},0,1,WHITE);
    }
}



//Função responsável por desenhar a personagem principal
void drawFlecha(Projetil flecha[], Personagem fulano) {
    for (int i = 0; i < fulano.quantidadeFlechas; i++)
    {
        if(i >= projetil_atual){
            if(i != projetil_atual || mirando ){
                DrawTexturePro(flecha[i].sprite.textura,
                    flecha[i].sprite.recorte,
                    (Rectangle){
                        flecha[i].posicao.x,
                        flecha[i].posicao.y,
                        flecha[i].sprite.recorte.width,
                        flecha[i].sprite.recorte.height},
                    (Vector2){38, 3.5},
                    flecha[i].angulo,
                    WHITE);
            }
        }
    }
}



//Função responsável por desenhar os inimigos da Fase
void drawInimigos(Personagem inimigos[], int quantidade) {
    for(int i = 0; i < quantidade; i++){
        
        if(inimigos[i].vida > 0) {
            drawSprite(inimigos[i].sprite, inimigos[i].posicao, (Vector2){0,0}, 0, 1, WHITE);
            // DrawCircleV(inimigos[i].posicao, 10, (Color){150,150,255,255});
        }
        
    }
}



//Função responsável por desenhar as paredes da Fase
void drawParedes(Rectangle PAREDES[], int tamanho) {
    for(int i = 0; i < tamanho; i++){
                
        DrawTexturePro(paredeTexture,
            (Rectangle){0,0,PAREDES[i].width,PAREDES[i].height},
            PAREDES[i],
            (Vector2){0,0},
            0,WHITE
        );
        
    }
}



//Função responsável por desenhar os pisos da Fase
void drawPiso(Rectangle PISO[], int tamanho) {     
    for(int i = 0; i < tamanho; i++){

        DrawTexturePro(pisoTexture,
            (Rectangle){0,0,PISO[i].width,PISO[i].height},
            PISO[i],
            (Vector2){0,0},
            0,WHITE
        );
         
    }
}



//Função responsável por desenhar as armadilhas da Fase
void drawArmadilhas(Rectangle ARMADILHAS[], int tamanho) {
    for(int i = 0; i < tamanho; i++){

        for (int x = 0; x < ARMADILHAS[i].width; x+=32)
        {
            for (int y = 0; y < ARMADILHAS[i].height; y+=32)
            {
                DrawTextureEx(armadilhaTexture, (Vector2) { ARMADILHAS[i].x + x , ARMADILHAS[i].y + y }, 0, 1,WHITE);
            }
               
        }
         
    }
}



//Função responsável por desenhar as armadilhas da Fase com animação
void drawArmadilhasRec(Rectangle ARMADILHAS[], int tamanho, Rectangle frameRec) {
    for(int i = 0; i < tamanho; i++){

        for (int x = 0; x < ARMADILHAS[i].width; x+=32)
        {
            for (int y = 0; y < ARMADILHAS[i].height; y+=32)
            {
                DrawTextureRec(armadilhaTexture, frameRec, (Vector2) { ARMADILHAS[i].x + x , ARMADILHAS[i].y + y }, WHITE);
            }
               
        }
         
    }
}

void drawSprite(Sprite sprite, Vector2 posicao, Vector2 origem, float rotacao, float escala, Color cor){
    DrawTexturePro(
        sprite.textura, 
        sprite.recorte,
        (Rectangle){
            posicao.x -(sprite.recorte.width * escala) /2, 
            posicao.y -(sprite.recorte.height * escala) /2, 
            escala*sprite.recorte.width, 
            escala*sprite.recorte.height
        },
        origem,
        rotacao,
        cor
    );
}
void drawMenuBackground(Color cor)
{
    DrawTexturePro(
            background,
            (Rectangle){0,0,background.width, background.height},
            (Rectangle){
                0,
                0,
                tela.width,
                tela.height},
            (Vector2){0,0},
            0,
            WHITE
        );
}
//-------------- HUD ---------------//

void drawHUD(int quantidadeVida, int quantidadeArrow){
    for (int i = 0; i < quantidadeVida; i++)
    {
        DrawTextureEx(vidaTexture, (Vector2){10+35*i, 10}, 0, 1.6, WHITE);
    }

    for (int i = 0; i < quantidadeArrow; i++)
    {
        DrawTextureEx(arrowTexture, (Vector2){10+35*i, 50}, 0, 1.6, WHITE);
    }
}

void drawPortal(Portal port, float size, Color color) {
    drawSprite(port.sprite, port.posicao, (Vector2){0,0}, 0, size, color);
}

// Predefined button;
void drawButtonD(const char *text, Rectangle button, bool selected){
    
    DrawRectangleRec(button, selected ? (Color){192, 24, 24, 255} : (Color){128,0,0, 255});

    DrawRectangleLines(
        (int) button.x-5,
        (int) button.y-5,
        (int) button.width+10,
        (int) button.height+10,
        selected ? (Color){64,0,0, 255} : (Color){192,0,0, 255});
    DrawText(
        text, 
        (int) (button.x + button.width/2 - MeasureText(text, 20)/2), 
        (int) button.y + button.height/2 - 10,
        20, 
        WHITE);
}

// OBS: O botão é centralizado por padrão.
// Os pontos (x,y) definem o centro do botão
void drawButtonEx(const char *texto, Rectangle botao, Color cor){
    DrawRectangleRec(
        (Rectangle){
            botao.x -botao.width/2,
            botao.y -botao.height/2,
            botao.width ,
            botao.height
        },
        cor
    ); //Desenha o box
    DrawRectangleLinesEx(
        (Rectangle){
            botao.x -botao.width/2 -5,
            botao.y -botao.height/2 -5,
            botao.width +10,
            botao.height +10
        },
        1,
        Fade(cor, 0.5));
    
    DrawText(
        texto,
        botao.x -MeasureText(texto, 20)/2,
        botao.y -botao.height/4,
        20,
        YELLOW
    );
}