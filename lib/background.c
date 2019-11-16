#include "background.h"
#include "tela.h"

void setImageBackground(char* imagePath) {
    pathImageBackground = imagePath;
}

void updateBackground() {
    Image backgroundImage = LoadImage(pathImageBackground);
    ImageResize(&backgroundImage, tela.width, tela.height);  
    background = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);
}

