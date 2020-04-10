#include "object.h"

Objeto selecionarObjeto(Mapa fase, Camera2D camera){
    Vector2 mousePos = GetMousePosition();
    mousePos = (Vector2){(mousePos.x -camera.offset.x) / camera.zoom, (mousePos.y -camera.offset.y) / camera.zoom};

    for (int i = 0; i < fase.parede_atual; i++){
        if(CheckCollisionCircleRec(mousePos,5, fase.parede[i])){
            return (Objeto){PAREDE,i};
        }
    }
    for (int i = 0; i < fase.inimigo_atual; i++){
        if(CheckCollisionCircles(mousePos,5, fase.inimigo[i], 5)){
            return (Objeto){INIMIGO,i};
        }
    }
    for (int i = 0; i < fase.vida_atual; i++){
        if(CheckCollisionCircles(mousePos,5, fase.vida[i], 5)){
            return (Objeto){VIDA,i};
        }
    }
    for (int i = 0; i < fase.flecha_atual; i++){
        if(CheckCollisionCircles(mousePos,5, fase.flecha[i], 5)){
            return (Objeto){FLECHA,i};
        }
    }
    for (int i = 0; i < fase.piso_atual; i++){
        if(CheckCollisionCircleRec(mousePos,5, fase.piso[i])){
            return (Objeto){PISO,i};
        }
    }
    return (Objeto){NENHUM,0};
}
void CheckFileOnScreen(Mapa *fase){
    int count = 0;
    char **arquivosSoltos = {0};

    if(IsFileDropped() && !count){
        arquivosSoltos = GetDroppedFiles(&count);
        carregar(arquivosSoltos[count -1], fase);
        ClearDroppedFiles();
    }
}