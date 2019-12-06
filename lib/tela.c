#include <raylib.h>
#include "tela.h"
#include "define.h"

void telaCheia()
{
    if(!is_fullscreen){
        larguraAnterior = GetScreenWidth();
        alturaAnterior = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    }
    ToggleFullscreen();

    if(is_fullscreen){
        SetWindowSize(larguraAnterior, alturaAnterior);
        SetWindowPosition(tela.x, tela.y);
    }
    is_fullscreen = !is_fullscreen; 
    
    tela.width = GetScreenWidth();
    tela.height = GetScreenHeight();
}

void atualizarCamera(Camera2D *cam, Vector2 posicao)
{
    cam->target.x = 0.9*cam->target.x + 0.1*posicao.x;
    cam->target.y = 0.9*cam->target.y + 0.1*posicao.y;

    #ifdef __WIN32
        cam->offset.x = tela.width/2  -cam->target.x;
        cam->offset.y = tela.height/2 -cam->target.y;
    #endif
}

void verificarTamanhoTela(){
    if(IsWindowResized())
    {
        tela.width = GetScreenWidth();
        tela.height = GetScreenHeight();   

        if(telaAtual == TELA_CONFIG || telaAtual == TELA_MENU){
            updateBackground();
        }
    }
}

//-------------- BACKGROUND ---------------//
void setImageBackground(char* imagePath) {
    pathImageBackground = imagePath;
}

void updateBackground() {
    Image backgroundImage = LoadImage(pathImageBackground);
    ImageResize(&backgroundImage, tela.width, tela.height);  
    background = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
}


//-------------- HUD ---------------//

void drawHUD(int quantidadeVida, int quantidadeArrow){
    for (int i = 0; i < quantidadeVida; i++)
    {
        DrawTexture(vida, 10+35*i, 10, GRAY);
    }

    for (int i = 0; i < quantidadeArrow; i++)
    {
        DrawTexture(arrow, 10+35*i, 50, GRAY);
    }
}

//-------------- TEXTURE ---------------//

void setTexture(Texture* texture, char* spritePath, int largura, int altura) {
    Image imagem =  LoadImage(spritePath);
    ImageResize(&imagem, largura , altura);
    *texture = LoadTextureFromImage(imagem);
    UnloadImage(imagem);
}

void setTextureCropped(Texture* texture, char* spritePath, Rectangle crop) {
    Image imagem = LoadImage(spritePath);
    ImageCrop(&imagem, crop);
    *texture = LoadTextureFromImage(imagem);
    UnloadImage(imagem);
}

//-------------- FONT ---------------//

void setFont(char* fontPath) {
    font = LoadFont(fontPath);
}


// ------------- CÂMERA ----------- //
void setTargetCamera(Personagem *target)
{
    cam.zoom = 1.5;
    cam.rotation = 0;
    cam.target = target->posicao;
    cam.offset = (Vector2){0,0};
    cam.offset = (Vector2){tela.width/2 , tela.height/2};
}

