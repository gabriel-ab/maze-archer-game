void move(Vector2 *coisa){
    if(IsKeyDown(KEY_W)) coisa->y -= 2;
    if(IsKeyDown(KEY_S)) coisa->y += 2;
    if(IsKeyDown(KEY_A)) coisa->x -= 2;
    if(IsKeyDown(KEY_D)) coisa->x += 2;
}