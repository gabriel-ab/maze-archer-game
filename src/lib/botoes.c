#include "../include/botoes.h"

// Controls the selection between min and max, both included
void menuControl(int min, int max, int *selection){
    if (IsKeyPressed(KEY_UP)){
        if (*selection > min) *selection = *selection -1;
        else *selection = max;
    }
    if (IsKeyPressed(KEY_DOWN)){
        if (*selection < max) *selection = *selection +1;
        else *selection = min;
    }
}